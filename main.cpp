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
#include <vector>
#include <memory>
#include <QApplication>

#include "parser.h"
#include "xycalculator.h"
#include "layoutwriter.h"
#include "mainwindow.h"

using namespace std;

//	USAGE
//	./qucs-rflayout
//			-h --help
//			-v 
//			-i schematic.sch
//			-f .output_format
//			-o output/directory
//			-G gui

int main(int argc, char* argv[]) {

//variables
	bool verbose=false;
	bool gui=false;
	string n_sch="";
	string out_dir="";
	string out_format=".kicad_pcb";

//argument parser
	for(int i=0;i<argc;i++) {
		if(string(argv[i])=="-h" || string(argv[i])=="--help"){
			cout << "Usage: " << argv[0] << " -i FILENAME.sch" << endl
				<< "       " << argv[0] << " -i FILENAME.sch -f [.kicad_pcb|.kicad_mod|.lht]" << endl
				<< "       " << argv[0] << " -i FILENAME.sch -f [.kicad_pcb|.kicad_mod|.lht] -o DIRNAME" << endl
				<< "       " << argv[0] << " -G" << endl
				<< endl
				<< "  -h, --help\tdisplay this help and exit" << endl
				<< "  -v, --verbose\tverbose mode" << endl
				<< "  -G\t\tGUI mode (no arguments equals to -G)" << endl
				<< "  -i FILENAME\tuse file as input schematic" << endl
				<< "  -o DIRNAME\tuse directory as output" << endl
				<< "  -f FORMAT\tuse format as output layout format" << endl
				<< "\t\tFORMAT can be:" << endl
				<< "\t\t- .kicad_pcb\t: kicad layout (default format)" << endl
				<< "\t\t- .kicad_mod\t: kicad module" << endl
				<< "\t\t- .lht\t\t: pcb-rnd layout" << endl;
			exit(0);
			}
		if(string(argv[i])=="-i" && argv[i+1]) {
			i++;
			n_sch=string(argv[i]);
			}
		if(string(argv[i])=="-o" && argv[i+1]) {
			i++;
			out_dir=string(argv[i]);
			}
		if(string(argv[i])=="-f" && argv[i+1]) {
			i++;
			if(string(argv[i])==".kicad_pcb"
			|| string(argv[i])==".kicad_mod"
			|| string(argv[i])==".lht") {
				out_format=string(argv[i]);
			} else {
				cerr << "ERROR : Invalid output format : " << argv[i] << endl;
				exit(1);
				}
			}
		if(string(argv[i])=="-v" || string(argv[i])=="--verbose") {
			verbose=true;
			}
		if(string(argv[i])=="-G" || argc==1) {
			gui=true;
			}
		}

	if(!verbose) {
		cout.rdbuf(NULL);
		}

	if(gui) {
		cerr << "GUI mode" << endl;
//		glutInit(&argc, argv);
		QApplication a(argc, argv);
		MainWindow w(QString::fromStdString(n_sch), QString::fromStdString(out_dir), QString::fromStdString(out_format));
		w.show();
		return a.exec();

	} else {

		if(n_sch=="") {
			cerr << "ERROR : Need an input file" << endl;
			exit(1);
			}



	//variables
		vector<shared_ptr<Element>> tab_all;
		long double extrem_pos[4]={0.0, 0.0, 0.0, 0.0};

	//parse files : create objects
		parser(tab_all, n_sch);

	//algorithm : find xy
		xycalculator(tab_all, extrem_pos);

	//write layout
		layoutwriter(tab_all, n_sch, out_dir, out_format);



	//debug
/*		for(unsigned int i=0;i<tab_all.size();i++) {
			cout << "tab_all[" << i << "] LABEL : " << tab_all[i]->getLabel() << endl;
			cout << "tab_all[" << i << "] TYPE : " << tab_all[i]->getType() << endl;
			cout << "\ttab_all[" << i << "] X : " << tab_all[i]->getX() << endl;
			cout << "\ttab_all[" << i << "] Y : " << tab_all[i]->getY() << endl;
			cout << "\ttab_all[" << i << "] MirrorX : " << tab_all[i]->getMirrorx() << endl;
			cout << "\ttab_all[" << i << "] R : " << tab_all[i]->getR() << endl;
			cout << "\ttab_all[" << i << "] W : " << tab_all[i]->getW() << endl;
			cout << "\ttab_all[" << i << "] W1 : " << tab_all[i]->getW1() << endl;
			cout << "\ttab_all[" << i << "] W2 : " << tab_all[i]->getW2() << endl;
			cout << "\ttab_all[" << i << "] W3 : " << tab_all[i]->getW3() << endl;
			cout << "\ttab_all[" << i << "] W4 : " << tab_all[i]->getW4() << endl;
			cout << "\ttab_all[" << i << "] L : " << tab_all[i]->getL() << endl;
			cout << "\ttab_all[" << i << "] D : " << tab_all[i]->getD() << endl;
			cout << "\ttab_all[" << i << "] S : " << tab_all[i]->getS() << endl;
			cout << "\ttab_all[" << i << "] Ri : " << tab_all[i]->getRi() << endl;
			cout << "\ttab_all[" << i << "] Ro : " << tab_all[i]->getRo() << endl;
			cout << "\ttab_all[" << i << "] Alpha : " << tab_all[i]->getAlpha() << endl;
			cout << "\ttab_all[" << i << "] Nport : " << tab_all[i]->getNport() << endl;
			cout << "\ttab_all[" << i << "] Net1 : " << tab_all[i]->getNet1() << endl;
			cout << "\ttab_all[" << i << "] Net2 : " << tab_all[i]->getNet2() << endl;
			cout << "\ttab_all[" << i << "] Net3 : " << tab_all[i]->getNet3() << endl;
			cout << "\ttab_all[" << i << "] Net4 : " << tab_all[i]->getNet4() << endl;
			cout << "\ttab_all[" << i << "] Npoint : " << tab_all[i]->getNpoint() << endl;
			}
*/		cout << endl;
		}
	return(0);
	}
