#include "xycalculator.h"
using namespace std;

int xycalculator(Element** tab_all, int &nelem) {

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
//	long double x=0;
//	long double y=0;
	int nundone=nelem;
	int nnets;
	int current_net=0;
//	int ielem=0;
	current->setX(0);
	current->setY(0);

//test
//	for(int i=0;i<nelem;i++) {
//		cout << "tab_undone[" << i << "]->prev : " << tab_undone[i]->prev << endl; 
//		if(tab_undone[i]->prev != NULL) {
//			cout << "tab_undone[" << i << "]->prev->getLabel() : " << tab_undone[i]->prev->getLabel() << endl;
//			}
//		}
//
//	tab_undone[2]=NULL;

//print address
	cout << "&tab_all : " << tab_all << endl;
	for(int i=0;i<nelem;i++) {
		cout << "&tab_all[" << i << "] : " << tab_all[i] << endl; 
		}
	cout << "&tab_undone : " << tab_undone << endl;
	for(int i=0;i<nelem;i++) {
		cout << "&tab_undone[" << i << "] : " << tab_undone[i] << endl; 
		}

	purgenets(tab_all, nelem);	

	while(nundone) {
		nnets=activenets(current);
		cout << endl;
		cout << "nundone : " << nundone << endl;
		cout << "current label : " << current->getLabel() << endl;
		cout << "current nnets : " << nnets << endl;
		if(nnets==0) {
			tab_remove(tab_undone, nundone, nelem, current);
			if(buffer.empty()==false){
				current=buffer.top();
				buffer.pop();
			} else {
				for(int i=0;i<nelem;i++) {
					if(tab_undone[i]!=NULL) {// && tab_undone[i]!=current) {
						current=tab_undone[i];
						break;
						}
					}
				if(current->getX()!=current->getX() || current->getY()!=current->getY()) {
					current->setX((nelem-nundone)*-5);		//set a random position
					current->setY((nelem-nundone)*-5);		//
					cout << "setX : ok" << endl;
					cout << "setY : ok" << endl;
					}
				}
		} else {
			if(nnets==1) {
				tab_remove(tab_undone, nundone, nelem, current);
			} else {
				buffer.push(current);
				}
			current_net=netmin(current);
			cout << "current_net : " << current_net << endl;
			xystep(current, current_net, prev_xstep, prev_ystep);
//			cout << "prev_xstep : " << prev_xstep << endl;
//			cout << "prev_ystep : " << prev_ystep << endl;
			findnext(tab_all, nelem, current, current_net, next);
			cout << "next label : " << next->getLabel() << endl;
			next->prev=current;
			current=next;
			next=NULL;
			if(current->getX()!=current->getX() || current->getY()!=current->getY()) {		//if position is -NaN
				xystep(current, current_net, current_xstep, current_ystep);
//				current_xstep*=-1;		//from port to center
//				current_ystep*=-1;
				cout << "prev_xstep : " << prev_xstep << endl;
				cout << "prev_ystep : " << prev_ystep << endl;
				cout << "current_xstep : " << -1*current_xstep << endl;
				cout << "current_ystep : " << -1*current_ystep << endl;
//				cout << "prev_x : " << current->prev->getX() << endl;
//				cout << "prev_y : " << current->prev->getY() << endl;
/*				x=current->prev->getX();
				x+=prev_xstep;
				x+=current_xstep;
				y=current->prev->getY();
				y+=prev_ystep;
				y+=current_ystep;
				cout << "x : " << x << endl;
				cout << "y : " << y << endl;
				cout << "to_string(x) : " << to_string(x) << endl;
				cout << "to_string(y) : " << to_string(y) << endl;
*/				current->setX((current->prev->getX())+(prev_xstep)-(current_xstep));
				current->setY((current->prev->getY())+(prev_ystep)-(current_ystep));
//				current->setX(x);
//				current->setY(y);
				cout << "X : " << current->getX() << endl;
				cout << "Y : " << current->getY() << endl;
				}
			}
		}

	delete[] tab_undone;
	return(0);
	}

int tab_remove(Element** tab_undone, int &nundone, int &nelem, Element* current) {
	for(int i=0;i<nelem;i++) {
		if(tab_undone[i]==current) {
			tab_undone[i]=NULL;
			nundone--;
			break;
			}
		}
	return(0);
	}

bool purgefind(Element** tab_all, int &nelem, Element* current, string _net) {
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

int purgenets(Element** tab_all, int &nelem) {
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

int activenets(Element* _elem) {
	int nlinks=0;
	if(_elem->getNet1()!="") nlinks++;
	if(_elem->getNet2()!="") nlinks++;
	if(_elem->getNet3()!="") nlinks++;
	if(_elem->getNet4()!="") nlinks++;
	return(nlinks);
	}

int netmin(Element* _elem) {
	if(_elem->getNet1()!="") return(1);
	if(_elem->getNet2()!="") return(2);
	if(_elem->getNet3()!="") return(3);
	if(_elem->getNet4()!="") return(4);
	return(0);
	}

int findnext(Element** tab_all, int& nelem, Element* current, int& current_net, Element*& next) {
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
				cout << "next net : 1" << endl;
				next=tab_all[i];
				tab_all[i]->setNet1("");
				current_net=1;
				break;
			} else if(tab_all[i]->getNet2()==_net) {
				cout << "next net : 2" << endl;
				next=tab_all[i];
				tab_all[i]->setNet2("");
				current_net=2;
				break;
			} else if(tab_all[i]->getNet3()==_net) {
				cout << "next net : 3" << endl;
				next=tab_all[i];
				tab_all[i]->setNet3("");
				current_net=3;
				break;
			} else if(tab_all[i]->getNet4()==_net) {
				cout << "next net : 4" << endl;
				next=tab_all[i];
				tab_all[i]->setNet4("");
				current_net=4;
				break;
				}
			}
		}
	return(0);
	}

int xystep(Element* _elem, int _net, long double& xstep, long double& ystep) {
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

