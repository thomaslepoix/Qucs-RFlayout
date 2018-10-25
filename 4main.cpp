#include <iostream>
#include <fstream>
#include <regex>
/*
#include "eqn.h"
#include "pac.h"
#include "mcorn.h"
#include "mcross.h"
#include "mcoupled.h"
#include "mgap.h"
#include "mmbend.h"
#include "mlin.h"
#include "mopen.h"
#include "mrstub.h"
#include "mstep.h"
#include "mtee.h"
#include "mvia.h"
*/
//#include "element.h"
#include "parser4.h"
#include "xycalculator.h"
#include "layoutwriter.h"

using namespace std;

int main(int argc, char* argv[]) {

//variables
	int nelem=0;
//	int ielem=0;
	string n_sch;
	string n_net;
	string out_format=".kicad_pcb";
	regex r_sch(".sch$");
	Element** tab_all;


//read arguments
	cout << endl;
	cout << "argc = " << argc << endl;
	for(int i=0; i<argc; i++) {
		cout << "argv[" << i << "] = " << argv[i] << endl;
		}

//parse arguments
	cout << endl;
	if(argc!=2){
		cout << "Problem with arguments, please read help" << endl << argv[0] << " --help" <<endl;
		return(1);
		}
	if(string(argv[1])=="--help"){
		cout << "Usage : " << argv[0] << " /path/to/qucs/schematic.sch" << endl;
		return(0);
	} else {
		n_sch=string(argv[1]);
		}

//BEGIN PARSER------------------------------------------------------------------
//open schematic
	cout << endl << "Opening " << n_sch << "... ";
	ifstream f_sch(n_sch.c_str());		//all_MS.sch
	if(f_sch) {
		cout << "OK" << endl;
		//f_sch << "bite cul chatte" << endl;
	} else {
		cout << "KO" << endl;
		return(1);
		}

//generation netlist
	cout << endl;
	if(regex_search(n_sch, r_sch)) {
		n_net=regex_replace(n_sch, r_sch, ".net");
		cout << "n_sch : " << n_sch << endl;
		cout << "n_net : " << n_net << endl;
	} else {
		cout << "ERROR : Invalid file format : " << n_sch << endl;
		return(1);
		}

	cout << endl << "Generating netlist... ";
	string net_gen="qucs -n -i "+n_sch+" -o "+n_net;
	if(system(net_gen.c_str())) {		//OK : exit status 0
		cout << " KO" << endl;
		cout << "ERROR : Problem with calling Qucs : " << net_gen << endl;
		return(2);
	} else {
		cout << " OK" << endl;
		}

//open netlist
	cout << endl << "Opening " << n_net << "... ";
	ifstream f_net(n_net.c_str());		//all_MS.net
	if(f_net) {
		cout << "OK" << endl;
	} else {
		cout << "KO" << endl;
		return(1);
		}

//parse files : create objects
	tab_all=parser4(f_sch, f_net, nelem);
//END PARSER--------------------------------------------------------------------

//print
	cout << endl << "nelem : " << nelem << endl;
	for(int ielem=0;ielem<nelem;ielem++) {
		cout << endl;
		cout << "tab_all[" << ielem << "]->label : " << tab_all[ielem]->getLabel() << endl;
		cout << "tab_all[" << ielem << "]->type : " << tab_all[ielem]->getType() << endl;
		cout << "tab_all[" << ielem << "]->mirrorx : " << tab_all[ielem]->getMirrorx() << endl;
		cout << "tab_all[" << ielem << "]->r : " << tab_all[ielem]->getR() << endl;
		cout << "tab_all[" << ielem << "]->nport : " << tab_all[ielem]->getNport() << endl;
		cout << "tab_all[" << ielem << "]->x : " << tab_all[ielem]->getX() << endl;
		cout << "tab_all[" << ielem << "]->y : " << tab_all[ielem]->getY() << endl;
		cout << "tab_all[" << ielem << "]->w : " << tab_all[ielem]->getW() << endl;
		cout << "tab_all[" << ielem << "]->w1 : " << tab_all[ielem]->getW1() << endl;
		cout << "tab_all[" << ielem << "]->w2 : " << tab_all[ielem]->getW2() << endl;
		cout << "tab_all[" << ielem << "]->w3 : " << tab_all[ielem]->getW3() << endl;
		cout << "tab_all[" << ielem << "]->w4 : " << tab_all[ielem]->getW4() << endl;
		cout << "tab_all[" << ielem << "]->l : " << tab_all[ielem]->getL() << endl;
		cout << "tab_all[" << ielem << "]->d : " << tab_all[ielem]->getD() << endl;
		cout << "tab_all[" << ielem << "]->s : " << tab_all[ielem]->getS() << endl;
		cout << "tab_all[" << ielem << "]->ri : " << tab_all[ielem]->getRi() << endl;
		cout << "tab_all[" << ielem << "]->ro : " << tab_all[ielem]->getRo() << endl;
		cout << "tab_all[" << ielem << "]->alpha : " << tab_all[ielem]->getAlpha() << endl;
		cout << "tab_all[" << ielem << "]->net1 : " << tab_all[ielem]->getNet1() << endl;
		cout << "tab_all[" << ielem << "]->net2 : " << tab_all[ielem]->getNet2() << endl;
		cout << "tab_all[" << ielem << "]->net3 : " << tab_all[ielem]->getNet3() << endl;
		cout << "tab_all[" << ielem << "]->net4 : " << tab_all[ielem]->getNet4() << endl;
		}
	cout << endl;
	cout << "&tab_all : " << tab_all << endl;
	for(int ielem=0;ielem<nelem;ielem++) {
		cout << "&tab_all[" << ielem << "] : " << tab_all[ielem] << endl;
		}

//algorithm : find xy
	xycalculator(tab_all, nelem);
	cout << endl;
	for(int ielem=0;ielem<nelem;ielem++) {
		cout << "tab_all[" << ielem << "] Label : " << tab_all[ielem]->getLabel() << endl;
		cout << "tab_all[" << ielem << "] X : " << tab_all[ielem]->getX() << endl;
		cout << "tab_all[" << ielem << "] Y : " << tab_all[ielem]->getY() << endl;
		}


//	cout << "mm: " << to_string(suffix("", "mm")) << endl;
/*	cout << endl;
	long double xstep=0;
	long double ystep=0;
	for(int i=0;i<nelem;i++) {
		cout<<tab_all[i]->getType()<<endl;
		for(int u=1;u<5;u++) {
			xstep=0;
			ystep=0;
			xystep(tab_all[i], u, xstep, ystep);
			cout<<"tab_all["<<i<<"] : net"<<u<<"\t| xstep : "<<xstep<<"\t| ystep : "<<ystep<<endl;
			}
		cout<<"--------------------------------------------------------------------------------"<<endl;
		}
*/

//write layout
	layoutwriter(tab_all, nelem, n_sch, out_format);

//objects destruction
	cout << endl;
	for(int ielem=0;ielem<nelem;ielem++) {
		delete tab_all[ielem];
		cout << "tab_all[" << ielem << "] : deleted" << endl;
		}
	delete[] tab_all;
	cout << "tab_all : deleted" << endl;

	return(0);
}
