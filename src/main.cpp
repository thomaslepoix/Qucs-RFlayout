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
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef _WIN32
#include <windows.h>
#include <shellapi.h>
#endif // _WIN32

#ifndef QRFL_MINIMAL
#include <QApplication>
#endif // QRFL_MINIMAL

#include <cstdlib>
#include <iostream>

#include "data.hpp"
#include "converter.hpp"
#include "logger.hpp"
#include "mainwindow.hpp"
#include "version.hpp"

using namespace std;

#ifdef QRFL_UNITTEST
#define main not_main
#endif // QRFL_UNITTEST

//******************************************************************************
int main(int argc, char* argv[]) {

#ifdef _WIN32
	int argcw = 0;
	LPWSTR *argvw = CommandLineToArgvW(GetCommandLineW(), &argcw);
	if(!argvw) {
		log_err << "ERROR : Cannot retrieve command line arguments" << "\n";
		return(EXIT_FAILURE);
		}
#endif // _WIN32

//variables
	bool verbose=false;
	bool gui=false;
	Data data;

//argument parser
	if(argc==1) {
#ifndef QRFL_MINIMAL
		gui=true;
#endif // QRFL_MINIMAL
	} else {
		for(int i=1;i<argc;i++) {
			if(string(argv[i])=="-h" || string(argv[i])=="--help") {
				cout << "Usage: " << argv[0] << " -i FILENAME.sch\n"
				        "       " << argv[0] << " -i FILENAME.sch -f [.kicad_pcb|.kicad_mod|.lht]\n"
				        "       " << argv[0] << " -i FILENAME.sch -f [.kicad_pcb|.kicad_mod|.lht] -o DIRNAME\n"
#ifndef QRFL_MINIMAL
				        "       " << argv[0] << " -G\n"
#endif // QRFL_MINIMAL
				        "\n"
				        "  -h, --help      Display this help and exit.\n"
				        "      --version   Display version information and exit.\n"
				        "  -v, --verbose   Verbose mode.\n"
#ifndef QRFL_MINIMAL
				        "  -G              GUI mode (no arguments equals to -G).\n"
#endif // QRFL_MINIMAL
				        "  -i FILENAME     Use file as input schematic.\n"
				        "  -o DIRNAME      Use directory as output (default current directory).\n"
				        "  -f FORMAT       Use format as output layout format.\n"
				        "                  FORMAT can be:\n"
				        "                  - .kicad_pcb    : KiCad layout (default format)\n"
				        "                  - .kicad_mod    : KiCad module\n"
				        "                  - .lht          : pcb-rnd layout\n"
				        "                  - .m            : OpenEMS Octave script\n"
				        "  -n NETLIST      Specify a netlist to use instead of calling Qucs to create it from the schematic.\n"
				        "                  Useful when Qucs is not installed, if you use QucsStudio for example.\n"
				        "  -q, --qucs PATH Specify Qucs executable to call for netlist creation, otherwise qucs, then qucs-s will\n"
				        "                  be tried regarding system PATH variable. PATH can be either a relative or an absolute path.\n"
				        "                  QucsStudio cannot be used.\n"
				        "  -s              Export each substrate in a different file.\n"
				        "  -b              Export each block in a different file.\n"
				        "  -k, --keep      Keep temporary files.\n"
				        "\n"
				        "  -e, --exclude STRING               Exclude a component. Must be a component label.\n"
				        "  -u, --use STRING                   Exclude all components except the used ones. Must be a component label.\n"
				        "      --margin-factor INTEGER        The distance between circuits and substrate edges.\n"
				        "                                     is defined as a substrate height multiple. Default is 10.\n"
				        "      --port-shift N X Y             Translate a port. X grows to the right, Y grows to the bottom.\n"
				        "      --port-size N L W              Set a port size. L is in x axis, W in y axis.\n"
				        "                                     Can be used with '--port-shift' to create designs such as\n"
				        "                                     center fed patch antenna.\n"
				        "      --oems-highres-div INTEGER     OpenEMS high resolution mesh lambda divisor. Default is 200.\n"
				        "      --oems-metalres-div INTEGER    OpenEMS metal resolution mesh lambda divisor. Default is 60.\n"
				        "      --oems-substres-div INTEGER    OpenEMS substrate resolution mesh lambda divisor. Default is 30.\n"
				        "      --oems-timeres INTEGER         Number of timesteps before OpenEMS stops simulation. Default is 300000.\n"
				        "      --oems-end-criteria STRING     OpenEMS stops simulation when energy decayed to this value.\n"
				        "                                     Should stay between 1e-3 (speed) and 1e-5 (precision). Default is 1e-4.\n"
				        "      --oems-nf2ff-center STRING     Set the OpenEMS far field center. Must be a component label.\n"
				        "      --oems-sort-metalresmesh       Order metal resolution mesh lines by edge coordinate.\n"
				        "                                     Default is grouped by component label.\n"
				        "      --oems-pkg                     Look for 'openems' and 'csxcad' Octave packages. Requires properly\n"
				        "                                     packaged Octaves packages such as 'octave-openems' and 'octave-csxcad'\n"
				        "                                     from Debian repositories.\n";
				return(EXIT_SUCCESS);
			} else if(string(argv[i])=="--version") {
				cout << "Qucs-RFlayout " << VERSION
#ifdef QRFL_MINIMAL
				                         << " minimal build"
#endif // QRFL_MINIMAL
				                         << endl;
				return(EXIT_SUCCESS);
			} else if(string(argv[i])=="-i" && argv[i+1]) {
				i++;
#ifdef _WIN32
				data.n_sch=filesystem::path(argvw[i]);
#else
				data.n_sch=filesystem::path(argv[i]);
#endif // _WIN32
			} else if(string(argv[i])=="-n" && argv[i+1]) {
				i++;
#ifdef _WIN32
				data.n_net=filesystem::path(argvw[i]);
#else
				data.n_net=filesystem::path(argv[i]);
#endif // _WIN32
			} else if(string(argv[i])=="-o" && argv[i+1]) {
				i++;
#ifdef _WIN32
				data.out_dir=filesystem::path(argvw[i]);
#else
				data.out_dir=filesystem::path(argv[i]);
#endif // _WIN32
			} else if(string(argv[i])=="-f" && argv[i+1]) {
				i++;
				if(string(argv[i])==".kicad_pcb"
				|| string(argv[i])==".kicad_mod"
				|| string(argv[i])==".lht"
				|| string(argv[i])==".m") {
					data.out_format=string(argv[i]);
				} else {
					log_err << "ERROR : Invalid output format : " << argv[i] << "\n";
					return(EXIT_FAILURE);
					}
			} else if((string(argv[i])=="-q" || string(argv[i])=="--qucs") && argv[i+1]) {
				i++;
				data.qucs_binary=string(argv[i]);
			} else if(string(argv[i])=="-s") {
				data.export_each_subst=true;
			} else if(string(argv[i])=="-b") {
				data.export_each_block=true;
			} else if(string(argv[i])=="-k" || string(argv[i])=="--keep") {
				data.keep_tmp_files=true;
			} else if((string(argv[i])=="-e" || string(argv[i])=="--exclude") && argv[i+1]) {
				i++;
				data.excluded_elements.push_back(string(argv[i]));
			} else if((string(argv[i])=="-u" || string(argv[i])=="--use") && argv[i+1]) {
				i++;
				data.used_elements.push_back(string(argv[i]));
			} else if(string(argv[i])=="--margin-factor" && argv[i+1]) {
				i++;
				data.subst_margin_factor=atoi(argv[i]);
			} else if(string(argv[i])=="--port-shift" && argv[i+1] && argv[i+2] && argv[i+3]) {
				i++;
				data.port_shift_args.push_back(make_tuple(stoul(string(argv[i])), string(argv[i+1]), string(argv[i+2])));
				i+=2;
			} else if(string(argv[i])=="--port-size" && argv[i+1] && argv[i+2] && argv[i+3]) {
				i++;
				data.port_size_args.push_back(make_tuple(stoul(string(argv[i])), string(argv[i+1]), string(argv[i+2])));
				i+=2;
			} else if(string(argv[i])=="--oems-highres-div" && argv[i+1]) {
				i++;
				data.oems_highres_div=atoi(argv[i]);
			} else if(string(argv[i])=="--oems-metalres-div" && argv[i+1]) {
				i++;
				data.oems_metalres_div=atoi(argv[i]);
			} else if(string(argv[i])=="--oems-substres-div" && argv[i+1]) {
				i++;
				data.oems_substres_div=atoi(argv[i]);
			} else if(string(argv[i])=="--oems-timeres" && argv[i+1]) {
				i++;
				data.oems_timeres=atoi(argv[i]);
			} else if(string(argv[i])=="--oems-end-criteria" && argv[i+1]) {
				i++;
				data.oems_end_criteria=string(argv[i]);
			} else if(string(argv[i])=="--oems-nf2ff-center" && argv[i+1]) {
				i++;
				data.oems_nf2ff_center=string(argv[i]);
			} else if(string(argv[i])=="--oems-sort-metalresmesh") {
				data.oems_sort_metalresmesh=true;
			} else if(string(argv[i])=="--oems-pkg") {
				data.oems_pkg=true;
			} else if(string(argv[i])=="-v" || string(argv[i])=="--verbose") {
				verbose=true;
#ifndef QRFL_MINIMAL
			} else if(string(argv[i])=="-G") {
				gui=true;
#endif // QRFL_MINIMAL
			} else {
				log_err << "ERROR : Unknown argument : " << argv[i] << "\n";
				return(EXIT_FAILURE);
				}
			}
		}

	if(!verbose) {
		cout.rdbuf(nullptr);
		}

#ifndef QRFL_MINIMAL
	if(gui) {
		cout << "GUI mode\n";
		QApplication a(argc, argv);
		// Avoid a stold() bug introduced by QApplication() performing setlocale(LC_ALL, "")
		setlocale(LC_NUMERIC, "C");
		MainWindow w(data);
		log_err.obj=&w;
		log_err.set_mode(gui);
		// log_err << "WARNING : GUI and circuit preview are not up to date yet, take a look at the command line. ;)\n";
		w.show();
		return(a.exec());

	} else
#endif // QRFL_MINIMAL
	{

		if(data.n_sch=="") {
			log_err << "ERROR : Need an input file\n";
			return(EXIT_FAILURE);
			}

		Converter converter(data);

		int ret=converter.run();
		if(ret) return(ret);

		cout << endl;
		}
	return(EXIT_SUCCESS);
	}

#ifdef QRFL_UNITTEST
#undef main
#endif // QRFL_UNITTEST
