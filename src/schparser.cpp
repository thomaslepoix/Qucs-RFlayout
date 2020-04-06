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
#include "schparser.hpp"
using namespace std;

SchParser::SchParser(vector<shared_ptr<Element>>& _tab_all, string const& _n_sch) :
	tab_all(_tab_all),
	n_sch(_n_sch)
	{}

void SchParser::clear(void) {
	unprintables.clear();
	}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas" //below warning not ignorable with gcc
#pragma GCC diagnostic ignored "-Wunknown-escape-sequence" //thrown by regex strings

int SchParser::run(void) {

//variables
	string n_net;
	string n_tmp;
	static regex const r_sch("\.sch$");
	string line;
	smatch match;

	string type;
	string label;
	bool is_active;
	bool mirrorx;
	short R;
	string subst;
	string simtype;
	long double L;
	long double W;
	long double W1;
	long double W2;
	long double W3;
	long double W4;
	long double S;
	long double D;
	long double ri;
	long double ro;
	long double Z;
	long double P;
	long double F;
	long double er;
	long double H;
	long double T;
	long double tand;
	long double rho;
	long double Fstart;
	long double Fstop;
	unsigned long N;
	short alpha;
	string net1;
	string net2;
	string net3;
	string net4;

//qucsstudio regex
	static regex const r_head("^<(Qucs(?:Studio)?) Schematic [0-9]+\.[0-9]+\.[0-9]+>$");  //regex group 1
	//g1 begin    g2 x    g3 y    g4 end    g5 r
	static regex const r_mstub("^  <MSTUB((?: [^ ]+){2} )([\-0-9]+) ([\-0-9]+)((?: [^ ]+){3} ([0123])[^>]+>$)");

//schematic regex
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

//netlist regex
	static regex const r_type("^([^:]*):");                                     //regex group 1
	static regex const r_label("^([^:]*):([^ ]*)");                             //regex group 2
	static regex const r_net1("^([^ ]* ){1}_net([0-9]*)");                      //regex group 2
	static regex const r_net2("^([^ ]* ){2}_net([0-9]*)");                      //regex group 2
	static regex const r_net3("^([^ ]* ){3}_net([0-9]*)");                      //regex group 2
	static regex const r_net4("^([^ ]* ){4}_net([0-9]*)");                      //regex group 2



//open schematic
	cout << endl << "Opening " << n_sch << "... ";
	ifstream f_sch(n_sch.c_str());
	if(f_sch) {
		cout << "OK" << endl;
	} else {
		log_err << "ERROR : Cannot open " << n_sch << "\n";
		return(1);
		}

//check if qucs or qucsstudio
	getline(f_sch, line);
	regex_search(line, match, r_head);
	if(match.str(1)=="Qucs") {
		n_tmp=n_sch;
	} else if(match.str(1)=="QucsStudio") {
		// QucsStudio does not provide command line to produce netlist
		// so, as formats are mostly compatible, let's try to replace the
		// header and use Qucs instead
		log_err << "WARNING : " << n_sch << " is a QucsStudio schematic, compatibility is not guaranteed\n";

		cout << "Conversion to Qucs format... ";
		n_tmp=regex_replace(n_sch, r_sch, "\.tmp\.sch");
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
		
		f_tmp.close();
		f_sch.close();
		cout << "Opening " << n_tmp << "... ";
		f_sch.open(n_tmp.c_str());
		if(f_sch) {
			cout << "OK" << endl;
		} else {
			log_err << "ERROR : Cannot open " << n_tmp << "\n";
			return(1);
			}
	} else {
		log_err << "ERROR : " << n_sch << " appears to be neither a Qucs nor a QucsStudio schematic\n";
		return(1);
		}

//generate netlist
	cout << endl;
	if(regex_search(n_sch, r_sch)) {
		n_net=regex_replace(n_sch, r_sch, "\.net");
		cout << "n_sch : " << n_sch << endl;
		cout << "n_net : " << n_net << endl;
	} else {
		log_err << "ERROR : Invalid input format : " << n_sch << "\n";
		return(1);
		}

	cout << endl << "Generating netlist... ";
	string net_gen="qucs -n -i \""+n_tmp+"\" -o \""+n_net+"\"";
	QProcess process_qucs;
	process_qucs.start(QString::fromStdString(net_gen));
	bool ret = process_qucs.waitForFinished();
	if(ret==false || process_qucs.exitCode()) {
		cout << "KO" << endl;
		log_err << "ERROR : Problem with calling Qucs : " << net_gen << "\n";
		return(2);
	} else {
		cout << "OK" << endl;
		}

//open netlist
	cout << endl << "Opening " << n_net << "... ";
	ifstream f_net(n_net.c_str());		//all_MS.net
	if(f_net) {
		cout << "OK" << endl;
	} else {
		cout << "KO" << endl;
		log_err << "ERROR : Cannot open netlist " << n_net << "\n";
		return(1);
		}

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
				type=match.str(1);
				cout << "\tType : " << type << endl;
			//label
				regex_search(line, match, r_field2);
				label=match.str(2);
				cout << "\tLabel : " << label << endl;
			//mirrorx
				regex_search(line, match, r_field8);
				mirrorx=stoi(match.str(2));
				cout << "\tMirrorx : " << mirrorx << endl;
			//rotation
				regex_search(line, match, r_field9);
				R=90*stoi(match.str(2));
				cout << "\tRotation : " << R << endl;

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
					tab_all.push_back(shared_ptr<Element>(new Eqn(label, type, mirrorx, R)));
				} else if(type=="Pac") {
					//number
						regex_search(line, match, r_quotedfield10);
						N=stoi(match.str(6));
						cout << "\tNumber : " << N << endl;
					//impedance
						regex_search(line, match, r_quotedfield12);
						Z=(stold(match.str(6)))*suffix(match.str(8), match.str(9), false);
						cout << "\tImpedance : " << Z << endl;
					//power
						regex_search(line, match, r_quotedfield14);
						P=(stold(match.str(6)))*suffix(match.str(8), match.str(9), false);
						cout << "\tPower : " << P << endl;
					//frequency
						regex_search(line, match, r_quotedfield16);
						F=(stold(match.str(6)))*suffix(match.str(8), match.str(9), false);
						cout << "\tFrequency : " << F << endl;
					tab_all.push_back(shared_ptr<Element>(new Pac(label, type, mirrorx, R, N, Z, P, F)));
				} else if(type==".SP") {
					//is active
						regex_search(line, match, r_field3);
						is_active=stoi(match.str(2));
						cout << "\tIs active : " << is_active << endl;
					if(is_active) {
						//simulation type
							regex_search(line, match, r_quotedfield10_raw);
							simtype=match.str(4);
							cout << "\tSimulation type : " << simtype << endl;
						if(simtype=="lin"
						|| simtype=="log") {
							//start frequency
								regex_search(line, match, r_quotedfield12);
								Fstart=(stold(match.str(6)))*suffix(match.str(8), match.str(9), false);
								cout << "\tStart frequency : " << Fstart << endl;
							//stop frequency
								regex_search(line, match, r_quotedfield14);
								Fstop=(stold(match.str(6)))*suffix(match.str(8), match.str(9), false);
								cout << "\tStop frequency : " << Fstop << endl;
							//step number
								regex_search(line, match, r_quotedfield16);
								N=(stold(match.str(6)))*suffix(match.str(8), match.str(9), false);
								cout << "\tStep number : " << N << endl;
							tab_all.push_back(shared_ptr<Element>(new Sp(label, type, mirrorx, R, simtype, Fstart, Fstop, N)));
						} else { // "list" & "const"
							log_err << "WARNING : " << label << " : Unsupported simulation type : " << simtype << " -> Ignored\n";
							}
						}
				} else if(type=="SUBST") {
					//relative permittivity
						regex_search(line, match, r_quotedfield10);
						er=(stold(match.str(6)))*suffix(match.str(8), match.str(9), false);
						cout << "\tRelative permittivity : " << er << endl;
					//substrate thickness
						regex_search(line, match, r_quotedfield12);
						H=(stold(match.str(6)))*suffix(match.str(8), match.str(9), true);
						cout << "\tSubstrate thickness : " << H << endl;
					//metal thickness
						regex_search(line, match, r_quotedfield14);
						T=(stold(match.str(6)))*suffix(match.str(8), match.str(9), true);
						cout << "\tMetal thickness : " << T << endl;
					//loss tangent
						regex_search(line, match, r_quotedfield16);
						tand=(stold(match.str(6)))*suffix(match.str(8), match.str(9), false);
						cout << "\tLoss tangent : " << tand << endl;
					//metal resistivity
						regex_search(line, match, r_quotedfield18);
						rho=(stold(match.str(6)))*suffix(match.str(8), match.str(9), false);
						cout << "\tMetal resistance : " << rho << endl;
					//substrate roughness
						regex_search(line, match, r_quotedfield20);
						D=(stold(match.str(6)))*suffix(match.str(8), match.str(9), false);
						cout << "\tMetal roughness : " << D << endl;
					tab_all.push_back(shared_ptr<Element>(new Subst(label, type, mirrorx, R, er, H, T, tand, rho, D)));
				} else if(type=="MCORN") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width
						regex_search(line, match, r_quotedfield12);
						W=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth : " << W << endl;
					tab_all.push_back(shared_ptr<Element>(new Mcorn(label, type, mirrorx, R, subst, W)));
				} else if(type=="MCROSS") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width 1
						regex_search(line, match, r_quotedfield12);
						W1=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 1 : " << W1 << endl;
					//width 2
						regex_search(line, match, r_quotedfield14);
						W2=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 2 : " << W2 << endl;
					//width 3
						regex_search(line, match, r_quotedfield16);
						W3=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 3 : " << W3 << endl;
					//width 4
						regex_search(line, match, r_quotedfield18);
						W4=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 4 : " << W4 << endl;
					tab_all.push_back(shared_ptr<Element>(new Mcross(label, type, mirrorx, R, subst, W1, W2, W3, W4)));
				} else if(type=="MCOUPLED") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width
						regex_search(line, match, r_quotedfield12);
						W=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth : " << W << endl;
					//length
						regex_search(line, match, r_quotedfield14);
						L=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tLength : " << L << endl;
					//space
						regex_search(line, match, r_quotedfield16);
						S=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tSpace : " << S << endl;
					tab_all.push_back(shared_ptr<Element>(new Mcoupled(label, type, mirrorx, R, subst, W, L, S)));
				} else if(type=="MGAP") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width 1
						regex_search(line, match, r_quotedfield12);
						string tmp;
						W1=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 1 : " << W1 << endl;
					//width 2
						regex_search(line, match, r_quotedfield14);
						W2=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 2 : " << W2 << endl;
					//space
						regex_search(line, match, r_quotedfield16);
						S=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tSpace : " << S << endl;
					tab_all.push_back(shared_ptr<Element>(new Mgap(label, type, mirrorx, R, subst, W1, W2, S)));
				} else if(type=="MMBEND") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width
						regex_search(line, match, r_quotedfield12);
						W=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth : " << W << endl;
					tab_all.push_back(shared_ptr<Element>(new Mmbend(label, type, mirrorx, R, subst, W)));
				} else if(type=="MLIN") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width
						regex_search(line, match, r_quotedfield12);
						W=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth : " << W << endl;
					//length
						regex_search(line, match, r_quotedfield14);
						L=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tLength : " << L << endl;
					tab_all.push_back(shared_ptr<Element>(new Mlin(label, type, mirrorx, R, subst, W, L)));
				} else if(type=="MOPEN") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width
						regex_search(line, match, r_quotedfield12);
						W=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth : " << W << endl;
					tab_all.push_back(shared_ptr<Element>(new Mopen(label, type, mirrorx, R, subst, W)));
				} else if(type=="MRSTUB") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//inner radius
						regex_search(line, match, r_quotedfield12);
						ri=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tInner radius : " << ri << endl;
					//outer radius
						regex_search(line, match, r_quotedfield14);
						ro=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tOuter radius : " << ro << endl;
					//alpha
						//no unit
						regex_search(line, match, r_quotedfield16);
						alpha=stoi(match.str(5));
						cout << "\tAlpha : " << alpha << endl;
					tab_all.push_back(shared_ptr<Element>(new Mrstub(label, type, mirrorx, R, subst, ri, ro, alpha)));
				} else if(type=="MSTEP") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width 1
						regex_search(line, match, r_quotedfield12);
						W1=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 1 : " << W1 << endl;
					//width 2
						regex_search(line, match, r_quotedfield14);
						W2=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 2 : " << W2 << endl;
					tab_all.push_back(shared_ptr<Element>(new Mstep(label, type, mirrorx, R, subst, W1, W2)));
				} else if(type=="MTEE") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//width 1
						regex_search(line, match, r_quotedfield12);
						W1=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 1 : " << W1 << endl;
					//width 2
						regex_search(line, match, r_quotedfield14);
						W2=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 2 : " << W2 << endl;
					//width 3
						regex_search(line, match, r_quotedfield16);
						W3=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tWidth 3 : " << W3 << endl;
					tab_all.push_back(shared_ptr<Element>(new Mtee(label, type, mirrorx, R, subst, W1, W2, W3)));
				} else if(type=="MVIA") {
					//substrat
						regex_search(line, match, r_quotedfield10_raw);
						subst=match.str(4);
						cout << "\tSubstrat : " << subst << endl;
					//diameter
						regex_search(line, match, r_quotedfield12);
						D=(stold(check_void(match.str(6), label)))*suffix(match.str(8), match.str(9), true);
						cout << "\tDiameter : " << D << endl;
					tab_all.push_back(shared_ptr<Element>(new Mvia(label, type, mirrorx, R, subst, D)));
					}
				}
			break;
			}
		}
	cout << "Reading schematic... OK" << endl;

