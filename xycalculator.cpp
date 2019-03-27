/***************************************************************************
                               xycalculator.cpp
                             ------------------
    begin                : Thu Oct 25 2018
    copyright            : (C) 2018 by Thomas Lepoix
    email                : thomas.lepoix@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "xycalculator.h"
using namespace std;

int xycalculator(std::vector<std::shared_ptr<Element>>& tab_all, long double* extrem_pos) {

//variables
	vector<shared_ptr<Element>> tab_undone=tab_all;
	stack<shared_ptr<Element>> buffer;
	shared_ptr<Element> current=tab_all[0];
	shared_ptr<Element> next=NULL;

	long double prev_xstep=0;
	long double prev_ystep=0;
	long double current_xstep=0;
	long double current_ystep=0;
	int nnets;
	int current_net=0;

//delete unconnected nets
	purgenets(tab_all);

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
					current->setX(((long double)(tab_all.size()-tab_undone.size()))*-3);		//set a random position
					current->setY(((long double)(tab_all.size()-tab_undone.size()))*-3);		//
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
			xystep(current, current_net, prev_xstep, prev_ystep);
			findnext(tab_all, current, current_net, next);
			cout << "Next label : " << next->getLabel() << endl;
			next->prev=current;
			current=next;
			next=NULL;
			cout << endl;
			cout << "Current label : " << current->getLabel() << endl;
			if(current->getX()!=current->getX() || current->getY()!=current->getY()) {		//if position is -NaN
				xystep(current, current_net, current_xstep, current_ystep);
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
			if(it->getP(u, _X, _R, _ABS)<extrem_pos[_XMIN]) extrem_pos[_XMIN]=it->getP(u, _X, _R, _ABS);
			if(it->getP(u, _X, _R, _ABS)>extrem_pos[_XMAX]) extrem_pos[_XMAX]=it->getP(u, _X, _R, _ABS);
			if(it->getP(u, _Y, _R, _ABS)<extrem_pos[_YMIN]) extrem_pos[_YMIN]=it->getP(u, _Y, _R, _ABS);
			if(it->getP(u, _Y, _R, _ABS)>extrem_pos[_YMAX]) extrem_pos[_YMAX]=it->getP(u, _Y, _R, _ABS);
			}
		}

	cout << endl;
	cout << "Xmin : " << extrem_pos[_XMIN] << endl;
	cout << "Xmax : " << extrem_pos[_XMAX] << endl;
	cout << "Ymin : " << extrem_pos[_YMIN] << endl;
	cout << "Ymax : " << extrem_pos[_YMAX] << endl;

	for(shared_ptr<Element> it : tab_all) {
		it->prev=NULL;
		}
	return(0);
	}

int tab_remove(vector<shared_ptr<Element>>& tab_undone, shared_ptr<Element> const& current) {
	for(unsigned int i=0;i<tab_undone.size();i++) {
		if(tab_undone[i]==current) {
			tab_undone.erase(tab_undone.begin()+i);
			break;
			}
		}
	return(0);
	}

bool purgefind(vector<shared_ptr<Element>> const& tab_all, shared_ptr<Element> const& current, string const _net) {
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

int purgenets(vector<shared_ptr<Element>> const& tab_all) {
//delete unconnected nets
	for(shared_ptr<Element> it : tab_all) {
		for(unsigned char u=1;u<5;u++) {
			if(u==1) {
				if(purgefind(tab_all, it, it->getNet1())==false) it->setNet1("");
			} else if(u==2) {
				if(purgefind(tab_all, it, it->getNet2())==false) it->setNet2("");
			} else if(u==3) {
				if(purgefind(tab_all, it, it->getNet3())==false) it->setNet3("");
			} else if(u==4) {
				if(purgefind(tab_all, it, it->getNet4())==false) it->setNet4("");
				}
			}
		}
	return(0);
	}

int activenets(shared_ptr<Element> const& _elem) {
	int nlinks=0;
	if(_elem->getNet1()!="") nlinks++;
	if(_elem->getNet2()!="") nlinks++;
	if(_elem->getNet3()!="") nlinks++;
	if(_elem->getNet4()!="") nlinks++;
	return(nlinks);
	}

int netmin(shared_ptr<Element> const& _elem) {
	if(_elem->getNet1()!="") return(1);
	if(_elem->getNet2()!="") return(2);
	if(_elem->getNet3()!="") return(3);
	if(_elem->getNet4()!="") return(4);
	return(0);
	}

int findnext(vector<shared_ptr<Element>> const& tab_all, shared_ptr<Element> const& current, int& current_net, shared_ptr<Element>& next) {
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

int xystep(shared_ptr<Element> const& _elem, int const _net, long double& xstep, long double& ystep) {
//step from center to port
	string type=_elem->getType();
	long double Wlong=0;
	xstep=0;
	ystep=0;

	if(type=="Eqn"
	|| type=="Pac"
	|| type=="MOPEN"
	|| type=="MRSTUB"
	|| type=="MSTEP"
	|| type=="MVIA") {
		xstep=0;
		ystep=0;
	} else if(type=="MCORN" || type=="MMBEND") {
		if(_elem->getMirrorx()==0 && _elem->getR()==0) {
			if(_net==1) {
				xstep= - (_elem->getW())/2;
				ystep=0;
			} else if(_net==2) {
				xstep=0;
				ystep= + (_elem->getW())/2;
				}
		} else if(_elem->getMirrorx()==0 && _elem->getR()==90) {
			if(_net==1) {
				xstep=0;
				ystep= + (_elem->getW())/2;
			} else if(_net==2) {
				xstep= + (_elem->getW())/2;
				ystep=0;
				}
		} else if(_elem->getMirrorx()==0 && _elem->getR()==180) {
			if(_net==1) {
				xstep= + (_elem->getW())/2;
				ystep=0;
			} else if(_net==2) {
				xstep=0;
				ystep= - (_elem->getW())/2;
				}
		} else if(_elem->getMirrorx()==0 && _elem->getR()==270) {
			if(_net==1) {
				xstep=0;
				ystep= - (_elem->getW())/2;
			} else if(_net==2) {
				xstep= - (_elem->getW())/2;
				ystep=0;
				}
		} else if(_elem->getMirrorx()==1 && _elem->getR()==0) {
			if(_net==1) {
				xstep= - (_elem->getW())/2;
				ystep=0;
			} else if(_net==2) {
				xstep=0;
				ystep= - (_elem->getW())/2;
				}
		} else if(_elem->getMirrorx()==1 && _elem->getR()==90) {
			if(_net==1) {
				xstep=0;
				ystep= + (_elem->getW())/2;
			} else if(_net==2) {
				xstep= - (_elem->getW())/2;
				ystep=0;
				}
		} else if(_elem->getMirrorx()==1 && _elem->getR()==180) {
			if(_net==1) {
				xstep= + (_elem->getW())/2;
				ystep=0;
			} else if(_net==2) {
				xstep=0;
				ystep= + (_elem->getW())/2;
				}
		} else if(_elem->getMirrorx()==1 && _elem->getR()==270) {
			if(_net==1) {
				xstep=0;
				ystep= - (_elem->getW())/2;
			} else if(_net==2) {
				xstep= + (_elem->getW())/2;
				ystep=0;
				}
			}
	} else if(type=="MCOUPLED") {
		if(_elem->getMirrorx()==0 && _elem->getR()==0) {
			if(_net==1) {
				xstep= - (_elem->getL())/2;
				ystep= - ((_elem->getW())+(_elem->getS()))/2;
			} else if(_net==2) {
				xstep= + (_elem->getL())/2;
				ystep= - ((_elem->getW())+(_elem->getS()))/2;
			} else if(_net==3) {
				xstep= + (_elem->getL())/2;
				ystep= + ((_elem->getW())+(_elem->getS()))/2;
			} else if(_net==4) {
				xstep= - (_elem->getL())/2;
				ystep= + ((_elem->getW())+(_elem->getS()))/2;
				}
		} else if(_elem->getMirrorx()==0 && _elem->getR()==90) {
			if(_net==1) {
				xstep= - ((_elem->getW())+(_elem->getS()))/2;
				ystep= + (_elem->getL())/2;
			} else if(_net==2) {
				xstep= - ((_elem->getW())+(_elem->getS()))/2;
				ystep= - (_elem->getL())/2;
			} else if(_net==3) {
				xstep= + ((_elem->getW())+(_elem->getS()))/2;
				ystep= - (_elem->getL())/2;
			} else if(_net==4) {
				xstep= + ((_elem->getW())+(_elem->getS()))/2;
				ystep= + (_elem->getL())/2;
				}
		} else if(_elem->getMirrorx()==0 && _elem->getR()==180) {
			if(_net==1) {
				xstep= + (_elem->getL())/2;
				ystep= + ((_elem->getW())+(_elem->getS()))/2;
			} else if(_net==2) {
				xstep= - (_elem->getL())/2;
				ystep= + ((_elem->getW())+(_elem->getS()))/2;
			} else if(_net==3) {
				xstep= - (_elem->getL())/2;
				ystep= - ((_elem->getW())+(_elem->getS()))/2;
			} else if(_net==4) {
				xstep= + (_elem->getL())/2;
				ystep= - ((_elem->getW())+(_elem->getS()))/2;
				}
		} else if(_elem->getMirrorx()==0 && _elem->getR()==270) {
			if(_net==1) {
				xstep= + ((_elem->getW())+(_elem->getS()))/2;
				ystep= - (_elem->getL())/2;
			} else if(_net==2) {
				xstep= + ((_elem->getW())+(_elem->getS()))/2;
				ystep= + (_elem->getL())/2;
			} else if(_net==3) {
				xstep= - ((_elem->getW())+(_elem->getS()))/2;
				ystep= + (_elem->getL())/2;
			} else if(_net==4) {
				xstep= - ((_elem->getW())+(_elem->getS()))/2;
				ystep= - (_elem->getL())/2;
				}
		} else if(_elem->getMirrorx()==1 && _elem->getR()==0) {
			if(_net==1) {
				xstep= - (_elem->getL())/2;
				ystep= + ((_elem->getW())+(_elem->getS()))/2;
			} else if(_net==2) {
				xstep= + (_elem->getL())/2;
				ystep= + ((_elem->getW())+(_elem->getS()))/2;
			} else if(_net==3) {
				xstep= + (_elem->getL())/2;
				ystep= - ((_elem->getW())+(_elem->getS()))/2;
			} else if(_net==4) {
				xstep= - (_elem->getL())/2;
				ystep= - ((_elem->getW())+(_elem->getS()))/2;
				}
		} else if(_elem->getMirrorx()==1 && _elem->getR()==90) {
			if(_net==1) {
				xstep= + ((_elem->getW())+(_elem->getS()))/2;
				ystep= + (_elem->getL())/2;
			} else if(_net==2) {
				xstep= + ((_elem->getW())+(_elem->getS()))/2;
				ystep= - (_elem->getL())/2;
			} else if(_net==3) {
				xstep= - ((_elem->getW())+(_elem->getS()))/2;
				ystep= - (_elem->getL())/2;
			} else if(_net==4) {
				xstep= - ((_elem->getW())+(_elem->getS()))/2;
				ystep= + (_elem->getL())/2;
				}
		} else if(_elem->getMirrorx()==1 && _elem->getR()==180) {
			if(_net==1) {
				xstep= + (_elem->getL())/2;
				ystep= - ((_elem->getW())+(_elem->getS()))/2;
			} else if(_net==2) {
				xstep= - (_elem->getL())/2;
				ystep= - ((_elem->getW())+(_elem->getS()))/2;
			} else if(_net==3) {
				xstep= - (_elem->getL())/2;
				ystep= + ((_elem->getW())+(_elem->getS()))/2;
			} else if(_net==4) {
				xstep= + (_elem->getL())/2;
				ystep= + ((_elem->getW())+(_elem->getS()))/2;
				}
		} else if(_elem->getMirrorx()==1 && _elem->getR()==270) {
			if(_net==1) {
				xstep= - ((_elem->getW())+(_elem->getS()))/2;
				ystep= - (_elem->getL())/2;
			} else if(_net==2) {
				xstep= - ((_elem->getW())+(_elem->getS()))/2;
				ystep= + (_elem->getL())/2;
			} else if(_net==3) {
				xstep= + ((_elem->getW())+(_elem->getS()))/2;
				ystep= + (_elem->getL())/2;
			} else if(_net==4) {
				xstep= + ((_elem->getW())+(_elem->getS()))/2;
				ystep= - (_elem->getL())/2;
				}
			}
	} else if(type=="MCROSS") {
		if(_elem->getMirrorx()==0 && _elem->getR()==0) {
			if(_net==1) {
				Wlong= (_elem->getW2()>_elem->getW4()) ? _elem->getW2() : _elem->getW4();
				xstep= - (Wlong)/2;
				ystep=0;
			} else if(_net==2) {
				Wlong= (_elem->getW1()>_elem->getW3()) ? _elem->getW1() : _elem->getW3();
				xstep=0;
				ystep= - (Wlong)/2;
			} else if(_net==3) {
				Wlong= (_elem->getW2()>_elem->getW4()) ? _elem->getW2() : _elem->getW4();
				xstep= + (Wlong)/2;
				ystep=0;
			} else if(_net==4) {
				Wlong= (_elem->getW1()>_elem->getW3()) ? _elem->getW1() : _elem->getW3();
				xstep=0;
				ystep= + (Wlong)/2;
				}
		} else if(_elem->getMirrorx()==0 && _elem->getR()==90) {
			if(_net==1) {
				Wlong= (_elem->getW2()>_elem->getW4()) ? _elem->getW2() : _elem->getW4();
				xstep=0;
				ystep= + (Wlong)/2;
			} else if(_net==2) {
				Wlong= (_elem->getW1()>_elem->getW3()) ? _elem->getW1() : _elem->getW3();
				xstep= - (Wlong)/2;
				ystep=0;
			} else if(_net==3) {
				Wlong= (_elem->getW2()>_elem->getW4()) ? _elem->getW2() : _elem->getW4();
				xstep=0;
				ystep= - (Wlong)/2;
			} else if(_net==4) {
				Wlong= (_elem->getW1()>_elem->getW3()) ? _elem->getW1() : _elem->getW3();
				ystep=0;
				xstep= + (Wlong)/2;
				}
		} else if(_elem->getMirrorx()==0 && _elem->getR()==180) {
			if(_net==1) {
				Wlong= (_elem->getW2()>_elem->getW4()) ? _elem->getW2() : _elem->getW4();
				xstep= + (Wlong)/2;
				ystep=0;
			} else if(_net==2) {
				Wlong= (_elem->getW1()>_elem->getW3()) ? _elem->getW1() : _elem->getW3();
				xstep=0;
				ystep= + (Wlong)/2;
			} else if(_net==3) {
				Wlong= (_elem->getW2()>_elem->getW4()) ? _elem->getW2() : _elem->getW4();
				xstep= - (Wlong)/2;
				ystep=0;
			} else if(_net==4) {
				Wlong= (_elem->getW1()>_elem->getW3()) ? _elem->getW1() : _elem->getW3();
				xstep=0;
				ystep= - (Wlong)/2;
				}
		} else if(_elem->getMirrorx()==0 && _elem->getR()==270) {
			if(_net==1) {
				Wlong= (_elem->getW2()>_elem->getW4()) ? _elem->getW2() : _elem->getW4();
				xstep=0;
				ystep= - (Wlong)/2;
			} else if(_net==2) {
				Wlong= (_elem->getW1()>_elem->getW3()) ? _elem->getW1() : _elem->getW3();
				xstep= + (Wlong)/2;
				ystep=0;
			} else if(_net==3) {
				Wlong= (_elem->getW2()>_elem->getW4()) ? _elem->getW2() : _elem->getW4();
				xstep=0;
				ystep= + (Wlong)/2;
			} else if(_net==4) {
				Wlong= (_elem->getW1()>_elem->getW3()) ? _elem->getW1() : _elem->getW3();
				ystep=0;
				xstep= - (Wlong)/2;
				}
		} else if(_elem->getMirrorx()==1 && _elem->getR()==0) {
			if(_net==1) {
				Wlong= (_elem->getW2()>_elem->getW4()) ? _elem->getW2() : _elem->getW4();
				xstep= - (Wlong)/2;
				ystep=0;
			} else if(_net==2) {
				Wlong= (_elem->getW1()>_elem->getW3()) ? _elem->getW1() : _elem->getW3();
				xstep=0;
				ystep= + (Wlong)/2;
			} else if(_net==3) {
				Wlong= (_elem->getW2()>_elem->getW4()) ? _elem->getW2() : _elem->getW4();
				xstep= + (Wlong)/2;
				ystep=0;
			} else if(_net==4) {
				Wlong= (_elem->getW1()>_elem->getW3()) ? _elem->getW1() : _elem->getW3();
				xstep=0;
				ystep= - (Wlong)/2;
				}
		} else if(_elem->getMirrorx()==1 && _elem->getR()==90) {
			if(_net==1) {
				Wlong= (_elem->getW2()>_elem->getW4()) ? _elem->getW2() : _elem->getW4();
				xstep=0;
				ystep= + (Wlong)/2;
			} else if(_net==2) {
				Wlong= (_elem->getW1()>_elem->getW3()) ? _elem->getW1() : _elem->getW3();
				xstep= + (Wlong)/2;
				ystep=0;
			} else if(_net==3) {
				Wlong= (_elem->getW2()>_elem->getW4()) ? _elem->getW2() : _elem->getW4();
				xstep=0;
				ystep= - (Wlong)/2;
			} else if(_net==4) {
				Wlong= (_elem->getW1()>_elem->getW3()) ? _elem->getW1() : _elem->getW3();
				ystep=0;
				xstep= - (Wlong)/2;
				}
		} else if(_elem->getMirrorx()==1 && _elem->getR()==180) {
			if(_net==1) {
				Wlong= (_elem->getW2()>_elem->getW4()) ? _elem->getW2() : _elem->getW4();
				xstep= + (Wlong)/2;
				ystep=0;
			} else if(_net==2) {
				Wlong= (_elem->getW1()>_elem->getW3()) ? _elem->getW1() : _elem->getW3();
				xstep=0;
				ystep= - (Wlong)/2;
			} else if(_net==3) {
				Wlong= (_elem->getW2()>_elem->getW4()) ? _elem->getW2() : _elem->getW4();
				xstep= - (Wlong)/2;
				ystep=0;
			} else if(_net==4) {
				Wlong= (_elem->getW1()>_elem->getW3()) ? _elem->getW1() : _elem->getW3();
				xstep=0;
				ystep= + (Wlong)/2;
				}
		} else if(_elem->getMirrorx()==1 && _elem->getR()==270) {
			if(_net==1) {
				Wlong= (_elem->getW2()>_elem->getW4()) ? _elem->getW2() : _elem->getW4();
				xstep=0;
				ystep= - (Wlong)/2;
			} else if(_net==2) {
				Wlong= (_elem->getW1()>_elem->getW3()) ? _elem->getW1() : _elem->getW3();
				xstep= - (Wlong)/2;
				ystep=0;
			} else if(_net==3) {
				Wlong= (_elem->getW2()>_elem->getW4()) ? _elem->getW2() : _elem->getW4();
				xstep=0;
				ystep= + (Wlong)/2;
			} else if(_net==4) {
				Wlong= (_elem->getW1()>_elem->getW3()) ? _elem->getW1() : _elem->getW3();
				ystep=0;
				xstep= + (Wlong)/2;
				}
			}
	} else if(type=="MGAP") {
		if(_elem->getR()==0) {
			if(_net==1) {
				xstep= - (_elem->getS())/2;
				ystep=0;
			} else if(_net==2) {
				xstep= + (_elem->getS())/2;
				ystep=0;
				}
		} else if(_elem->getR()==90) {
			if(_net==1) {
				xstep=0;
				ystep= + (_elem->getS())/2;
			} else if(_net==2) {
				xstep=0;
				ystep= - (_elem->getS())/2;
				}
		} else if(_elem->getR()==180) {
			if(_net==1) {
				xstep= + (_elem->getS())/2;
				ystep=0;
			} else if(_net==2) {
				xstep= - (_elem->getS())/2;
				ystep=0;
				}
		} else if(_elem->getR()==270) {
			if(_net==1) {
				xstep=0;
				ystep= - (_elem->getS())/2;
			} else if(_net==2) {
				xstep=0;
				ystep= + (_elem->getS())/2;
				}
			}
	} else if(type=="MLIN") {
		if(_elem->getR()==0) {
			if(_net==1) {
				xstep= - (_elem->getL())/2;
				ystep=0;
			} else if(_net==2) {
				xstep= + (_elem->getL())/2;
				ystep=0;
				}
		} else if(_elem->getR()==90) {
			if(_net==1) {
				xstep=0;
				ystep= + (_elem->getL())/2;
			} else if(_net==2) {
				xstep=0;
				ystep= - (_elem->getL())/2;
				}
		} else if(_elem->getR()==180) {
			if(_net==1) {
				xstep= + (_elem->getL())/2;
				ystep=0;
			} else if(_net==2) {
				xstep= - (_elem->getL())/2;
				ystep=0;
				}
		} else if(_elem->getR()==270) {
			if(_net==1) {
				xstep=0;
				ystep= - (_elem->getL())/2;
			} else if(_net==2) {
				xstep=0;
				ystep= + (_elem->getL())/2;
				}
			}
	} else if(type=="MTEE") {
		if(_elem->getMirrorx()==0 && _elem->getR()==0) {
			if(_net==1) {
				xstep= - (_elem->getW3())/2;
				ystep=0;
			} else if(_net==2) {
				xstep= + (_elem->getW3())/2;
				ystep=0;
			} else if(_net==3) {
				Wlong= (_elem->getW1()>_elem->getW2()) ? _elem->getW1() : _elem->getW2();
				xstep=0;
				ystep= + (Wlong)/2;
				}
		} else if(_elem->getMirrorx()==0 && _elem->getR()==90) {
			if(_net==1) {
				xstep=0;
				ystep= + (_elem->getW3())/2;
			} else if(_net==2) {
				xstep=0;
				ystep= - (_elem->getW3())/2;
			} else if(_net==3) {
				Wlong= (_elem->getW1()>_elem->getW2()) ? _elem->getW1() : _elem->getW2();
				xstep= + (Wlong)/2;
				ystep=0;
				}
		} else if(_elem->getMirrorx()==0 && _elem->getR()==180) {
			if(_net==1) {
				xstep= + (_elem->getW3())/2;
				ystep=0;
			} else if(_net==2) {
				xstep= - (_elem->getW3())/2;
				ystep=0;
			} else if(_net==3) {
				Wlong= (_elem->getW1()>_elem->getW2()) ? _elem->getW1() : _elem->getW2();
				xstep=0;
				ystep= - (Wlong)/2;
				}
		} else if(_elem->getMirrorx()==0 && _elem->getR()==270) {
			if(_net==1) {
				xstep=0;
				ystep= - (_elem->getW3())/2;
			} else if(_net==2) {
				xstep=0;
				ystep= + (_elem->getW3())/2;
			} else if(_net==3) {
				Wlong= (_elem->getW1()>_elem->getW2()) ? _elem->getW1() : _elem->getW2();
				xstep= - (Wlong)/2;
				ystep=0;
				}
		} else if(_elem->getMirrorx()==1 && _elem->getR()==0) {
			if(_net==1) {
				xstep= - (_elem->getW3())/2;
				ystep=0;
			} else if(_net==2) {
				xstep= + (_elem->getW3())/2;
				ystep=0;
			} else if(_net==3) {
				Wlong= (_elem->getW1()>_elem->getW2()) ? _elem->getW1() : _elem->getW2();
				xstep=0;
				ystep= - (Wlong)/2;
				}
		} else if(_elem->getMirrorx()==1 && _elem->getR()==90) {
			if(_net==1) {
				xstep=0;
				ystep= + (_elem->getW3())/2;
			} else if(_net==2) {
				xstep=0;
				ystep= - (_elem->getW3())/2;
			} else if(_net==3) {
				Wlong= (_elem->getW1()>_elem->getW2()) ? _elem->getW1() : _elem->getW2();
				xstep= - (Wlong)/2;
				ystep=0;
				}
		} else if(_elem->getMirrorx()==1 && _elem->getR()==180) {
			if(_net==1) {
				xstep= + (_elem->getW3())/2;
				ystep=0;
			} else if(_net==2) {
				xstep= - (_elem->getW3())/2;
				ystep=0;
			} else if(_net==3) {
				Wlong= (_elem->getW1()>_elem->getW2()) ? _elem->getW1() : _elem->getW2();
				xstep=0;
				ystep= + (Wlong)/2;
				}
		} else if(_elem->getMirrorx()==1 && _elem->getR()==270) {
			if(_net==1) {
				xstep=0;
				ystep= - (_elem->getW3())/2;
			} else if(_net==2) {
				xstep=0;
				ystep= + (_elem->getW3())/2;
			} else if(_net==3) {
				Wlong= (_elem->getW1()>_elem->getW2()) ? _elem->getW1() : _elem->getW2();
				xstep= + (Wlong)/2;
				ystep=0;
				}
			}
		}
	return(0);
	}

