#include <iostream>
#include <fstream>
#include <regex>

//#include "element.h"
#include "parser4.h"
#include "xycalculator.h"
#include "layoutwriter.h"

using namespace std;

//	USAGE
//	./qucs-rflayout
//			-h --help
//			-v 
//			-i schematic.sch
//			-f output_format
//			-o layout.output_format

int main(int argc, char* argv[]) {

//variables
	int nelem=0;
	string n_sch;
	string out_format=".kicad_pcb";
	Element** tab_all;


//read arguments
//	cout << endl;
//	cout << "argc = " << argc << endl;
//	for(int i=0; i<argc; i++) {
//		cout << "argv[" << i << "] = " << argv[i] << endl;
//		}

//parse arguments
//optarg
	cout << endl;
	if(argc!=2){
		cout << "Problem with arguments, please read help" << endl << argv[0] << " --help" << endl << endl;
		return(1);
		}
	if(string(argv[1])=="--help" || string(argv[1])=="-h"){
		cout << "Usage : " << argv[0] << " /path/to/qucs/schematic.sch" << endl << endl;
		return(0);
	} else {
		n_sch=string(argv[1]);
		}
//	if verbose
//		streambuf* buffer;
//		cout.rdbuf(buffer);



//parse files : create objects
	parser4(tab_all, n_sch, nelem);

//print
/*	cout << endl << "nelem : " << nelem << endl;
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
*/

//algorithm : find xy
	xycalculator(tab_all, nelem);
	cout << endl;
	for(int ielem=0;ielem<nelem;ielem++) {
		cout << "tab_all[" << ielem << "] Label : " << tab_all[ielem]->getLabel() << endl;
		cout << "tab_all[" << ielem << "] X : " << tab_all[ielem]->getX() << endl;
		cout << "tab_all[" << ielem << "] Y : " << tab_all[ielem]->getY() << endl;
		}

//write layout
	layoutwriter(tab_all, nelem, n_sch, out_format);

//objects destruction
	cout << endl;
	for(int ielem=0;ielem<nelem;ielem++) {
		delete tab_all[ielem];
//		cout << "tab_all[" << ielem << "] : deleted" << endl;
		}
	delete[] tab_all;
//	cout << "tab_all : deleted" << endl;

	return(0);
}
