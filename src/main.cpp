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

#ifdef QRFL_UNITTEST
#define main not_main
#endif // QRFL_UNITTEST

int main(int argc, char* argv[]) {

//variables
	bool verbose=false;
	bool gui=false;
	Data data;

//argument parser
	for(int i=0;i<argc;i++) {
		if(string(argv[i])=="-h" || string(argv[i])=="--help") {
			cout << "Usage: " << argv[0] << " -i FILENAME.sch\n"
			        "       " << argv[0] << " -i FILENAME.sch -f [.kicad_pcb|.kicad_mod|.lht]\n"
			        "       " << argv[0] << " -i FILENAME.sch -f [.kicad_pcb|.kicad_mod|.lht] -o DIRNAME\n"
			        "       " << argv[0] << " -G\n"
			        "\n"
			        "  -h, --help\tdisplay this help and exit.\n"
			        "      --version\tdisplay version information and exit.\n"
			        "  -v, --verbose\tverbose mode.\n"
			        "  -G\t\tGUI mode (no arguments equals to -G).\n"
			        "  -i FILENAME\tuse file as input schematic.\n"
			        "  -o DIRNAME\tuse directory as output.\n"
			        "  -f FORMAT\tuse format as output layout format.\n"
			        "\t\tFORMAT can be:\n"
			        "\t\t- .kicad_pcb\t: kicad layout (default format)\n"
			        "\t\t- .kicad_mod\t: kicad module\n"
			        "\t\t- .lht\t\t: pcb-rnd layout\n"
			        "\t\t- .m\t\t: openems octave script\n"
			        "  -s\t\texport each substrate in a different file.\n"
			        "  -b\t\texport each block in a different file.\n"
			        "\n"
			        "      --margin-factor INTEGER\t\tThe distance between circuits and substrate edges.\n"
			        "                             \t\tis defined as a substrate height multiple. Default is 10.\n"
			        "      --oems-highres-div INTEGER\tOpenEMS high resolution mesh lambda divisor. Default is 200.\n"
			        "      --oems-metalres-div INTEGER\tOpenEMS metal resolution mesh lambda divisor. Default is 60.\n"
			        "      --oems-substres-div INTEGER\tOpenEMS substrate resolution mesh lambda divisor. Default is 30.\n"
			        "      --oems-timeres INTEGER\t\tNumber of timesteps before OpenEMS stops simulation.\n"
			        "      --port-shift N X Y\t\tTranslate a port. X grows to the right, Y grows to the bottom.\n"
			        "      --port-size N L W\t\t\tSet a port size. L is in x axis, W in y axis.\n"
			        "                       \t\t\tCan be used with '--port-shift' to create designs such as\n"
			        "                       \t\t\tcenter fed patch antenna.\n";
			return(0);
			}
		if(string(argv[i])=="--version") {
			cout << "Qucs-RFlayout " << VERSION << endl;
			return(0);
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
				return(1);
				}
			}
		if(string(argv[i])=="-s") {
			data.export_each_subst=true;
			}
		if(string(argv[i])=="-b") {
			data.export_each_block=true;
			}
		if(string(argv[i])=="--margin-factor" && argv[i+1]) {
			i++;
			data.subst_margin_factor=atoi(argv[i]);
			}
		if(string(argv[i])=="--oems-highres-div" && argv[i+1]) {
			i++;
			data.oems_highres_div=atoi(argv[i]);
			}
		if(string(argv[i])=="--oems-metalres-div" && argv[i+1]) {
			i++;
			data.oems_metalres_div=atoi(argv[i]);
			}
		if(string(argv[i])=="--oems-substres-div" && argv[i+1]) {
			i++;
			data.oems_substres_div=atoi(argv[i]);
			}
		if(string(argv[i])=="--oems-timeres" && argv[i+1]) {
			i++;
			data.oems_timeres=atoi(argv[i]);
			}
		if(string(argv[i])=="--port-shift" && argv[i+1] && argv[i+2] && argv[i+3]) {
			i++;
			data.port_shift_args.push_back(make_tuple(stoul(string(argv[i])), string(argv[i+1]), string(argv[i+2])));
			i+=2;
			}
		if(string(argv[i])=="--port-size" && argv[i+1] && argv[i+2] && argv[i+3]) {
			i++;
			data.port_size_args.push_back(make_tuple(stoul(string(argv[i])), string(argv[i+1]), string(argv[i+2])));
			i+=2;
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
		// Avoid a stold() bug introduced by QApplication() performing setlocale(LC_ALL, "")
		setlocale(LC_NUMERIC, "C");
		MainWindow w(data);
		log_err.obj=&w;
		log_err.set_mode(gui);
		w.show();
		return(a.exec());

	} else {

		if(data.n_sch=="") {
			log_err << "ERROR : Need an input file\n";
			return(1);
			}

		Converter converter(data);

		int ret=converter.run();
		if(ret) return(ret);

		cout << endl;
		}
	return(0);
	}

#ifdef QRFL_UNITTEST
#undef main
#endif // QRFL_UNITTEST
