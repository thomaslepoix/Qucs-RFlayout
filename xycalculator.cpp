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

int xycalculator(Element** const& tab_all, int const& nelem) {

//variables
	Element** tab_undone = new Element*[nelem];
	for(int i=0;i<nelem;i++) {
		tab_undone[i]=tab_all[i];
		}

	stack<Element*> buffer;
	Element* current=tab_all[0];
	Element* next=NULL;

	long double prev_xstep=0;
	long double prev_ystep=0;
	long double current_xstep=0;
	long double current_ystep=0;
	int nundone=nelem;
	int nnets;
	int current_net=0;

//delete unconnected nets
	purgenets(tab_all, nelem);	

//first element
	current->setX(0);
	current->setY(0);
	cout << endl << "Finding positions..." << endl << endl;
	cout << "Current label : " << current->getLabel() << endl;

	while(nundone) {
		nnets=activenets(current);
		cout << "Undone elements : " << nundone << endl;
		cout << "Active nets : " << nnets << endl;
		if(nnets==0) {
			tab_remove(tab_undone, nundone, nelem, current);
			if(buffer.empty()==false){
				current=buffer.top();
				buffer.pop();
				cout << "End of a branch : Next from buffer" << endl;
				cout << endl;
				cout << "Current label : " << current->getLabel() << endl;
			} else {
				for(int i=0;i<nelem;i++) {
					if(tab_undone[i]!=NULL) {// && tab_undone[i]!=current) {
						current=tab_undone[i];
						cout << "End of a block : Next from undone elements" << endl;
						cout << endl;
						cout << "Current label : " << current->getLabel() << endl;
						break;
						}
					}
				if(current->getX()!=current->getX() || current->getY()!=current->getY()) {
					current->setX((nelem-nundone)*-5);		//set a random position
					current->setY((nelem-nundone)*-5);		//
					cout << "Random X : " << current->getX() << endl;
					cout << "Random Y : " << current->getY() << endl;
					}
				}
		} else {
			if(nnets==1) {
				tab_remove(tab_undone, nundone, nelem, current);
			} else {
				buffer.push(current);
				}
			current_net=netmin(current);
			cout << "Selected net : " << current_net << endl;
			xystep(current, current_net, prev_xstep, prev_ystep);
			findnext(tab_all, nelem, current, current_net, next);
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

	delete[] tab_undone;
	return(0);
	}

int tab_remove(Element** const& tab_undone, int& nundone, int const& nelem, Element* const& current) {
	for(int i=0;i<nelem;i++) {
		if(tab_undone[i]==current) {
			tab_undone[i]=NULL;
			nundone--;
			break;
			}
		}
	return(0);
	}

bool purgefind(Element** const& tab_all, int const& nelem, Element* const& current, string const _net) {
	for(int i=0;i<nelem;i++) {
		if(tab_all[i]!=current) {
			if(tab_all[i]->getNet1()==_net) return(1);
			if(tab_all[i]->getNet2()==_net) return(1);
			if(tab_all[i]->getNet3()==_net) return(1);
			if(tab_all[i]->getNet4()==_net) return(1);
			}
		}
	return(0);
	}

int purgenets(Element** const& tab_all, int const& nelem) {
//delete unconnected nets
	for(int i=0;i<nelem;i++) {
		for(int u=1;u<5;u++) {
			if(u==1) {
				if(purgefind(tab_all, nelem, tab_all[i], tab_all[i]->getNet1())==false) tab_all[i]->setNet1("");
			} else if(u==2) {
				if(purgefind(tab_all, nelem, tab_all[i], tab_all[i]->getNet2())==false) tab_all[i]->setNet2("");
			} else if(u==3) {
				if(purgefind(tab_all, nelem, tab_all[i], tab_all[i]->getNet3())==false) tab_all[i]->setNet3("");
			} else if(u==4) {
				if(purgefind(tab_all, nelem, tab_all[i], tab_all[i]->getNet4())==false) tab_all[i]->setNet4("");
				}
			}
		}
	return(0);
	}

int activenets(Element* const& _elem) {
	int nlinks=0;
	if(_elem->getNet1()!="") nlinks++;
	if(_elem->getNet2()!="") nlinks++;
	if(_elem->getNet3()!="") nlinks++;
	if(_elem->getNet4()!="") nlinks++;
	return(nlinks);
	}

int netmin(Element* const& _elem) {
	if(_elem->getNet1()!="") return(1);
	if(_elem->getNet2()!="") return(2);
	if(_elem->getNet3()!="") return(3);
	if(_elem->getNet4()!="") return(4);
	return(0);
	}

int findnext(Element** const& tab_all, int const& nelem, Element* const& current, int& current_net, Element*& next) {
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
	for(int i=0;i<nelem;i++) {
		if(tab_all[i]!=current) {
			if(tab_all[i]->getNet1()==_net) {
				cout << "Next net : 1" << endl;
				next=tab_all[i];
				tab_all[i]->setNet1("");
				current_net=1;
				break;
			} else if(tab_all[i]->getNet2()==_net) {
				cout << "Next net : 2" << endl;
				next=tab_all[i];
				tab_all[i]->setNet2("");
				current_net=2;
				break;
			} else if(tab_all[i]->getNet3()==_net) {
				cout << "Next net : 3" << endl;
				next=tab_all[i];
				tab_all[i]->setNet3("");
				current_net=3;
				break;
			} else if(tab_all[i]->getNet4()==_net) {
				cout << "Next net : 4" << endl;
				next=tab_all[i];
				tab_all[i]->setNet4("");
				current_net=4;
				break;
				}
			}
		}
	return(0);
	}

int xystep(Element* const& _elem, int const _net, long double& xstep, long double& ystep) {
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

