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

#include "xycalculator.hpp"
using namespace std;

XyCalculator::XyCalculator(vector<shared_ptr<Element>>& _tab_all, array<long double, 4>& _extrem_pos) :
	tab_all(_tab_all),
	extrem_pos(_extrem_pos)
	{}

int XyCalculator::run(void) {

//variables
	vector<shared_ptr<Element>> tab_undone=tab_all;
	stack<shared_ptr<Element>> buffer;
	shared_ptr<Element> current=tab_undone[0];
	shared_ptr<Element> next=nullptr;

	long double prev_xstep=0;
	long double prev_ystep=0;
	long double current_xstep=0;
	long double current_ystep=0;
	int nnets;
	int current_net=0;

//check geometric coherence of the schematic
	if(checkintersection()) {
		log_err << "ERROR : A wire is used to connect more than two connection points.\n"
		           "\tPlease use a component like a tee or a cross to avoid this.\n";
		return(3);
		}

//delete unconnected nets
	purgenets();

//first element
	current->setX(0);
	current->setY(0);
	cout << endl << "Finding positions..." << endl << endl;
	cout << "Current label : " << current->getLabel() << endl;

//algorithm : find elements potitions
	while(tab_undone.size()) {
		nnets=activenets(current);
		cout << "Undone elements : " << tab_undone.size() << endl;
		cout << "Active nets : " << nnets << endl;
		if(nnets==0) {
			tab_remove(tab_undone, current);
			if(buffer.empty()==false){
				current=buffer.top();
				buffer.pop();
				cout << "End of a branch : Next from buffer" << endl;
				cout << endl;
				cout << "Current label : " << current->getLabel() << endl;
			} else {
				if(tab_undone.size()) {
					current=tab_undone[0];
					cout << "End of a block : Next from undone elements" << endl;
					cout << endl;
					cout << "Current label : " << current->getLabel() << endl;
					}
				if(current->getX()!=current->getX() || current->getY()!=current->getY()) {
					//set a random position
					current->setX(((long double)(tab_all.size()-tab_undone.size()))*-3);
					current->setY(((long double)(tab_all.size()-tab_undone.size()))*-3);
					cout << "Random X : " << current->getX() << endl;
					cout << "Random Y : " << current->getY() << endl;
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
//			xystep(current, current_net, prev_xstep, prev_ystep);
			current->getStep(current_net, prev_xstep, prev_ystep);
			findnext(current, current_net, next);
			cout << "Next label : " << next->getLabel() << endl;
			next->prev=current;
			current=next;
			next=nullptr;
			cout << endl;
			cout << "Current label : " << current->getLabel() << endl;
			if(current->getX()!=current->getX() || current->getY()!=current->getY()) {		//if position is -NaN
//				xystep(current, current_net, current_xstep, current_ystep);
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
	cout << endl << "Finding positons... DONE" << endl;



//find points positions & extrems points positions
	for(shared_ptr<Element> it : tab_all) {
		it->setP();
		for(int u=0;u<it->getNpoint();u++) {
			if(it->getP(u, X, R, ABS)<extrem_pos[XMIN]) extrem_pos[XMIN]=it->getP(u, X, R, ABS);
			if(it->getP(u, X, R, ABS)>extrem_pos[XMAX]) extrem_pos[XMAX]=it->getP(u, X, R, ABS);
			if(it->getP(u, Y, R, ABS)<extrem_pos[YMIN]) extrem_pos[YMIN]=it->getP(u, Y, R, ABS);
			if(it->getP(u, Y, R, ABS)>extrem_pos[YMAX]) extrem_pos[YMAX]=it->getP(u, Y, R, ABS);
			}
		}

	cout << endl;
	cout << "Xmin : " << extrem_pos[XMIN] << endl;
	cout << "Xmax : " << extrem_pos[XMAX] << endl;
	cout << "Ymin : " << extrem_pos[YMIN] << endl;
	cout << "Ymax : " << extrem_pos[YMAX] << endl;

//translate shapes in positive quarter
	for(shared_ptr<Element> it : tab_all) {
		it->setX(it->getX()-extrem_pos[XMIN]+1);
		it->setY(it->getY()-extrem_pos[YMIN]+1);
		it->setP();
		}

//reset extrem_pos
	for(unsigned char i=0;i<4;i++)
		extrem_pos[i]=0.0;
	for(shared_ptr<Element> it : tab_all) {
		for(int u=0;u<it->getNpoint();u++) {
			if(it->getP(u, X, R, ABS)<extrem_pos[XMIN]) extrem_pos[XMIN]=it->getP(u, X, R, ABS);
			if(it->getP(u, X, R, ABS)>extrem_pos[XMAX]) extrem_pos[XMAX]=it->getP(u, X, R, ABS);
			if(it->getP(u, Y, R, ABS)<extrem_pos[YMIN]) extrem_pos[YMIN]=it->getP(u, Y, R, ABS);
			if(it->getP(u, Y, R, ABS)>extrem_pos[YMAX]) extrem_pos[YMAX]=it->getP(u, Y, R, ABS);
			}
		}

	cout << "Translated extrem positions :" << endl;
	cout << "Xmin : " << extrem_pos[XMIN] << endl;
	cout << "Xmax : " << extrem_pos[XMAX] << endl;
	cout << "Ymin : " << extrem_pos[YMIN] << endl;
	cout << "Ymax : " << extrem_pos[YMAX] << endl;



//delete objects inner pointers
	for(shared_ptr<Element> it : tab_all) {
		it->prev=nullptr;
		}
	return(0);
	}

int XyCalculator::tab_remove(vector<shared_ptr<Element>>& tab_undone, shared_ptr<Element> const& current) {
	for(unsigned int i=0;i<tab_undone.size();i++) {
		if(tab_undone[i]==current) {
			tab_undone.erase(tab_undone.begin()+i);
			break;
			}
		}
	return(0);
	}

bool XyCalculator::purgefind(shared_ptr<Element> const& current, string const _net) {
//check if another element with this net exists
	for(shared_ptr<Element> it : tab_all) {
		if(it!=current) {
			if(it->getNet1()==_net) return(1);
			if(it->getNet2()==_net) return(1);
			if(it->getNet3()==_net) return(1);
			if(it->getNet4()==_net) return(1);
			}
		}
	return(0);
	}

int XyCalculator::purgenets(void) {
//delete unconnected nets
	for(shared_ptr<Element> it : tab_all) {
		if(purgefind(it, it->getNet1())==false) it->setNet1("");
		if(purgefind(it, it->getNet2())==false) it->setNet2("");
		if(purgefind(it, it->getNet3())==false) it->setNet3("");
		if(purgefind(it, it->getNet4())==false) it->setNet4("");
		}
	return(0);
	}

bool XyCalculator::checkonenet(string const _net) {
	unsigned int count=0;
	if(_net!=""){
		for(shared_ptr<Element> it : tab_all) {
			if(it->getNet1()==_net) count++;
			if(it->getNet2()==_net) count++;
			if(it->getNet3()==_net) count++;
			if(it->getNet4()==_net) count++;
			}
		}
	return(count>2 ? 1 : 0);
	}

int XyCalculator::checkintersection(void) {
//check if there are net intersections : more than 2 times the same net
	for(shared_ptr<Element> it : tab_all) {
		for(shared_ptr<Element> ut : tab_all) {
			if(checkonenet(it->getNet1())==true) return(1);
			if(checkonenet(it->getNet2())==true) return(1);
			if(checkonenet(it->getNet3())==true) return(1);
			if(checkonenet(it->getNet4())==true) return(1);
			}
		}
	return(0);
	}

int XyCalculator::activenets(shared_ptr<Element> const& _elem) {
	int nlinks=0;
	if(_elem->getNet1()!="") nlinks++;
	if(_elem->getNet2()!="") nlinks++;
	if(_elem->getNet3()!="") nlinks++;
	if(_elem->getNet4()!="") nlinks++;
	return(nlinks);
	}

int XyCalculator::netmin(shared_ptr<Element> const& _elem) {
	if(_elem->getNet1()!="") return(1);
	if(_elem->getNet2()!="") return(2);
	if(_elem->getNet3()!="") return(3);
	if(_elem->getNet4()!="") return(4);
	return(0);
	}

int XyCalculator::findnext(shared_ptr<Element> const& current, int& current_net, shared_ptr<Element>& next) {
//find next element and delete link
	string _net="";
	if(current_net==1) {
		_net=current->getNet1();
		current->setNet1("");
	} else if(current_net==2) {
		_net=current->getNet2();
		current->setNet2("");
	} else if(current_net==3) {
		_net=current->getNet3();
		current->setNet3("");
	} else if(current_net==4) {
		_net=current->getNet4();
		current->setNet4("");
		}
	for(shared_ptr<Element> it : tab_all) {
		if(it!=current) {
			if(it->getNet1()==_net) {
				cout << "Next net : 1" << endl;
				next=it;
				it->setNet1("");
				current_net=1;
				break;
			} else if(it->getNet2()==_net) {
				cout << "Next net : 2" << endl;
				next=it;
				it->setNet2("");
				current_net=2;
				break;
			} else if(it->getNet3()==_net) {
				cout << "Next net : 3" << endl;
				next=it;
				it->setNet3("");
				current_net=3;
				break;
			} else if(it->getNet4()==_net) {
				cout << "Next net : 4" << endl;
				next=it;
				it->setNet4("");
				current_net=4;
				break;
				}
			}
		}
	return(0);
	}
