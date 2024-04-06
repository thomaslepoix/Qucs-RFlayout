/***************************************************************************
                               schparser.cpp
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

#include <QProcess>

#include <array>
#include <iostream>
#include <regex>
#include <string>
#include <tuple>

#include "logger.hpp"
#include "microstrip/microstrip.hpp"
#include "schparser.hpp"
using namespace std;

//******************************************************************************
SchParser::SchParser(Data& _data) :
	data(_data)
	{}

//******************************************************************************
int SchParser::run() {
	int ret;
	string n_sch;
	string n_net;
	string n_dat;
	ifstream f_sch;
	ifstream f_net;
	ifstream f_dat;
	vector<string> unprintables;
	vector<pair<string, long double>> variables;
	static regex const r_sch("\\.sch$");

	// Filenames processing
	cout << endl;
	if(regex_search(data.n_sch, r_sch)) {
		n_net=regex_replace(data.n_sch, r_sch, ".net");
		n_sch=regex_replace(data.n_sch, r_sch, ".tmp.sch");
	} else {
		log_err << "ERROR : Invalid input format : " << data.n_sch << "\n";
		return(1);
		}

	cout << "Schematic file : " << data.n_sch << endl;
	f_sch.open(data.n_sch.c_str());
	if(f_sch.fail()) {
		log_err << "ERROR : Cannot open " << data.n_sch << "\n";
		return(1);
		}

	bool is_qucsstudio=false;
	ret=check_qucsstudio(f_sch, n_sch, is_qucsstudio);
	if(ret)
		return(ret);

	if(data.n_net=="") {
		ret=generate_netlist(n_sch, n_net);
		if(ret)
			return(ret);
	} else {
		n_net=data.n_net;
		}

	cout << "Netlist file : " << n_net << endl;
	f_net.open(n_net.c_str());
	if(f_net.fail()) {
		log_err << "ERROR : Cannot open " << n_net << "\n";
		return(1);
		}

	bool is_there_eqn;
	parse_schematic_datafile(f_sch, n_dat, is_there_eqn);

	f_dat.open(n_dat.c_str());
	if(f_dat.fail()) {
		if(is_there_eqn) {
			log_err << "WARNING : Cannot open " << n_dat <<
			           ". Not problematic if variables and equations are not used."
			           " Otherwise, try to run a simulation to produce it.\n";
			}
	} else {
		cout << "Data file : " << n_dat << endl;
		parse_data(f_dat, variables);
		}

	parse_schematic_components(f_sch, variables, unprintables);
	parse_netlist(f_net);

	parse_port_shift_args();
	parse_port_size_args();

	cout << "Number of elements : " << data.tab_all.size() << endl;
	warn_unprintable(unprintables);

	f_sch.close();
	f_net.close();
	f_dat.close();
	// Remove QucsStudio temporary schematic and automatically generated netlist
	rm_tmp_files({ (is_qucsstudio ? n_sch : ""), (data.n_net=="" ? n_net : "") });
	return(0);
	}

// Uncomplete feature. Could be usable on every elements
// TODO why does if function without getP update?
//******************************************************************************
void SchParser::parse_port_shift_args() {
	for(tuple<unsigned long, string, string> arg : data.port_shift_args) {
		bool is_port_existant=false;
		for(shared_ptr<Element> element : data.tab_all) {
			if(element->getType()=="Pac") {
				if(element->getN()==get<0>(arg)) {
					smatch match;

					// g1 value    g2 suffix    g3 scientific    g4 engineer
					// Cares about negatives
					static regex const r_port_shift_arg("((?:-?|\\+?)[0-9.]*)(([eE]-?[0-9]+)? ?([EPTGMkmunpfa]?(?:m?|(?:Hz)|(?:Ohm)?|(?:dBm)?))?)");

					regex_search(get<1>(arg), match, r_port_shift_arg);
					element->setShiftX(stold(check_void(match.str(1)))*suffix(match.str(3), match.str(4), true));
					regex_search(get<2>(arg), match, r_port_shift_arg);
					element->setShiftY(stold(check_void(match.str(1)))*suffix(match.str(3), match.str(4), true));

					is_port_existant=true;
					break;
					}
				}
			}
		if(!is_port_existant) {
			log_err << "WARNING : '--port-shift " << get<0>(arg) << " " << get<1>(arg) << " " << get<2>(arg)
			        << "' Port '" << get<0>(arg) << "' does not exist -> Ignored\n";
			}
		}
	}

//******************************************************************************
void SchParser::parse_port_size_args() {
	for(tuple<unsigned long, string, string> arg : data.port_size_args) {
		bool is_port_existant=false;
		for(shared_ptr<Element> element : data.tab_all) {
			if(element->getType()=="Pac") {
				if(element->getN()==get<0>(arg)) {
					smatch match;

					// g1 value    g2 suffix    g3 scientific    g4 engineer
					// Does not care about negatives
					static regex const r_port_size_arg("(\\+?[0-9.]*)(([eE]-?[0-9]+)? ?([EPTGMkmunpfa]?(?:m?|(?:Hz)|(?:Ohm)?|(?:dBm)?))?)");

					regex_search(get<1>(arg), match, r_port_size_arg);
					element->setL(stold(check_void(match.str(1)))*suffix(match.str(3), match.str(4), true));
					regex_search(get<2>(arg), match, r_port_size_arg);
					element->setW(stold(check_void(match.str(1)))*suffix(match.str(3), match.str(4), true));

					dynamic_cast<Pac*>(element.get())->is_size_set=true;
					is_port_existant=true;
					break;
					}
				}
			}
		if(!is_port_existant) {
			log_err << "WARNING : '--port-size " << get<0>(arg) << " " << get<1>(arg) << " " << get<2>(arg)
			        << "' Port '" << get<0>(arg) << "' does not exist -> Ignored\n";
			}
		}
	}

//******************************************************************************
int SchParser::check_qucsstudio(ifstream& f_sch, string& n_tmp, bool& is_qucsstudio) const {
	string line;
	smatch match;

	// g1 software    g2 major
	static regex const r_head("^<(Qucs(?:Studio)?) Schematic ([0-9]+)\\.[0-9]+\\.[0-9]+>$");

	// g1 begin    g2 x    g3 y    g4 end    g5 r
	static regex const r_mstub("^  <MSTUB((?: [^ ]+){2} )(-?[0-9]+) (-?[0-9]+)((?: [^ ]+){3} ([0123])[^>]+>$)");


	getline(f_sch, line);
	regex_search(line, match, r_head);
	if(match.str(1)=="Qucs") {
		n_tmp=data.n_sch; // f_sch is ok, reset n_tmp to its filename
	} else if(match.str(1)=="QucsStudio") {
		if(stoi(match.str(2))>=3) {
			log_err << "ERROR : QucsStudio 3.x and newer are not supported.\n";
			return(1);
			}

		// QucsStudio does not provide command line to produce netlist
		// so, as formats are mostly compatible, let's try to replace the
		// header and use Qucs instead
		is_qucsstudio=true;
		log_err << "WARNING : " << data.n_sch << " is a QucsStudio schematic, compatibility is not guaranteed\n";

		cout << "Conversion to Qucs format... ";
		ofstream f_tmp(n_tmp.c_str());
		if(f_tmp.fail()) {
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
		cout << "Temporary schematic file : " << n_tmp << endl;

		f_tmp.close();
		f_sch.close();
		f_sch.open(n_tmp.c_str());
		if(f_sch.fail()) {
			log_err << "ERROR : Cannot open " << n_tmp << "\n";
			return(1);
			}
	} else {
		log_err << "ERROR : " << data.n_sch << " appears to be neither a Qucs nor a QucsStudio schematic\n";
		return(1);
		}
	return(0);
	}

//******************************************************************************
int SchParser::generate_netlist(string const& n_sch, string const& n_net) const {
	static constexpr array<string, 2> to_try{"qucs", "qucs-s"};
	string const args=" -n -i \""+n_sch+"\" -o \""+n_net+"\"";
	bool is_done=false;

	auto const run_qucs=[&](string const& binary) {
		cout << "Trying " + binary + "... " ;
		QProcess process_qucs;
		process_qucs.startCommand(QString::fromStdString(binary + args));
		if(!process_qucs.waitForFinished() || process_qucs.exitCode()) {
			cout << "KO" << endl;
			return(false);
		} else {
			cout << "OK" << endl;
			is_done=true;
			return(true);
			}
		};

	cout << endl << "Generating netlist... " << endl;
	if(!data.qucs_binary.empty()) {
		run_qucs(data.qucs_binary);
	} else {
		for(auto& binary : to_try) {
			if(run_qucs(binary))
				break;
			}
		}

	if(is_done) {
		cout << "Generating netlist... OK" << endl;
		return(0);
	}

	log_err << "ERROR : Problem calling Qucs for generating netlist\n";
	return(2);
	}

//******************************************************************************
long double SchParser::process_field(vector<pair<string, long double>> const& variables, string const variable, string const value, string const s_sci, string const s_eng, string const label, bool const is_length) const {
	if(variable!="") {
		for(pair<string, long double> it : variables) {
			if(it.first==variable) {
				return(it.second*(is_length ? 1000 : 1));
				}
			}
		log_err << "WARNING : Variable not found in component " << label << " : " << variable << " -> Assigned to 0. Try to start a simulation.\n";
		return(0);
	} else {
		return(stold(check_void(value, label))*suffix(s_sci, s_eng, is_length));
		}
	}

//******************************************************************************
void SchParser::parse_data(std::ifstream& f_dat, vector<pair<string, long double>>& variables) const {
	string line;
	string text;
	smatch match;
	static regex const r_indep("^<indep (.*) 1>$");

	// g1 variable    g2 "()"    g3 value    g4 scientific
	static regex const r_variable("<indep (.*) 1>\n  ((\\+?-?[0-9.]*)(([eE](?:-?|\\+?)[0-9]+)?))\n<\\/indep>");

	cout << endl << "Reading data file... " << endl;

	// Variable are 3 lines "<indep>" blocks, so do not buffer too long
	// "<indep>" blocks as those are not variables.
	int line_count=0;
	bool is_in_block=false;
	while(getline(f_dat, line)) {
		if(regex_match(line, r_indep)) {
			line_count=0;
			is_in_block=true;
			}
		if(is_in_block && line_count<5) {
			text+=line + "\n";
			line_count++;
			}
		if(line=="</indep>") {
			if(regex_search(text, match, r_variable)) {
				variables.push_back(make_pair(match.str(1), (stold(check_void(match.str(3), match.str(1))))*suffix(match.str(4), "", false)));
				cout << "Variable : " << variables.back().first << " = " << variables.back().second << endl;
				}
			text.erase();
			is_in_block=false;
			}
		}

	cout << "Reading data file... OK" << endl;
	}

//******************************************************************************
void SchParser::parse_schematic_datafile(ifstream& f_sch, string& n_dat, bool& is_there_eqn) const {
	string line;
	smatch match;

	// g1 path    g2 absolute
	static regex const r_dat("^  <DataSet=(((?:[a-zA-Z]:)?[\\/]?).*)>$");
	static regex const r_path("^(.*\\/)[^\\/]*$");      // g1 path
	static regex const r_field1("^  <([.a-zA-Z]+)");    //regex group 1

	is_there_eqn=false;
	f_sch.seekg(0);
	while(getline(f_sch, line)) {
		if(line=="</Components>") {
			break;
			}
		if(regex_search(line, match, r_dat)) {
			if(match.str(2)=="") {
				n_dat=regex_replace(data.n_sch, r_path, "$1") + match.str(1);
			} else {
				n_dat=match.str(1);
				}
			}
		if(regex_search(line, match, r_field1) && match.str(1)=="Eqn") {
			is_there_eqn=true;
			break;
			}
		}
	f_sch.seekg(0);
	}

//******************************************************************************
void SchParser::parse_schematic_components(ifstream& f_sch, vector<pair<string, long double>>& variables, vector<string>& unprintables) {
	string line;
	smatch match;

	static regex const r_field1("^  <([.a-zA-Z]+)");    //regex group 1
	static regex const r_field2("^ ( ([^ ]+)){2}");     //regex group 2
	static regex const r_field3("^ ( ([^ ]+)){3}");     //regex group 2
	static regex const r_field8("^ ( ([^ ]+)){8}");     //regex group 2
	static regex const r_field9("^ ( ([^ ]+)){9}");     //regex group 2
	static regex const r_quotedfield10_raw("^ ( ([^ ]+)){9}( \"([^\"]*)\" [0-1]{1}){1}"); //regex group 4

	// g5 "()"    g6 value    g7 suffix    g8 scientific    g9 engineer    g10 variable
	static regex const r_quotedfield10("^ ( ([^ ]+)){9}( \"[^\"]*\" [0-1]{1}){0}( \"(([0-9.]*)(([eE](?:-?|\\+?)[0-9]+)? ?([EPTGMkmunpfa]?(?:m?|(?:Hz)|(?:Ohm)?|(?:dBm)?))?)|([^\"]*))\"){1}");
	static regex const r_quotedfield12("^ ( ([^ ]+)){9}( \"[^\"]*\" [0-1]{1}){1}( \"(([0-9.]*)(([eE](?:-?|\\+?)[0-9]+)? ?([EPTGMkmunpfa]?(?:m?|(?:Hz)|(?:Ohm)?|(?:dBm)?))?)|([^\"]*))\"){1}");
	static regex const r_quotedfield14("^ ( ([^ ]+)){9}( \"[^\"]*\" [0-1]{1}){2}( \"(([0-9.]*)(([eE](?:-?|\\+?)[0-9]+)? ?([EPTGMkmunpfa]?(?:m?|(?:Hz)|(?:Ohm)?|(?:dBm)?))?)|([^\"]*))\"){1}");
	static regex const r_quotedfield16("^ ( ([^ ]+)){9}( \"[^\"]*\" [0-1]{1}){3}( \"(([0-9.]*)(([eE](?:-?|\\+?)[0-9]+)? ?([EPTGMkmunpfa]?(?:m?|(?:Hz)|(?:Ohm)?|(?:dBm)?))?)|([^\"]*))\"){1}");
	static regex const r_quotedfield18("^ ( ([^ ]+)){9}( \"[^\"]*\" [0-1]{1}){4}( \"(([0-9.]*)(([eE](?:-?|\\+?)[0-9]+)? ?([EPTGMkmunpfa]?(?:m?|(?:Hz)|(?:Ohm)?|(?:dBm)?))?)|([^\"]*))\"){1}");
	static regex const r_quotedfield20("^ ( ([^ ]+)){9}( \"[^\"]*\" [0-1]{1}){5}( \"(([0-9.]*)(([eE](?:-?|\\+?)[0-9]+)? ?([EPTGMkmunpfa]?(?:m?|(?:Hz)|(?:Ohm)?|(?:dBm)?))?)|([^\"]*))\"){1}");

	// Read schematic <Components> </Components>
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
				} else if(type=="Pac") {
					//number
						regex_search(line, match, r_quotedfield10);
						unsigned long N=stoi(match.str(6));
						cout << "\tNumber : " << N << endl;
					//impedance
						regex_search(line, match, r_quotedfield12);
						long double Z=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, false);
						cout << "\tImpedance : " << Z << endl;
					//power
						regex_search(line, match, r_quotedfield14);
						long double P=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, false);
						cout << "\tPower : " << P << endl;
					//frequency
						regex_search(line, match, r_quotedfield16);
						long double F=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, false);
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
							long double Fstart=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, false);
							cout << "\tStart frequency : " << Fstart << endl;
						//stop frequency
							regex_search(line, match, r_quotedfield14);
							long double Fstop=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, false);
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
						long double er=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, false);
						cout << "\tRelative permittivity : " << er << endl;
					//substrate thickness
						regex_search(line, match, r_quotedfield12);
						long double H=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tSubstrate thickness : " << H << endl;
					//metal thickness
						regex_search(line, match, r_quotedfield14);
						long double T=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tMetal thickness : " << T << endl;
					//loss tangent
						regex_search(line, match, r_quotedfield16);
						long double tand=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, false);
						cout << "\tLoss tangent : " << tand << endl;
					//metal resistivity
						regex_search(line, match, r_quotedfield18);
						long double rho=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, false);
						cout << "\tMetal resistivity : " << rho << endl;
					//substrate roughness
						regex_search(line, match, r_quotedfield20);
						long double D=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, false);
						cout << "\tMetal roughness : " << D << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Subst(label, type, mirrorx, 0, er, H, T, tand, rho, D, data.subst_margin_factor)));
				} else if(type=="MCORN") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width
						regex_search(line, match, r_quotedfield12);
						long double W=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tWidth : " << W << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mcorn(label, type, active, mirrorx, R, subst, W)));
				} else if(type=="MCROSS") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width 1
						regex_search(line, match, r_quotedfield12);
						long double W1=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tWidth 1 : " << W1 << endl;
					//width 2
						regex_search(line, match, r_quotedfield14);
						long double W2=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tWidth 2 : " << W2 << endl;
					//width 3
						regex_search(line, match, r_quotedfield16);
						long double W3=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tWidth 3 : " << W3 << endl;
					//width 4
						regex_search(line, match, r_quotedfield18);
						long double W4=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tWidth 4 : " << W4 << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mcross(label, type, active, mirrorx, R, subst, W1, W2, W3, W4)));
				} else if(type=="MCOUPLED") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width
						regex_search(line, match, r_quotedfield12);
						long double W=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tWidth : " << W << endl;
					//length
						regex_search(line, match, r_quotedfield14);
						long double L=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tLength : " << L << endl;
					//space
						regex_search(line, match, r_quotedfield16);
						long double S=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tSpace : " << S << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mcoupled(label, type, active, mirrorx, R, subst, W, L, S)));
				} else if(type=="MGAP") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width 1
						regex_search(line, match, r_quotedfield12);
						long double W1=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tWidth 1 : " << W1 << endl;
					//width 2
						regex_search(line, match, r_quotedfield14);
						long double W2=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tWidth 2 : " << W2 << endl;
					//space
						regex_search(line, match, r_quotedfield16);
						long double S=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tSpace : " << S << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mgap(label, type, active, mirrorx, R, subst, W1, W2, S)));
				} else if(type=="MMBEND") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width
						regex_search(line, match, r_quotedfield12);
						long double W=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tWidth : " << W << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mmbend(label, type, active, mirrorx, R, subst, W)));
				} else if(type=="MLIN") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width
						regex_search(line, match, r_quotedfield12);
						long double W=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tWidth : " << W << endl;
					//length
						regex_search(line, match, r_quotedfield14);
						long double L=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tLength : " << L << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mlin(label, type, active, mirrorx, R, subst, W, L)));
				} else if(type=="MOPEN") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width
						regex_search(line, match, r_quotedfield12);
						long double W=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tWidth : " << W << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mopen(label, type, active, mirrorx, R, subst, W)));
				} else if(type=="MRSTUB") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//inner radius
						regex_search(line, match, r_quotedfield12);
						long double ri=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tInner radius : " << ri << endl;
					//outer radius
						regex_search(line, match, r_quotedfield14);
						long double ro=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tOuter radius : " << ro << endl;
					//alpha
						regex_search(line, match, r_quotedfield16);
						long double alpha=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, false);
						cout << "\tAlpha : " << alpha << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mrstub(label, type, active, mirrorx, R, subst, ri, ro, alpha)));
				} else if(type=="MSTEP") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width 1
						regex_search(line, match, r_quotedfield12);
						long double W1=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tWidth 1 : " << W1 << endl;
					//width 2
						regex_search(line, match, r_quotedfield14);
						long double W2=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tWidth 2 : " << W2 << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mstep(label, type, active, mirrorx, R, subst, W1, W2)));
				} else if(type=="MTEE") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width 1
						regex_search(line, match, r_quotedfield12);
						long double W1=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tWidth 1 : " << W1 << endl;
					//width 2
						regex_search(line, match, r_quotedfield14);
						long double W2=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tWidth 2 : " << W2 << endl;
					//width 3
						regex_search(line, match, r_quotedfield16);
						long double W3=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tWidth 3 : " << W3 << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mtee(label, type, active, mirrorx, R, subst, W1, W2, W3)));
				} else if(type=="MVIA") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						string subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//diameter
						regex_search(line, match, r_quotedfield12);
						long double D=process_field(variables, match.str(10), match.str(6), match.str(8), match.str(9), label, true);
						cout << "\tDiameter : " << D << endl;
					data.tab_all.push_back(shared_ptr<Element>(new Mvia(label, type, active, mirrorx, R, subst, D)));
					}
				}
			break;
			}
		}
	cout << "Reading schematic... OK" << endl;
	}

//******************************************************************************
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
						if(type=="MOPEN"
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

//******************************************************************************
void SchParser::warn_unprintable(vector<string> const& unprintables) const {
	if(unprintables.size()) {
		log_err << "WARNING : Schematic contains some unprintable transmission lines";
		for(string element : unprintables) {
			log_err << " " << element;
			if(element!=unprintables.back()) log_err << ",";
			}
		log_err << " -> Ignored\n";
		}
	}

//******************************************************************************
void SchParser::rm_tmp_files(initializer_list<string> const args) const {
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
			process_rm.startCommand(QString::fromStdString("rm"+str_cmd));
			if(!process_rm.waitForFinished() || process_rm.exitCode()) {
				log_err << "WARNING : Could not remove :" << str_log << "\n";
			} else {
				cout << "\nRemove temporary files :" << str_log << "\n";
				}
			}
		}
	}

// Convert suffix into multiplicator
//******************************************************************************
long double SchParser::suffix(string const s_sci, string const s_eng, bool const is_length) const {
	static regex  const r_sci("^[eE](-?|\\+?)([0-9]*)$");    // g1 signe    g2 exposant
	smatch match;
	long double multiplicator=1;

// Scientific suffix
	if(s_sci!="") {
		regex_search(s_sci, match, r_sci);
		if(match.str(1)=="" || match.str(1)=="+") {
			for(int i=0;i<stoi(match.str(2));i++) {
				multiplicator*=10;
				}
		} else if(match.str(1)=="-") {
			for(int i=0;i<stoi(match.str(2));i++) {
				multiplicator/=10;
				}
			}
		}

// Engineer suffix
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

//******************************************************************************
string SchParser::check_void(string const match, string const label) const {
	if(match=="") {
		if(label!="") {
			log_err << "WARNING : Void field in component " << label << " -> Assigned to 0\n";
			}
		return("0");
	} else {
		return(match);
		}
	}

//******************************************************************************
string SchParser::mstub_shift(bool const xy, string const str, string const r) const {
	if(r=="0")      return(xy ? to_string(stoi(str)-10) : str);
	else if(r=="1") return(xy ? str : to_string(stoi(str)-10));
	else if(r=="2") return(xy ? to_string(stoi(str)+10) : str);
	else if(r=="3") return(xy ? str : to_string(stoi(str)+10));
	else return(str); // Never happens
	}
