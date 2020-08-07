/***************************************************************************
                               xycalculator.cpp
                             ------------------
    begin                : Thu Oct 25 2018
    copyright            : (C) 2018 by Thomas Lepoix
    email                : thomas.lepoix@protonmail.ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <array>
#include <iostream>
#include <stack>
#include <utility>

#include "logger.hpp"
#include "microstrip/pac.hpp"
#include "microstrip/subst.hpp"
#include "xycalculator.hpp"
using namespace std;

XyCalculator::XyCalculator(Data& _data) :
	data(_data)
	{}

int XyCalculator::run(void) {

//check geometric coherence of the schematic
	if(check_intersection()) {
		log_err << "ERROR : A wire is used to connect more than two connection points.\n"
		           "\tPlease use a component like a tee or a cross to avoid this.\n";
		return(3);
		}

	//delete unconnected nets
	purge_nets();
	populate_adjacents();
	resolve_pac_shapes();
	place_elements();
	purge_blocks();
	place_blocks();

	return(0);
	}

void XyCalculator::resolve_pac_shapes(void) {
// Pac have no shape so they calc it from adjacent largest element
	for(shared_ptr<Element> pac : data.tab_all) {
		if(pac->getType()=="Pac" && dynamic_cast<Pac*>(pac.get())->is_size_set==false) {
			long double edge=0;
			short dir=0;
			for(short i=1;i<=pac->getNport();i++) {
				string pac_net;
				if(i==1) pac_net=pac->getNet1();
				else if(i==2) pac_net=pac->getNet2();
				for(shared_ptr<Element> element : data.tab_all) {
					if(element!=pac) {
						int net=0;
						if(element->getNet1()==pac_net) net=1;
						if(element->getNet2()==pac_net) net=2;
						if(element->getNet3()==pac_net) net=3;
						if(element->getNet4()==pac_net) net=4;
						if(net) {
							long double edge_tmp;
							short dir_tmp;
							element->getEdge(net, edge_tmp, dir_tmp);
							if(edge_tmp>edge) {
								edge=edge_tmp;
								dir=dir_tmp;
								}
							break;
							}
						}
					}
				}
			pac->setW(edge);
			pac->setL(data.port_default_l);
			switch(dir) {
				// Only axis matters
				case XMIN: case XMAX: pac->setR(0); break;
				case YMIN: case YMAX: pac->setR(90); break;
				}
			}
		}
	}

void XyCalculator::place_elements(void) {
	if(!data.tab_all.size())
		return;

//variables
	vector<shared_ptr<Element>> tab_undone=data.tab_all;
	stack<shared_ptr<Element>> buffer;
	shared_ptr<Element> current=tab_undone.front();
	shared_ptr<Element> next=nullptr;

	long double prev_xstep=0;
	long double prev_ystep=0;
	long double current_xstep=0;
	long double current_ystep=0;
	int nnets;
	int current_net=0;

//first element
	current->setX(0);
	current->setY(0);
	cout << endl << "Calculating elements positions..." << endl;
	cout << "Current label : " << current->getLabel() << endl;
	data.all_blocks.push_back(shared_ptr<Block>(new Block()));
	add_to_block(data.all_blocks.back(), current);

//algorithm : find elements potitions
	while(tab_undone.size()) {
		nnets=activenets(current);
		cout << "Undone elements : " << tab_undone.size() << endl;
		cout << "Active nets : " << nnets << endl;
		if(nnets==0) {
			tab_remove(tab_undone, current);
			if(buffer.empty()==false){
				current=buffer.top();
				add_to_block(data.all_blocks.back(), current);
				buffer.pop();
				cout << "End of a branch : Next from buffer" << endl;
				cout << endl;
				cout << "Current label : " << current->getLabel() << endl;
			} else {
				if(tab_undone.size()) {
					current=tab_undone.front();
					data.all_blocks.push_back(shared_ptr<Block>(new Block()));
					add_to_block(data.all_blocks.back(), current);
					cout << "End of a block : Next from undone elements" << endl;
					cout << endl;
					cout << "Current label : " << current->getLabel() << endl;
					}
				if(current->getX()!=current->getX() || current->getY()!=current->getY()) {
					// Reset position
					current->setX(0);
					current->setY(0);
					cout << "Reset X : " << current->getX() << endl;
					cout << "Reset Y : " << current->getY() << endl;
					}
				}
		} else {
			if(nnets==1) {
				tab_remove(tab_undone, current);
			} else {
				buffer.push(current);
				}
			current_net=netmin(current);
			cout << "Selected net : " << current_net << endl;
			current->getStep(current_net, prev_xstep, prev_ystep);
			findnext(current, current_net, next);
			cout << "Next label : " << next->getLabel() << endl;
			next->prev=current;
			current=next;
			add_to_block(data.all_blocks.back(), current);
			next=nullptr;
			cout << endl;
			cout << "Current label : " << current->getLabel() << endl;
			if(current->getX()!=current->getX() || current->getY()!=current->getY()) { // If position is -NaN
				current->getStep(current_net, current_xstep, current_ystep);
				cout << "Previous Xstep : " << prev_xstep << endl;
				cout << "Previous Ystep : " << prev_ystep << endl;
				cout << "Current Xstep : " << -1*current_xstep << endl;
				cout << "Current Ystep : " << -1*current_ystep << endl;
				current->setX((current->prev->getX())+(prev_xstep)-(current_xstep));
				current->setY((current->prev->getY())+(prev_ystep)-(current_ystep));
				cout << "X : " << current->getX() << endl;
				cout << "Y : " << current->getY() << endl;
				}
			}
		}
	cout << "Calculating elements positons... OK" << endl;
	}

void XyCalculator::place_blocks(void) {
//place element blocks regarding each other

//store all substrates
	vector<shared_ptr<Element>> tab_subst;
	for(shared_ptr<Element> it : data.tab_all) {
		if(it->getType()=="SUBST") {
			tab_subst.push_back(it);
			}
		}
	if(!tab_subst.size()) {
		data.is_volume_error=true;
		data.volume_error += "ERROR : No substrate in the schematic.\n";
		}

//check block / subst coherence
	cout << endl << "Analysing blocks... ";
	for(shared_ptr<Block> block : data.all_blocks) {
		vector<pair<string, int>> subst_in_block;
		for(shared_ptr<Element> it : block->elements) {
			if(it->getType()=="Pac") {
				continue; // No subst field in Pac
				}
			bool subst_exist=false;
			for(shared_ptr<Element> subst : tab_subst) {
				if(it->getSubst()==subst->getLabel()) {
					subst_exist=true;
					break;
					}
				}
			if(!subst_exist) {
				data.is_volume_error=true;
				data.volume_error += "ERROR : Invalid substrate \"" + it->getSubst()
				                  + "\" in : " + it->getLabel() + "\n";
				}

		//count each different subst occurences in a block
			bool subst_registered=false;
			for(pair<string, int> subst : subst_in_block) {
				if(subst.first==it->getSubst()) {
					subst.second++;
					subst_registered=true;
					break;
					}
				}
			if(!subst_registered) {
				subst_in_block.push_back(pair<string, int>(it->getSubst(), 1));
				}
			}

	//treat different occurences configurations
		if(subst_in_block.size()==0
		||(subst_in_block.size()==1
		&& subst_in_block[0].first=="")) {
			data.is_volume_error=true;
			data.volume_error += "ERROR : No substrate used in a block\n";
		} else if(subst_in_block.size()>1) {
			data.is_volume_error=true;
			data.volume_error += "ERROR : Too many different substrates used in a block\n";
		} else if(subst_in_block.size()==1) {
			//assign a subst to block
			for(shared_ptr<Element> subst : tab_subst) {
				if(subst->getLabel()==subst_in_block[0].first) {
					block->subst=subst;
					}
				}
			//set pacs subst field to block subst
			for(shared_ptr<Element> pac : block->elements) {
				if(pac->getType()=="Pac") {
					pac->setSubst(block->subst->getLabel());
					}
				}
			}
		}
	cout << "OK" << endl;

	sort_blocks(data.all_blocks, tab_subst); //sort by subst

//block placement
	cout << endl << "Calculating blocks positons..." << endl;
	shared_ptr<Block> prev=nullptr;
	axis_t vector=Y;
	for(shared_ptr<Block> block : data.all_blocks) {
		cout << endl;
		cout << "Block :" << endl;
		block->print();
		if(block->subst) block->margin=block->subst->getMargin();
		block->set_extrem_pos();
		if(prev) {
			long double shift_x;
			long double shift_y;
			cout << "Previous extrem positions :" << endl;
			prev->print_extrem_pos();
			bool is_new_subst=false;
			if(block->subst!=prev->subst) {
				is_new_subst=true;
				cout << "Different substrate : margins doubled" << endl;
				}
			if(vector==X) {
				cout << "Shift vector : X" << endl;
				shift_x=prev->extrem_pos[XMAX]-block->extrem_pos[XMIN];
				shift_y=prev->extrem_pos[YMIN]-block->extrem_pos[YMIN];
				if(is_new_subst) shift_x+=prev->margin+block->margin;
				shift_x+=prev->margin+block->margin;
			} else {
				cout << "Shift vector : Y" << endl;
				shift_y=prev->extrem_pos[YMAX]-block->extrem_pos[YMIN];
				shift_x=prev->extrem_pos[XMIN]-block->extrem_pos[XMIN];
				if(is_new_subst) shift_y+=prev->margin+block->margin;
				shift_y+=prev->margin+block->margin;
				}
			//shift=set_margin(prev, block, data);
			cout << "Xshift : " << shift_x << endl;
			cout << "Yshift : " << shift_y << endl;
			block->shift(shift_x, shift_y);
			cout << "Shifted extrem positions :" << endl;
			block->print_extrem_pos();
			}

		prev=block;
		if(block->extrem_pos[XMAX]-block->extrem_pos[XMIN]
		>= block->extrem_pos[YMAX]-block->extrem_pos[YMIN]) {
			vector=Y;
		} else {
			vector=X;
			}
		}
	cout << "Calculating blocks positons... OK" << endl;

//subst placement
	cout << endl << "Calculating substrates positons..." << endl;
	for(shared_ptr<Element> subst : tab_subst) {
		array<long double, 4> extrem_pos={0.0, 0.0, 0.0, 0.0};
		for(shared_ptr<Block> block : data.all_blocks) {
			if(block->subst==subst) {
				extrem_pos=block->extrem_pos;
				break;
				}
			data.extrem_pos=block->extrem_pos;
			}
		for(shared_ptr<Block> block : data.all_blocks) {
			if(block->subst==subst) {
				if(block->extrem_pos[XMIN]<extrem_pos[XMIN]) extrem_pos[XMIN]=block->extrem_pos[XMIN];
				if(block->extrem_pos[XMAX]>extrem_pos[XMAX]) extrem_pos[XMAX]=block->extrem_pos[XMAX];
				if(block->extrem_pos[YMIN]<extrem_pos[YMIN]) extrem_pos[YMIN]=block->extrem_pos[YMIN];
				if(block->extrem_pos[YMAX]>extrem_pos[YMAX]) extrem_pos[YMAX]=block->extrem_pos[YMAX];
				}
			}
		subst->setL(extrem_pos[XMAX]-extrem_pos[XMIN]+2*subst->getMargin());
		subst->setW(extrem_pos[YMAX]-extrem_pos[YMIN]+2*subst->getMargin());
		subst->setX((extrem_pos[XMAX]+extrem_pos[XMIN])/2);
		subst->setY((extrem_pos[YMAX]+extrem_pos[YMIN])/2);
		subst->setP();
		}


//set global extrem_pos
	for(shared_ptr<Block> block : data.all_blocks) {
		if(block->extrem_pos[XMIN]-block->margin<data.extrem_pos[XMIN]) data.extrem_pos[XMIN]=block->extrem_pos[XMIN]-block->margin;
		if(block->extrem_pos[XMAX]+block->margin>data.extrem_pos[XMAX]) data.extrem_pos[XMAX]=block->extrem_pos[XMAX]+block->margin;
		if(block->extrem_pos[YMIN]-block->margin<data.extrem_pos[YMIN]) data.extrem_pos[YMIN]=block->extrem_pos[YMIN]-block->margin;
		if(block->extrem_pos[YMAX]+block->margin>data.extrem_pos[YMAX]) data.extrem_pos[YMAX]=block->extrem_pos[YMAX]+block->margin;
		}

	for(shared_ptr<Element> it : tab_subst) {
		Subst* subst=dynamic_cast<Subst*>(it.get());
		if(subst->extrem_pos[XMIN]-subst->getMargin()<data.extrem_pos[XMIN]) data.extrem_pos[XMIN]=subst->extrem_pos[XMIN]-subst->getMargin();
		if(subst->extrem_pos[XMAX]+subst->getMargin()>data.extrem_pos[XMAX]) data.extrem_pos[XMAX]=subst->extrem_pos[XMAX]+subst->getMargin();
		if(subst->extrem_pos[YMIN]-subst->getMargin()<data.extrem_pos[YMIN]) data.extrem_pos[YMIN]=subst->extrem_pos[YMIN]-subst->getMargin();
		if(subst->extrem_pos[YMAX]+subst->getMargin()>data.extrem_pos[YMAX]) data.extrem_pos[YMAX]=subst->extrem_pos[YMAX]+subst->getMargin();
		}
	cout << "Calculating substrates positons... OK" << endl;

//translate to positive quarter
	cout << endl << "Translating to positive quarter... ";
	for(shared_ptr<Block> block : data.all_blocks) {
		block->shift(-data.extrem_pos[XMIN], -data.extrem_pos[YMIN]);
		}
	for(shared_ptr<Element> subst : tab_subst) {
		subst->setX(subst->getX()-data.extrem_pos[XMIN]);
		subst->setY(subst->getY()-data.extrem_pos[YMIN]);
		subst->setP();
		}
	//maximums first
	data.extrem_pos[XMAX]-=data.extrem_pos[XMIN];
	data.extrem_pos[XMIN]-=data.extrem_pos[XMIN];
	data.extrem_pos[YMAX]-=data.extrem_pos[YMIN];
	data.extrem_pos[YMIN]-=data.extrem_pos[YMIN];
	cout << "OK" << endl;

//local subst placement
	cout << endl << "Calculating local substrates positons... ";
	for(shared_ptr<Block> block : data.all_blocks) {
		if(block->subst) {
			Subst* subst=dynamic_cast<Subst*>(block->subst.get());
			block->subst_local=shared_ptr<Element>(new Subst(subst));
			block->subst_local->setL(block->boundary[XMAX]-block->boundary[XMIN]);//+2*block->subst_local->getMargin());
			block->subst_local->setW(block->boundary[YMAX]-block->boundary[YMIN]);//+2*block->subst_local->getMargin());
			block->subst_local->setX((block->boundary[XMAX]+block->boundary[XMIN])/2);
			block->subst_local->setY((block->boundary[YMAX]+block->boundary[YMIN])/2);
			block->subst_local->setP();
			}
		}
	cout << "OK" << endl;
	}

void XyCalculator::sort_blocks(vector<shared_ptr<Block>> blocks, vector<shared_ptr<Element>> substs) {
	vector<shared_ptr<Block>> tmp_blocks;
	for(shared_ptr<Element> subst : substs) {
		for(shared_ptr<Block> block : blocks) {
			if(block->subst==subst) {
				tmp_blocks.push_back(block);
				}
			}
		}
	for(shared_ptr<Block> block : blocks) {
		if(block->subst==nullptr) {
			tmp_blocks.push_back(block);
			}
		}
	blocks.swap(tmp_blocks);
	}

int XyCalculator::add_to_block(shared_ptr<Block>& block, shared_ptr<Element> const& element) {
//add geometric element if not already present
	if(element->getType()=="SUBST"
	|| element->getType()==".SP") {
		return(1);
		}
	for(shared_ptr<Element> it : block->elements) {
		if(it==element) {
			return(1);
			}
		}
	block->elements.push_back(element);
	return(0);
	}

int XyCalculator::tab_remove(vector<shared_ptr<Element>>& elements, shared_ptr<Element> const& element) {
	for(unsigned int i=0;i<elements.size();i++) {
		if(elements[i]==element) {
			elements.erase(elements.begin()+i);
			break;
			}
		}
	return(0);
	}

bool XyCalculator::purgefind(shared_ptr<Element> const& element, string const net) {
//check if another element with this net exists
	for(shared_ptr<Element> it : data.tab_all) {
		if(it!=element) {
			if(it->getNet1()==net) return(1);
			if(it->getNet2()==net) return(1);
			if(it->getNet3()==net) return(1);
			if(it->getNet4()==net) return(1);
			}
		}
	return(0);
	}

int XyCalculator::purge_nets(void) {
//delete unconnected nets
	for(shared_ptr<Element> it : data.tab_all) {
		if(purgefind(it, it->getNet1())==false) it->setNet1("");
		if(purgefind(it, it->getNet2())==false) it->setNet2("");
		if(purgefind(it, it->getNet3())==false) it->setNet3("");
		if(purgefind(it, it->getNet4())==false) it->setNet4("");
		}
	return(0);
	}

int XyCalculator::purge_blocks(void) {
//delete blocks with only a non geometric element inside
	for(unsigned int i=0;i<data.all_blocks.size();i++) {
		if(data.all_blocks[i]->elements.size()==0) {
			data.all_blocks.erase(data.all_blocks.begin()+i);
			i--;
			}
		}
	return(0);
	}

bool XyCalculator::check_onenet(string const net) {
	unsigned int count=0;
	if(net!=""){
		for(shared_ptr<Element> it : data.tab_all) {
			if(it->getNet1()==net) count++;
			if(it->getNet2()==net) count++;
			if(it->getNet3()==net) count++;
			if(it->getNet4()==net) count++;
			}
		}
	return(count>2 ? 1 : 0);
	}

bool XyCalculator::check_intersection(void) {
//check if there are net intersections : more than 2 times the same net
	for(shared_ptr<Element> it : data.tab_all) {
		if(check_onenet(it->getNet1())==true) return(1);
		if(check_onenet(it->getNet2())==true) return(1);
		if(check_onenet(it->getNet3())==true) return(1);
		if(check_onenet(it->getNet4())==true) return(1);
		}
	return(0);
	}

int XyCalculator::activenets(shared_ptr<Element> const& element) {
	int nlinks=0;
	if(element->getNet1()!="") nlinks++;
	if(element->getNet2()!="") nlinks++;
	if(element->getNet3()!="") nlinks++;
	if(element->getNet4()!="") nlinks++;
	return(nlinks);
	}

int XyCalculator::netmin(shared_ptr<Element> const& element) {
	if(element->getNet1()!="") return(1);
	if(element->getNet2()!="") return(2);
	if(element->getNet3()!="") return(3);
	if(element->getNet4()!="") return(4);
	return(0);
	}

void XyCalculator::populate_adjacents(void) {
	for(shared_ptr<Element> element : data.tab_all) {
		for(shared_ptr<Element> it : data.tab_all) {
			if(it!=element) {
				if(get_port(it, element->getNet1())) element->setAdjacent(1, it, get_port(it, element->getNet1()));
				if(get_port(it, element->getNet2())) element->setAdjacent(2, it, get_port(it, element->getNet2()));
				if(get_port(it, element->getNet3())) element->setAdjacent(3, it, get_port(it, element->getNet3()));
				if(get_port(it, element->getNet4())) element->setAdjacent(4, it, get_port(it, element->getNet4()));
				}
			}
		}
	}

int XyCalculator::get_port(shared_ptr<Element> const& element, string const net) {
	if(net!="") {
		if(element->getNet1()==net) return(1);
		if(element->getNet2()==net) return(2);
		if(element->getNet3()==net) return(3);
		if(element->getNet4()==net) return(4);
		}
	return(0);
	}

void XyCalculator::findnext(shared_ptr<Element> const& current, int& current_net, shared_ptr<Element>& next) {
//find next element and delete link
	string net="";
	if(current_net==1) {
		net=current->getNet1();
		current->setNet1("");
	} else if(current_net==2) {
		net=current->getNet2();
		current->setNet2("");
	} else if(current_net==3) {
		net=current->getNet3();
		current->setNet3("");
	} else if(current_net==4) {
		net=current->getNet4();
		current->setNet4("");
		}
	for(shared_ptr<Element> it : data.tab_all) {
		if(it!=current) {
			if(it->getNet1()==net) {
				cout << "Next net : 1" << endl;
				next=it;
				it->setNet1("");
				current_net=1;
				break;
			} else if(it->getNet2()==net) {
				cout << "Next net : 2" << endl;
				next=it;
				it->setNet2("");
				current_net=2;
				break;
			} else if(it->getNet3()==net) {
				cout << "Next net : 3" << endl;
				next=it;
				it->setNet3("");
				current_net=3;
				break;
			} else if(it->getNet4()==net) {
				cout << "Next net : 4" << endl;
				next=it;
				it->setNet4("");
				current_net=4;
				break;
				}
			}
		}
	}