//read netlist
	cout << endl << "Reading netlist... " << endl;
	while(getline(f_net, line)) {
		if(line=="") {
			while(getline(f_net, line)) {
				cout << line << endl;

			//type
				regex_search(line, match, r_type);
				type=match.str(1);
				cout << "\tType : " << type << endl;
			//label
				regex_search(line, match, r_label);
				label=match.str(2);
				cout << "\tLabel : " << label << endl;
			//find ielem->label
				for(shared_ptr<Element> it : tab_all) {
					if(it->getLabel()==label) {
						if(type=="Eqn"
						|| type=="SUBST"){
							//to be complete
						} else if(type=="MOPEN"
							   || type=="MRSTUB"
							   || type=="MVIA") {
							//net 1
								regex_search(line, match, r_net1);
								net1=match.str(2);
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
								net1=match.str(2);
								cout << "\tNet 1 : " << net1 << endl;
							//net 2
								regex_search(line, match, r_net2);
								net2=match.str(2);
								cout << "\tNet 2 : " << net2 << endl;
							it->setNet1(net1);
							it->setNet2(net2);
						} else if(type=="MTEE") {
							//net 1
								regex_search(line, match, r_net1);
								net1=match.str(2);
								cout << "\tNet 1 : " << net1 << endl;
							//net 2
								regex_search(line, match, r_net2);
								net2=match.str(2);
								cout << "\tNet 2 : " << net2 << endl;
							//net 3
								regex_search(line, match, r_net3);
								net3=match.str(2);
								cout << "\tNet 3 : " << net3 << endl;
							it->setNet1(net1);
							it->setNet2(net2);
							it->setNet3(net3);
						} else if(type=="MCOUPLED"
								||type=="MCROSS") {
							//net 1
								regex_search(line, match, r_net1);
								net1=match.str(2);
								cout << "\tNet 1 : " << net1 << endl;
							//net 2
								regex_search(line, match, r_net2);
								net2=match.str(2);
								cout << "\tNet 2 : " << net2 << endl;
							//net 3
								regex_search(line, match, r_net3);
								net3=match.str(2);
								cout << "\tNet 3 : " << net3 << endl;
							//net 4
								regex_search(line, match, r_net4);
								net4=match.str(2);
								cout << "\tNet 4 : " << net4 << endl;
							it->setNet1(net1);
							it->setNet2(net2);
							it->setNet3(net3);
							it->setNet4(net4);
							}
						}
					}
				}
			}
		}
	cout << "Reading netlist... OK" << endl;
	cout << "N elements : " << tab_all.size() << endl;
	warn_unprintable();
	return(0);
	}

void SchParser::warn_unprintable(void) {
	if(unprintables.size()) {
		log_err << "WARNING : Schematic contains some unprintable transmission lines";
		for(string element : unprintables) {
			log_err << " " << element;
			if(element!=unprintables.back()) log_err << ",";
			}
		log_err << " -> Ignored\n";
		}
	}

long double SchParser::suffix(string const s_sci, const string s_eng, bool is_length) {
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


string SchParser::check_void(string match, string label) {
	if(match=="") {
		log_err << "WARNING : Void field in component " << label << " -> Assigned to 0\n";
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
	else return(str); //never happend
	}

#pragma GCC diagnostic pop

