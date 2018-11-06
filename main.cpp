/***************************************************************************
                               main.cpp
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

#include <iostream>

//#include "element.h"
#include "parser.h"
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
	bool verbose=false;
	int nelem=0;
	string n_sch="";
	string out_format=".kicad_pcb";
	Element** tab_all;


//argument parser
	for(int i=0;i<argc;i++) {
		if(string(argv[i])=="-h" || string(argv[i])=="--help"){
			cout << "Usage: " << argv[0] << " -i FILENAME.sch" << endl
				<< "       " << argv[0] << " -i FILENAME.sch -f [.kicad_pcb|.kicad_mod]" << endl
				<< endl
				<< "  -h, --help\tdisplay this help and exit" << endl
				<< "  -v, --verbose\tverbose mode" << endl
				<< "  -i FILENAME\tuse file as input schematic" << endl
				<< "  -f FORMAT\tuse format as output layout format" << endl
				<< "\t\tFORMAT can be:" << endl
				<< "\t\t- .kicad_pcb\t: kicad layout" << endl
				<< "\t\t- .kicad_mod\t: kicad module" << endl
				<< "\t\t- .lht\t\t: pcb-rnd layout" << endl;
			exit(0);
			}
		if(string(argv[i])=="-i" && argv[i+1]) {
			i++;
			n_sch=string(argv[i]);
			}
		if(string(argv[i])=="-f" && argv[i+1]) {
			i++;
			if(string(argv[i])==".kicad_pcb"
			|| string(argv[i])==".kicad_mod") {
				out_format=string(argv[i]);
			} else {
				cerr << "ERROR : Invalid output format : " << argv[i] << endl;
				exit(1);
				}
			}
		if(string(argv[i])=="-v" || string(argv[i])=="--verbose") {
			verbose=true;
			}
		}

	if(n_sch=="") {
		cerr << "ERROR : Need an input file" << endl;
		exit(1);
		}
	if(!verbose) {
		cout.rdbuf(NULL);
		}



//parse files : create objects
	parser(tab_all, n_sch, nelem);

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
		}
	delete[] tab_all;
	return(0);
}
