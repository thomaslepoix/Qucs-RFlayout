/***************************************************************************
                               parser.cpp
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

#include <QProcess>

#include <iostream>
#include <regex>
#include <string>
#include <tuple>

#include "logger.hpp"
#include "microstrip/microstrip.hpp"
#include "schparser.hpp"
using namespace std;

SchParser::SchParser(Data& _data) :
	data(_data)
	{}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas" //below warning not ignorable with gcc
#pragma GCC diagnostic ignored "-Wunknown-escape-sequence" //thrown by regex strings

int SchParser::run(void) {
	int ret;
	string n_sch;
	string n_net;
	ifstream f_sch;
	ifstream f_net;
	vector<string> unprintables;
	static regex const r_sch("\.sch$");

//filenames processing
	cout << endl;
	if(regex_search(data.n_sch, r_sch)) {
		n_net=regex_replace(data.n_sch, r_sch, "\.net");
		n_sch=regex_replace(data.n_sch, r_sch, "\.tmp\.sch");
		cout << "Schematic : " << data.n_sch << endl;
	} else {
		log_err << "ERROR : Invalid input format : " << data.n_sch << "\n";
		return(1);
		}

	ret=open_file(f_sch, data.n_sch);
	if(ret) return(ret);

	bool is_qucsstudio=false;
	ret=check_qucsstudio(f_sch, n_sch, is_qucsstudio);
	if(ret) return(ret);

	if(data.n_net=="") {
		ret=generate_netlist(n_sch, n_net);
		if(ret) return(ret);
	} else {
		n_net=data.n_net;
		}

	ret=open_file(f_net, n_net);
	if(ret) return(ret);

	parse_schematic(f_sch, unprintables);
	parse_netlist(f_net);

	parse_port_shift_args();
	parse_port_size_args();

	cout << "Number of elements : " << data.tab_all.size() << endl;
	warn_unprintable(unprintables);

	// Remove QucsStudio temporary schematic and automatically generated netlist
	rm_tmp_files({ (is_qucsstudio ? n_sch : ""), (data.n_net=="" ? n_net : "") });
	return(0);
	}

void SchParser::parse_port_shift_args(void) {
	for(tuple<unsigned long, string, string> arg : data.port_shift_args) {
		bool is_port_existant=false;
		for(shared_ptr<Element> element : data.tab_all) {
			if(element->getType()=="Pac") {
				if(element->getN()==get<0>(arg)) {
					smatch match;

					// g1 value    g2 suffix    g3 scientific    g4 engineer
					// Cares about negatives
					static regex const r_port_shift_arg("([\-0-9.]*)((e-?[0-9]+)? ?([EPTGMkmunpfa]?(?:m?|(?:Hz)|(?:Ohm)?|(?:dBm)?))?)");

					regex_search(get<1>(arg), match, r_port_shift_arg);
					element->setShiftX(stold(check_void(match.str(1)))*suffix(match.str(3), match.str(4), true));
					regex_search(get<2>(arg), match, r_port_shift_arg);
					element->setShiftY(stold(check_void(match.str(1)))*suffix(match.str(3), match.str(4), true));

					is_port_existant=true;
					}
				}
			}
		if(!is_port_existant) {
			log_err << "WARNING : '--port-shift " << get<0>(arg) << " " << get<1>(arg) << " " << get<2>(arg)
			        << "' Port '" << get<0>(arg) << "' does not exist -> Ignored\n";
			}
		}
	}

void SchParser::parse_port_size_args(void) {
	for(tuple<unsigned long, string, string> arg : data.port_size_args) {
		bool is_port_existant=false;
		for(shared_ptr<Element> element : data.tab_all) {
			if(element->getType()=="Pac") {
				if(element->getN()==get<0>(arg)) {
					smatch match;

					// g1 value    g2 suffix    g3 scientific    g4 engineer
					// Does not care about negatives
					static regex const r_port_size_arg("([0-9.]*)((e-?[0-9]+)? ?([EPTGMkmunpfa]?(?:m?|(?:Hz)|(?:Ohm)?|(?:dBm)?))?)");

					regex_search(get<1>(arg), match, r_port_size_arg);
					element->setL(stold(check_void(match.str(1)))*suffix(match.str(3), match.str(4), true));
					regex_search(get<2>(arg), match, r_port_size_arg);
					element->setW(stold(check_void(match.str(1)))*suffix(match.str(3), match.str(4), true));

					dynamic_cast<Pac*>(element.get())->is_size_set=true;
					is_port_existant=true;
					}
				}
			}
		if(!is_port_existant) {
			log_err << "WARNING : '--port-size " << get<0>(arg) << " " << get<1>(arg) << " " << get<2>(arg)
			        << "' Port '" << get<0>(arg) << "' does not exist -> Ignored\n";
			}
		}
	}

int SchParser::open_file(ifstream& file, string const name) {
	cout << endl << "Opening " << name << "... ";
	file.open(name.c_str());
	if(file) {
		cout << "OK" << endl;
	} else {
		cout << "KO" << endl;
		log_err << "ERROR : Cannot open " << name << "\n";
		return(1);
		}
	return(0);
	}

int SchParser::check_qucsstudio(ifstream& f_sch, string& n_tmp, bool& is_qucsstudio) {
	string line;
	smatch match;

	static regex const r_head("^<(Qucs(?:Studio)?) Schematic [0-9]+\.[0-9]+\.[0-9]+>$"); //regex group 1

	//g1 begin    g2 x    g3 y    g4 end    g5 r
	static regex const r_mstub("^  <MSTUB((?: [^ ]+){2} )([\-0-9]+) ([\-0-9]+)((?: [^ ]+){3} ([0123])[^>]+>$)");


	getline(f_sch, line);
	regex_search(line, match, r_head);
	if(match.str(1)=="Qucs") {
		n_tmp=data.n_sch; // f_sch is ok, reset n_tmp to its filename
	} else if(match.str(1)=="QucsStudio") {
		// QucsStudio does not provide command line to produce netlist
		// so, as formats are mostly compatible, let's try to replace the
		// header and use Qucs instead
		is_qucsstudio=true;
		log_err << "WARNING : " << data.n_sch << " is a QucsStudio schematic, compatibility is not guaranteed\n";

		cout << "Conversion to Qucs format... ";
		ofstream f_tmp(n_tmp.c_str());
		if(!f_tmp) {
			log_err << "ERROR : Cannot open " << n_tmp << "\n";
			return(1);
			}

		f_tmp << "<Qucs Schematic 0.0.0>" << endl;
		while(getline(f_sch, line)) {
			// MSTUB -> MRSTUB : wire wrap point is different, excentred by 10
			if(regex_search(line, match, r_mstub)) {
				f_tmp << "  <MRSTUB" << match.str(1)
				      << mstub_shift(X, match.str(2), match.str(5))
				      << " "
				      << mstub_shift(Y, match.str(3), match.str(5))
				      << match.str(4) << endl;
			} else {
				f_tmp << line << endl;
				}
			}
		cout << "OK" << endl;
		cout << "Temporary schematic : " << n_tmp << endl;
		
		f_tmp.close();
		f_sch.close();
		open_file(f_sch, n_tmp);
	} else {
		log_err << "ERROR : " << data.n_sch << " appears to be neither a Qucs nor a QucsStudio schematic\n";
		return(1);
		}
	return(0);
	}

int SchParser::generate_netlist(string const& n_sch, string const& n_net) {
	cout << endl << "Generating netlist... ";
	string net_gen="qucs -n -i \""+n_sch+"\" -o \""+n_net+"\"";
	QProcess process_qucs;
	process_qucs.start(QString::fromStdString(net_gen));
	bool ret = process_qucs.waitForFinished();
	if(ret==false || process_qucs.exitCode()) {
		cout << "KO" << endl;
		log_err << "ERROR : Problem calling Qucs : " << net_gen << "\n";
		return(2);
	} else {
		cout << "OK" << endl;
		cout << "Netlist : " << n_net << endl;
		return(0);
		}
	}

void SchParser::parse_schematic(ifstream& f_sch, vector<string>& unprintables) {
	string line;
	smatch match;

	static regex const r_field1("^  <([.a-zA-Z]+)");                            //regex group 1
	static regex const r_field2("^ ( ([^ ]+)){2}");                             //regex group 2
	static regex const r_field3("^ ( ([^ ]+)){3}");                             //regex group 2
	static regex const r_field8("^ ( ([^ ]+)){8}");                             //regex group 2
	static regex const r_field9("^ ( ([^ ]+)){9}");                             //regex group 2
	static regex const r_quotedfield10_raw("^ ( ([^ ]+)){9}( \"([^\"]*)\" [0-1]{1}){1}"); //regex group 4

	//g5 "()"    g6 value    g7 suffix    g8 scientific    g9 engineer
	static regex const r_quotedfield10("^ ( ([^ ]+)){9}( \"[^\"]*\" [0-1]{1}){0}( \"(([0-9.]*)((e-?[0-9]+)? ?([EPTGMkmunpfa]?(?:m?|(?:Hz)|(?:Ohm)?|(?:dBm)?))?))\"){1}");
	static regex const r_quotedfield12("^ ( ([^ ]+)){9}( \"[^\"]*\" [0-1]{1}){1}( \"(([0-9.]*)((e-?[0-9]+)? ?([EPTGMkmunpfa]?(?:m?|(?:Hz)|(?:Ohm)?|(?:dBm)?))?))\"){1}");
	static regex const r_quotedfield14("^ ( ([^ ]+)){9}( \"[^\"]*\" [0-1]{1}){2}( \"(([0-9.]*)((e-?[0-9]+)? ?([EPTGMkmunpfa]?(?:m?|(?:Hz)|(?:Ohm)?|(?:dBm)?))?))\"){1}");
	static regex const r_quotedfield16("^ ( ([^ ]+)){9}( \"[^\"]*\" [0-1]{1}){3}( \"(([0-9.]*)((e-?[0-9]+)? ?([EPTGMkmunpfa]?(?:m?|(?:Hz)|(?:Ohm)?|(?:dBm)?))?))\"){1}");
	static regex const r_quotedfield18("^ ( ([^ ]+)){9}( \"[^\"]*\" [0-1]{1}){4}( \"(([0-9.]*)((e-?[0-9]+)? ?([EPTGMkmunpfa]?(?:m?|(?:Hz)|(?:Ohm)?|(?:dBm)?))?))\"){1}");
	static regex const r_quotedfield20("^ ( ([^ ]+)){9}( \"[^\"]*\" [0-1]{1}){5}( \"(([0-9.]*)((e-?[0-9]+)? ?([EPTGMkmunpfa]?(?:m?|(?:Hz)|(?:Ohm)?|(?:dBm)?))?))\"){1}");

	//read schematic <Components> </Components>
	cout << endl << "Reading schematic... " << endl;
	while(getline(f_sch, line)) {
		if(line=="<Components>") {
			cout << line << endl;

		//parse schematic
			while(getline(f_sch, line)) {
				cout << line << endl;
				if(line=="</Components>") {
					break;
					}

			//type
				regex_search(line, match, r_field1);
				string type=match.str(1);
				cout << "\tType : " << type << endl;
			//label
				regex_search(line, match, r_field2);
				string label=match.str(2);
				cout << "\tLabel : " << label << endl;
			//active
				regex_search(line, match, r_field3);
				short active=stoi(match.str(2));
				cout << "\tActive : " << active << endl;
			//mirrorx
				regex_search(line, match, r_field8);
				bool mirrorx=stoi(match.str(2));
				cout << "\tMirrorx : " << mirrorx << endl;
			//rotation
				regex_search(line, match, r_field9);
				short R=90*stoi(match.str(2));
				cout << "\tRotation : " << R << endl;

				if(data.used_elements.size()) {
					bool is_used=false;
					for(string it : data.used_elements) {
						if(label==it) {
							is_used=true;
							break;
							}
						}
					if(!is_used) {
						continue;
						}
				} else {
					bool is_excluded=false;
					for(string it : data.excluded_elements) {
						if(label==it) {
							is_excluded=true;
							break;
							}
						}
					if(is_excluded) {
						continue;
						}
					}

				if(active==0) {
					cout << "Inactive -> ignored" << endl;
					continue;
				} else if(active==2) {
					active=0; // 2 is semi-inactive (grey) state
					}

				if(type=="TLIN"
				|| type=="TAPEREDLINE"
				|| type=="TLIN4P"
				|| type=="CTLIN"
				|| type=="TWIST"
				|| type=="COAX"
				|| type=="RLCG"
				|| type=="BOND"
				|| type=="CIRCLINE"
				|| type=="RECTLINE") {
					bool absent=true;
					for(string element : unprintables) {
						if(element==type) absent=false;
						}
					if(absent) unprintables.push_back(type);
				} else if(type=="Eqn") {
					//to be complete...
					data.tab_all.push_back(shared_ptr<Element>(new Eqn(label, type, mirrorx, R)));
				} else if(type=="Pac") {
					//number
						regex_search(line, match, r_quotedfield10);
						unsigned long N=stoi(match.str(6));
						cout << "\tNumber : " << N << endl;
					//impedance
						regex_search(line, match, r_quotedfield12);
						long double Z=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), false);
						cout << "\tImpedance : " << Z << endl;
					//power
						regex_search(line, match, r_quotedfield14);
						long double P=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), false);
						cout << "\tPower : " << P << endl;
					//frequency
						regex_search(line, match, r_quotedfield16);
						long double F=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), false);
						cout << "\tFrequency : " << F << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Pac(label, type, active, mirrorx, 0, N, Z, P, F)));
				} else if(type==".SP") {
					//simulation type
						regex_search(line, match, r_quotedfield10_raw);
						string simtype=match.str(4);
						cout << "\tSimulation type : " << simtype << endl;
					if(simtype=="lin"
					|| simtype=="log") {
						//start frequency
							regex_search(line, match, r_quotedfield12);
							long double Fstart=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), false);
							cout << "\tStart frequency : " << Fstart << endl;
						//stop frequency
							regex_search(line, match, r_quotedfield14);
							long double Fstop=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), false);
							cout << "\tStop frequency : " << Fstop << endl;
						//step number
							regex_search(line, match, r_quotedfield16);
							unsigned long N=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), false);
							cout << "\tStep number : " << N << endl;
						data.tab_all.push_back(shared_ptr<Element>(new Sp(label, type, mirrorx, 0, simtype, Fstart, Fstop, N)));
					} else { // "list" & "const"
						log_err << "WARNING : " << label << " : Unsupported simulation type : " << simtype << " -> Ignored\n";
						}
				} else if(type=="SUBST") {
					//relative permittivity
						regex_search(line, match, r_quotedfield10);
						long double er=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), false);
						cout << "\tRelative permittivity : " << er << endl;
					//substrate thickness
						regex_search(line, match, r_quotedfield12);
						long double H=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tSubstrate thickness : " << H << endl;
					//metal thickness
						regex_search(line, match, r_quotedfield14);
						long double T=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tMetal thickness : " << T << endl;
					//loss tangent
						regex_search(line, match, r_quotedfield16);
						long double tand=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), false);
						cout << "\tLoss tangent : " << tand << endl;
					//metal resistivity
						regex_search(line, match, r_quotedfield18);
						long double rho=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), false);
						cout << "\tMetal resistivity : " << rho << endl;
					//substrate roughness
						regex_search(line, match, r_quotedfield20);
						long double D=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), false);
						cout << "\tMetal roughness : " << D << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Subst(label, type, mirrorx, 0, er, H, T, tand, rho, D, data.subst_margin_factor)));
				} else if(type=="MCORN") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width
						regex_search(line, match, r_quotedfield12);
						long double W=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth : " << W << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mcorn(label, type, active, mirrorx, R, subst, W)));
				} else if(type=="MCROSS") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width 1
						regex_search(line, match, r_quotedfield12);
						long double W1=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 1 : " << W1 << endl;
					//width 2
						regex_search(line, match, r_quotedfield14);
						long double W2=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 2 : " << W2 << endl;
					//width 3
						regex_search(line, match, r_quotedfield16);
						long double W3=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 3 : " << W3 << endl;
					//width 4
						regex_search(line, match, r_quotedfield18);
						long double W4=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 4 : " << W4 << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mcross(label, type, active, mirrorx, R, subst, W1, W2, W3, W4)));
				} else if(type=="MCOUPLED") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width
						regex_search(line, match, r_quotedfield12);
						long double W=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth : " << W << endl;
					//length
						regex_search(line, match, r_quotedfield14);
						long double L=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tLength : " << L << endl;
					//space
						regex_search(line, match, r_quotedfield16);
						long double S=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tSpace : " << S << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mcoupled(label, type, active, mirrorx, R, subst, W, L, S)));
				} else if(type=="MGAP") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width 1
						regex_search(line, match, r_quotedfield12);
						long double W1=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 1 : " << W1 << endl;
					//width 2
						regex_search(line, match, r_quotedfield14);
						long double W2=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 2 : " << W2 << endl;
					//space
						regex_search(line, match, r_quotedfield16);
						long double S=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tSpace : " << S << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mgap(label, type, active, mirrorx, R, subst, W1, W2, S)));
				} else if(type=="MMBEND") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width
						regex_search(line, match, r_quotedfield12);
						long double W=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth : " << W << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mmbend(label, type, active, mirrorx, R, subst, W)));
				} else if(type=="MLIN") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width
						regex_search(line, match, r_quotedfield12);
						long double W=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth : " << W << endl;
					//length
						regex_search(line, match, r_quotedfield14);
						long double L=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tLength : " << L << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mlin(label, type, active, mirrorx, R, subst, W, L)));
				} else if(type=="MOPEN") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width
						regex_search(line, match, r_quotedfield12);
						long double W=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth : " << W << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mopen(label, type, active, mirrorx, R, subst, W)));
				} else if(type=="MRSTUB") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//inner radius
						regex_search(line, match, r_quotedfield12);
						long double ri=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tInner radius : " << ri << endl;
					//outer radius
						regex_search(line, match, r_quotedfield14);
						long double ro=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tOuter radius : " << ro << endl;
					//alpha
						regex_search(line, match, r_quotedfield16);
						long double alpha=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), false);
						cout << "\tAlpha : " << alpha << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mrstub(label, type, active, mirrorx, R, subst, ri, ro, alpha)));
				} else if(type=="MSTEP") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width 1
						regex_search(line, match, r_quotedfield12);
						long double W1=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 1 : " << W1 << endl;
					//width 2
						regex_search(line, match, r_quotedfield14);
						long double W2=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 2 : " << W2 << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mstep(label, type, active, mirrorx, R, subst, W1, W2)));
				} else if(type=="MTEE") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width 1
						regex_search(line, match, r_quotedfield12);
						long double W1=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 1 : " << W1 << endl;
					//width 2
						regex_search(line, match, r_quotedfield14);
						long double W2=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 2 : " << W2 << endl;
					//width 3
						regex_search(line, match, r_quotedfield16);
						long double W3=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 3 : " << W3 << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mtee(label, type, active, mirrorx, R, subst, W1, W2, W3)));
				} else if(type=="MVIA") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//diameter
						regex_search(line, match, r_quotedfield12);
						long double D=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tDiameter : " << D << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mvia(label, type, active, mirrorx, R, subst, D)));
					}
				}
			break;
			}
		}
	cout << "Reading schematic... OK" << endl;
	}

void SchParser::parse_netlist(ifstream& f_net) {
	string line;
	smatch match;

	static regex const r_type("^([^:]*):");                   //regex group 1
	static regex const r_label("^([^:]*):([^ ]*)");           //regex group 2
	static regex const r_net1("^([^ ]* ){1}_net([0-9]*)");    //regex group 2
	static regex const r_net2("^([^ ]* ){2}_net([0-9]*)");    //regex group 2
	static regex const r_net3("^([^ ]* ){3}_net([0-9]*)");    //regex group 2
	static regex const r_net4("^([^ ]* ){4}_net([0-9]*)");    //regex group 2

	cout << endl << "Reading netlist... " << endl;
	while(getline(f_net, line)) {
		if(line=="") {
			while(getline(f_net, line)) {
				cout << line << endl;

			//type
				regex_search(line, match, r_type);
				string type=match.str(1);
				cout << "\tType : " << type << endl;
			//label
				regex_search(line, match, r_label);
				string label=match.str(2);
				cout << "\tLabel : " << label << endl;
			//find ielem->label
				for(shared_ptr<Element> it : data.tab_all) {
					if(it->getLabel()==label) {
						if(type=="Eqn"
						|| type=="SUBST"){
							//to be complete
						} else if(type=="MOPEN"
							   || type=="MRSTUB"
							   || type=="MSTUB"
							   || type=="MVIA") {
							//net 1
								regex_search(line, match, r_net1);
								string net1=match.str(2);
								cout << "\tNet 1 : " << net1 << endl;
							it->setNet1(net1);
						} else if(type=="Pac"
							   || type=="MCORN"
							   || type=="MGAP"
							   || type=="MLIN"
							   || type=="MMBEND"
							   || type=="MSTEP") {
							//net 1
								regex_search(line, match, r_net1);
								string net1=match.str(2);
								cout << "\tNet 1 : " << net1 << endl;
							//net 2
								regex_search(line, match, r_net2);
								string net2=match.str(2);
								cout << "\tNet 2 : " << net2 << endl;
							it->setNet1(net1);
							it->setNet2(net2);
						} else if(type=="MTEE") {
							//net 1
								regex_search(line, match, r_net1);
								string net1=match.str(2);
								cout << "\tNet 1 : " << net1 << endl;
							//net 2
								regex_search(line, match, r_net2);
								string net2=match.str(2);
								cout << "\tNet 2 : " << net2 << endl;
							//net 3
								regex_search(line, match, r_net3);
								string net3=match.str(2);
								cout << "\tNet 3 : " << net3 << endl;
							it->setNet1(net1);
							it->setNet2(net2);
							it->setNet3(net3);
						} else if(type=="MCOUPLED"
								||type=="MCROSS") {
							//net 1
								regex_search(line, match, r_net1);
								string net1=match.str(2);
								cout << "\tNet 1 : " << net1 << endl;
							//net 2
								regex_search(line, match, r_net2);
								string net2=match.str(2);
								cout << "\tNet 2 : " << net2 << endl;
							//net 3
								regex_search(line, match, r_net3);
								string net3=match.str(2);
								cout << "\tNet 3 : " << net3 << endl;
							//net 4
								regex_search(line, match, r_net4);
								string net4=match.str(2);
								cout << "\tNet 4 : " << net4 << endl;
							it->setNet1(net1);
							it->setNet2(net2);
							it->setNet3(net3);
							it->setNet4(net4);
							}
					// Semi-inactive (grey) components are replaced by a set of
					// R=0 in the netlist
					} else if(type=="R") {
						if(it->getLabel()+".0"==label) {
							//net 1
								regex_search(line, match, r_net1);
								string net1=match.str(2);
								cout << "\tNet 1 (" << it->getLabel() << " net 1) : " << net1 << endl;
							//net 2
								regex_search(line, match, r_net2);
								string net2=match.str(2);
								cout << "\tNet 2 (" << it->getLabel() << " net 2) : " << net2 << endl;
							if(it->getNet1()=="")
								it->setNet1(net1);
							it->setNet2(net2);
						} else if(it->getLabel()+".1"==label) {
							//net 1
								regex_search(line, match, r_net1);
								string net1=match.str(2);
								cout << "\tNet 1 (" << it->getLabel() << " net 1) : " << net1 << endl;
							//net 2
								regex_search(line, match, r_net2);
								string net2=match.str(2);
								cout << "\tNet 2 (" << it->getLabel() << " net 3): " << net2 << endl;
							if(it->getNet1()=="")
								it->setNet1(net1);
							it->setNet3(net2);
						} else if(it->getLabel()+".2"==label) {
							//net 1
								regex_search(line, match, r_net1);
								string net1=match.str(2);
								cout << "\tNet 1 (" << it->getLabel() << " net 1) : " << net1 << endl;
							//net 2
								regex_search(line, match, r_net2);
								string net2=match.str(2);
								cout << "\tNet 2 (" << it->getLabel() << " net 4): " << net2 << endl;
							if(it->getNet1()=="")
								it->setNet1(net1);
							it->setNet4(net2);
							}
						}
					}
				}
			}
		}
	cout << "Reading netlist... OK" << endl;
	}

void SchParser::warn_unprintable(vector<string> const& unprintables) {
	if(unprintables.size()) {
		log_err << "WARNING : Schematic contains some unprintable transmission lines";
		for(string element : unprintables) {
			log_err << " " << element;
			if(element!=unprintables.back()) log_err << ",";
			}
		log_err << " -> Ignored\n";
		}
	}

void SchParser::rm_tmp_files(initializer_list<string> args) {
	if(!data.keep_tmp_files) {
		QProcess process_rm;
		string str_cmd;
		string str_log;
		for(string it : args) {
			if(it!="") {
				str_cmd+=" "+it;
				str_log+="\n"+it;
				}
			}
		if(str_cmd!="") {
			process_rm.start(QString::fromStdString("rm"+str_cmd));
			bool ret = process_rm.waitForFinished();
			if(ret==false || process_rm.exitCode()) {
				log_err << "WARNING : Could not remove :" << str_log << "\n";
			} else {
				cout << "\nRemove temporary files :" << str_log << "\n";
				}
			}
		}
	}

long double SchParser::suffix(string const s_sci, string const s_eng, bool const is_length) {
//convert suffix into multiplicator
	static regex  const r_sci("^e(-?)([0-9]*)$");    //g1 signe    g2 exposant
	smatch match;
	long double multiplicator=1;

//scientific suffix
	if(s_sci!="") {
		regex_search(s_sci, match, r_sci);
		if(match.str(1)=="") {
			for(int i=0;i<stoi(match.str(2));i++) {
				multiplicator*=10;
				}
		} else if(match.str(1)=="-") {
			for(int i=0;i<stoi(match.str(2));i++) {
				multiplicator/=10;
				}
			}
		}

//engineer suffix
	if(s_eng=="E" || s_eng=="Em" || s_eng=="EHz" || s_eng=="EOhm" || s_eng=="EdBm") {
		multiplicator*=1000000000000000000;
	} else if(s_eng=="P" || s_eng=="Pm" || s_eng=="PHz" || s_eng=="POhm" || s_eng=="PdBm") {
		multiplicator*=1000000000000000;
	} else if(s_eng=="T" || s_eng=="Tm" || s_eng=="THz" || s_eng=="TOhm" || s_eng=="TdBm") {
		multiplicator*=1000000000000;
	} else if(s_eng=="G" || s_eng=="Gm" || s_eng=="GHz" || s_eng=="GOhm" || s_eng=="GdBm") {
		multiplicator*=1000000000;
	} else if(s_eng=="M" || s_eng=="Mm" || s_eng=="MHz" || s_eng=="MOhm" || s_eng=="MdBm") {
		multiplicator*=1000000;
	} else if(s_eng=="k" || s_eng=="km" || s_eng=="kHz" || s_eng=="kOhm" || s_eng=="kdBm") {
		multiplicator*=1000;
	} else if(s_eng=="" || s_eng=="Hz" || s_eng=="Ohm" || s_eng=="dBm") {
		multiplicator*=1;
	} else if(s_eng=="m" || s_eng=="mm" || s_eng=="mHz" || s_eng=="mOhm" || s_eng=="mdBm") {
		multiplicator/=1000;
	} else if(s_eng=="u" || s_eng=="um" || s_eng=="uHz" || s_eng=="uOhm" || s_eng=="udBm") {
		multiplicator/=1000000;
	} else if(s_eng=="n" || s_eng=="nm" || s_eng=="nHz" || s_eng=="nOhm" || s_eng=="ndBm") {
		multiplicator/=1000000000;
	} else if(s_eng=="p" || s_eng=="pm" || s_eng=="pHz" || s_eng=="pOhm" || s_eng=="pdBm") {
		multiplicator/=1000000000000;
	} else if(s_eng=="f" || s_eng=="fm" || s_eng=="fHz" || s_eng=="fOhm" || s_eng=="fdBm") {
		multiplicator/=1000000000000000;
	} else if(s_eng=="a" || s_eng=="am" || s_eng=="aHz" || s_eng=="aOhm" || s_eng=="adBm") {
		multiplicator/=1000000000000000000;
		}

	if(is_length)
		multiplicator*=1000; //reference unit = mm

	return(multiplicator);
	}


string SchParser::check_void(string const match, string const label) {
	if(match=="") {
		if(label!="") {
			log_err << "WARNING : Void field in component " << label << " -> Assigned to 0\n";
			}
		return("0");
	} else {
		return(match);
		}
	}

string SchParser::mstub_shift(bool const xy, string const str, string const r) {
	if(r=="0")      return(xy ? to_string(stoi(str)-10) : str);
	else if(r=="1") return(xy ? str : to_string(stoi(str)-10));
	else if(r=="2") return(xy ? to_string(stoi(str)+10) : str);
	else if(r=="3") return(xy ? str : to_string(stoi(str)+10));
	else return(str); // Never happens
	}

#pragma GCC diagnostic pop
