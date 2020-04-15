/***************************************************************************
                               main.cpp
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

#include <QApplication>

#include <iostream>

#include "data.hpp"
#include "converter.hpp"
#include "logger.hpp"
#include "mainwindow.hpp"
#include "version.hpp"

using namespace std;

//	USAGE
//	./qucs-rflayout
//			-h --help
//			-v 
//			-i schematic.sch
//			-f .output_format
//			-o output/directory
//			-G gui

#ifdef QRFL_UNITTEST
#define main not_main
#endif // QRFL_UNITTEST

int main(int argc, char* argv[]) {

//variables
	bool verbose=false;
	bool gui=false;
	Data data;
	data.n_sch="";
	data.out_dir="";
	data.out_format=".kicad_pcb";

//argument parser
	for(int i=0;i<argc;i++) {
		if(string(argv[i])=="-h" || string(argv[i])=="--help") {
			cout << "Usage: " << argv[0] << " -i FILENAME.sch" << endl
			     << "       " << argv[0] << " -i FILENAME.sch -f [.kicad_pcb|.kicad_mod|.lht]" << endl
			     << "       " << argv[0] << " -i FILENAME.sch -f [.kicad_pcb|.kicad_mod|.lht] -o DIRNAME" << endl
			     << "       " << argv[0] << " -G" << endl
			     << endl
			     << "  -h, --help\tdisplay this help and exit" << endl
			     << "      --version\tdisplay version information and exit" << endl
			     << "  -v, --verbose\tverbose mode" << endl
			     << "  -G\t\tGUI mode (no arguments equals to -G)" << endl
			     << "  -i FILENAME\tuse file as input schematic" << endl
			     << "  -o DIRNAME\tuse directory as output" << endl
			     << "  -f FORMAT\tuse format as output layout format" << endl
			     << "\t\tFORMAT can be:" << endl
			     << "\t\t- .kicad_pcb\t: kicad layout (default format)" << endl
			     << "\t\t- .kicad_mod\t: kicad module" << endl
			     << "\t\t- .lht\t\t: pcb-rnd layout" << endl
			     << "\t\t- .m\t\t: openems octave script" << endl;
			exit(0);
			}
		if(string(argv[i])=="--version") {
			cout << "Qucs-RFlayout " << VERSION << endl;
			exit(0);
			}
		if(string(argv[i])=="-i" && argv[i+1]) {
			i++;
			data.n_sch=string(argv[i]);
			}
		if(string(argv[i])=="-o" && argv[i+1]) {
			i++;
			data.out_dir=string(argv[i]);
			}
		if(string(argv[i])=="-f" && argv[i+1]) {
			i++;
			if(string(argv[i])==".kicad_pcb"
			|| string(argv[i])==".kicad_mod"
			|| string(argv[i])==".lht"
			|| string(argv[i])==".m") {
				data.out_format=string(argv[i]);
			} else {
				log_err << "ERROR : Invalid output format : " << argv[i] << "\n";
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
		cout.rdbuf(nullptr);
		}

	if(gui) {
		log_err << "GUI mode\n";
		QApplication a(argc, argv);
		MainWindow w(data);
		log_err.obj=&w;
		log_err.set_mode(gui);
		w.show();
		return(a.exec());

	} else {

		if(data.n_sch=="") {
			log_err << "ERROR : Need an input file\n";
			exit(1);
			}

		Converter converter(data);

		int ret=converter.run();
		if(ret) exit(ret);

		cout << endl;
		}
	return(0);
	}

#ifdef QRFL_UNITTEST
#undef main
#endif // QRFL_UNITTEST
