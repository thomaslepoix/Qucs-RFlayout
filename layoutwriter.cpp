/***************************************************************************
                               layoutwriter.cpp
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

#include "layoutwriter.h"
using namespace std;

int layoutwriter(Element** const& tab_all, int const& nelem, string const& n_sch, string const& out_format) {

//variables
	regex r_sch(".sch$");
	string n_out;
	string name=regex_replace(n_sch, r_sch, "");

//generation output file
	cout << endl;
	n_out=regex_replace(n_sch, r_sch, out_format);
	cout << "Input schematic : " << n_sch << endl;
	cout << "Output layout : " << n_out << endl;
	ofstream f_out(n_out.c_str());

//write
	if(out_format==".kicad_pcb") write_kicad_pcb(tab_all, nelem, f_out);
	if(out_format==".kicad_mod") write_kicad_mod(tab_all, nelem, name, f_out);

	return(0);
	}

int write_kicad_pcb(Element** const& tab_all, int const& nelem, ofstream& f_out) {
	string type;
	signed int s;
	string s1;
	string s2;
	signed int n;
	long double Wlong;
	long double Wlong13;
	long double Wlong24;

	f_out << "\
(kicad_pcb (version 20171130) (host pcbnew 5.0.1-33cea8e~67~ubuntu18.04.1)\n\
\n\
  (general\n\
    (thickness 1.6)\n\
    (drawings 0)\n\
    (tracks 0)\n\
    (zones 0)\n\
    (modules 0)\n\
    (nets 1)\n\
  )\n\
\n\
  (page A4)\n\
  (layers\n\
    (0 F.Cu signal)\n\
    (31 B.Cu signal)\n\
    (32 B.Adhes user)\n\
    (33 F.Adhes user)\n\
    (34 B.Paste user)\n\
    (35 F.Paste user)\n\
    (36 B.SilkS user)\n\
    (37 F.SilkS user)\n\
    (38 B.Mask user)\n\
    (39 F.Mask user)\n\
    (40 Dwgs.User user)\n\
    (41 Cmts.User user)\n\
    (42 Eco1.User user)\n\
    (43 Eco2.User user)\n\
    (44 Edge.Cuts user)\n\
    (45 Margin user)\n\
    (46 B.CrtYd user)\n\
    (47 F.CrtYd user)\n\
    (48 B.Fab user)\n\
    (49 F.Fab user)\n\
  )\n\
\n\
  (setup\n\
    (last_trace_width 0.25)\n\
    (trace_clearance 0.2)\n\
    (zone_clearance 0.508)\n\
    (zone_45_only no)\n\
    (trace_min 0.2)\n\
    (segment_width 0.2)\n\
    (edge_width 0.15)\n\
    (via_size 0.8)\n\
    (via_drill 0.4)\n\
    (via_min_size 0.4)\n\
    (via_min_drill 0.3)\n\
    (uvia_size 0.3)\n\
    (uvia_drill 0.1)\n\
    (uvias_allowed no)\n\
    (uvia_min_size 0.2)\n\
    (uvia_min_drill 0.1)\n\
    (pcb_text_width 0.3)\n\
    (pcb_text_size 1.5 1.5)\n\
    (mod_edge_width 0.15)\n\
    (mod_text_size 1 1)\n\
    (mod_text_width 0.15)\n\
    (pad_size 1.524 1.524)\n\
    (pad_drill 0.762)\n\
    (pad_to_mask_clearance 0.051)\n\
    (solder_mask_min_width 0.25)\n\
    (aux_axis_origin 0 0)\n\
    (visible_elements FFFFFF7F)\n\
    (pcbplotparams\n\
      (layerselection 0x010fc_ffffffff)\n\
      (usegerberextensions false)\n\
      (usegerberattributes false)\n\
      (usegerberadvancedattributes false)\n\
      (creategerberjobfile false)\n\
      (excludeedgelayer true)\n\
      (linewidth 0.150000)\n\
      (plotframeref false)\n\
      (viasonmask false)\n\
      (mode 1)\n\
      (useauxorigin false)\n\
      (hpglpennumber 1)\n\
      (hpglpenspeed 20)\n\
      (hpglpendiameter 15.000000)\n\
      (psnegative false)\n\
      (psa4output false)\n\
      (plotreference true)\n\
      (plotvalue true)\n\
      (plotinvisibletext false)\n\
      (padsonsilk false)\n\
      (subtractmaskfromsilk false)\n\
      (outputformat 1)\n\
      (mirror false)\n\
      (drillshape 1)\n\
      (scaleselection 1)\n\
      (outputdirectory \"\"))\n\
  )\n\
\n\
  (net 0 \"\")\n\
\n\
  (net_class Default \"This is the default net class.\"\n\
    (clearance 0.2)\n\
    (trace_width 0.25)\n\
    (via_dia 0.8)\n\
    (via_drill 0.4)\n\
    (uvia_dia 0.3)\n\
    (uvia_drill 0.1)\n\
  )\n\n";

	for(int i=0;i<nelem;i++) {
		type=tab_all[i]->getType();
		if(type=="Eqn" || type=="Pac" || type=="MGAP" || type=="MOPEN" || type=="MSTEP") {
			//nothing to do
		} else if(type=="MCORN") {//////////////////////////////////////////////
			f_out << "\
  (module " << tab_all[i]->getType() << " (layer F.Cu) (tedit 0) (tstamp 0)\n\
    (at " << tab_all[i]->getX() << " " << tab_all[i]->getY() << " " << tab_all[i]->getR() << ")\n\
    (fp_text reference " << tab_all[i]->getLabel() << " (at 0 0.5) (layer F.SilkS)\n\
      (effects (font (size 0.25 0.25) (thickness 0.05)))\n\
    )\n\
    (fp_text value micostrip_corner (at 0 -0.5) (layer F.Fab)\n\
      (effects (font (size 0.25 0.25) (thickness 0.05)))\n\
    )\n\
    (pad \"\" smd rect (at 0 0 " << tab_all[i]->getR() << ") (size " << tab_all[i]->getW() << " " << tab_all[i]->getW() << ") (layers F.Cu))\n\
  )\n\n";
		} else if(type=="MCROSS") {/////////////////////////////////////////////
			if(tab_all[i]->getMirrorx()==0) {
				s1="";
				s2="-";
			} else if(tab_all[i]->getMirrorx()==1) {
				s1="-";
				s2="";
				}
			Wlong13= (tab_all[i]->getW1()>tab_all[i]->getW3()) ? tab_all[i]->getW1() : tab_all[i]->getW3();
			Wlong24= (tab_all[i]->getW2()>tab_all[i]->getW4()) ? tab_all[i]->getW2() : tab_all[i]->getW4();
			f_out << "\
  (module " << tab_all[i]->getType() << " (layer F.Cu) (tedit 0) (tstamp 0)\n\
    (at " << tab_all[i]->getX() << " " << tab_all[i]->getY() << " " << tab_all[i]->getR() << ")\n\
    (fp_text reference " << tab_all[i]->getLabel() << " (at 0 0.5) (layer F.SilkS)\n\
      (effects (font (size 0.25 0.25) (thickness 0.05)))\n\
    )\n\
    (fp_text value micostrip_cross (at 0 -0.5 360) (layer F.Fab)\n\
      (effects (font (size 0.25 0.25) (thickness 0.05)))\n\
    )\n\
    (fp_poly (pts \
(xy " << -Wlong24/2 << " " << s1 << tab_all[i]->getW1()/2 << ") \
(xy " << -Wlong24/2 << " " << s2 << tab_all[i]->getW1()/2 << ")\n      ";
			if(Wlong13==tab_all[i]->getW3() && Wlong24==tab_all[i]->getW4()) f_out << "(xy " << -tab_all[i]->getW2()/2 << " " << s2 << tab_all[i]->getW1()/2 << ")\n      ";
			f_out << "\
(xy " << -tab_all[i]->getW2()/2 << " " << s2 << Wlong13/2 << ") \
(xy " << tab_all[i]->getW2()/2 << " " << s2 << Wlong13/2 << ")\n      ";
			if(Wlong13==tab_all[i]->getW1() && Wlong24==tab_all[i]->getW4()) f_out << "(xy " << tab_all[i]->getW2()/2 << " " << s2 << tab_all[i]->getW3()/2 << ")\n      ";
			f_out << "\
(xy " << Wlong24/2 << " " << s2 << tab_all[i]->getW3()/2 << ") \
(xy " << Wlong24/2 << " " << s1 << tab_all[i]->getW3()/2 << ")\n      ";
			if(Wlong13==tab_all[i]->getW1() && Wlong24==tab_all[i]->getW2()) f_out << "(xy " << tab_all[i]->getW4()/2 << " " << s1 << tab_all[i]->getW3()/2 << ")\n      ";
			f_out << "\
(xy " << tab_all[i]->getW4()/2 << " " << s1 << Wlong13/2 << ") \
(xy " << -tab_all[i]->getW4()/2 << " " << s1 << Wlong13/2 << ")\n      ";
			if(Wlong13==tab_all[i]->getW3() && Wlong24==tab_all[i]->getW2()) f_out << "(xy " << -tab_all[i]->getW4()/2 << " " << s1 << tab_all[i]->getW1()/2 << ")\n      ";
			f_out << "\
) (layer F.Cu) (width 0))\n\
  )\n\n";
		} else if(type=="MCOUPLED") {///////////////////////////////////////////
			f_out << "\
  (module " << tab_all[i]->getType() << " (layer F.Cu) (tedit 0) (tstamp 0)\n\
    (at " << tab_all[i]->getX() << " " << tab_all[i]->getY() << " " << tab_all[i]->getR() << ")\n\
    (fp_text reference " << tab_all[i]->getLabel() << " (at 0 0.5) (layer F.SilkS)\n\
      (effects (font (size 0.25 0.25) (thickness 0.05)))\n\
    )\n\
    (fp_text value micostrip_line (at 0 -0.5) (layer F.Fab)\n\
      (effects (font (size 0.25 0.25) (thickness 0.05)))\n\
    )\n\
    (pad \"\" smd rect (at 0 " << (tab_all[i]->getS()/2)+(tab_all[i]->getW()/2) << " " << tab_all[i]->getR() << ") (size " << tab_all[i]->getL() << " " << tab_all[i]->getW() << ") (layers F.Cu))\n\
    (pad \"\" smd rect (at 0 " << -(tab_all[i]->getS()/2)-(tab_all[i]->getW()/2) << " " << tab_all[i]->getR() << ") (size " << tab_all[i]->getL() << " " << tab_all[i]->getW() << ") (layers F.Cu))\n\
  )\n\n";
		} else if(type=="MMBEND") {/////////////////////////////////////////////
			if(tab_all[i]->getMirrorx()==0) {
				s1="";
				s2="-";
			} else if(tab_all[i]->getMirrorx()==1) {
				s1="-";
				s2="";
				}
			f_out << "\
  (module " << tab_all[i]->getType() << " (layer F.Cu) (tedit 0) (tstamp 0)\n\
    (at " << tab_all[i]->getX() << " " << tab_all[i]->getY() << " " << tab_all[i]->getR() << ")\n\
    (fp_text reference " << tab_all[i]->getLabel() << " (at 0 0.5) (layer F.SilkS)\n\
      (effects (font (size 0.25 0.25) (thickness 0.05)))\n\
    )\n\
    (fp_text value micostrip_mitered_bend (at 0 -0.5 360) (layer F.Fab)\n\
      (effects (font (size 0.25 0.25) (thickness 0.05)))\n\
    )\n\
    (fp_poly (pts \
(xy " << tab_all[i]->getW()/2 << " " << s1 << tab_all[i]->getW()/2 << ") \
(xy " << -tab_all[i]->getW()/2 << " " << s2 << tab_all[i]->getW()/2 << ")\n      \
(xy " << -tab_all[i]->getW()/2 << " " << s1 << tab_all[i]->getW()/2 << ")) (layer F.Cu) (width 0))\n\
  )\n\n";
		} else if(type=="MLIN") {///////////////////////////////////////////////
			f_out << "\
  (module " << tab_all[i]->getType() << " (layer F.Cu) (tedit 0) (tstamp 0)\n\
    (at " << tab_all[i]->getX() << " " << tab_all[i]->getY() << " " << tab_all[i]->getR() << ")\n\
    (fp_text reference " << tab_all[i]->getLabel() << " (at 0 0.5) (layer F.SilkS)\n\
      (effects (font (size 0.25 0.25) (thickness 0.05)))\n\
    )\n\
    (fp_text value micostrip_line (at 0 -0.5) (layer F.Fab)\n\
      (effects (font (size 0.25 0.25) (thickness 0.05)))\n\
    )\n\
    (pad \"\" smd rect (at 0 0 " << tab_all[i]->getR() << ") (size " << tab_all[i]->getL() << " " << tab_all[i]->getW() << ") (layers F.Cu))\n\
  )\n\n";
		} else if(type=="MRSTUB") {/////////////////////////////////////////////
			n=int(tab_all[i]->getAlpha())/5;
			if(tab_all[i]->getMirrorx()==0) s=1;
			if(tab_all[i]->getMirrorx()==1) s=-1;
			f_out << "\
  (module " << tab_all[i]->getType() << " (layer F.Cu) (tedit 0) (tstamp 0)\n\
    (at " << tab_all[i]->getX() << " " << tab_all[i]->getY() << " " << tab_all[i]->getR() << ")\n\
    (fp_text reference " << tab_all[i]->getLabel() << " (at 0 0.5) (layer F.SilkS)\n\
      (effects (font (size 0.25 0.25) (thickness 0.05)))\n\
    )\n\
    (fp_text value micostrip_radial_stub (at 0 -0.5 360) (layer F.Fab)\n\
      (effects (font (size 0.25 0.25) (thickness 0.05)))\n\
    )\n\
    (fp_poly (pts \
(xy " << tab_all[i]->getW()/2 << " 0) \
(xy " << -tab_all[i]->getW()/2 << " 0)\n      \
(xy " << tab_all[i]->getRo()*sin((M_PI/180)*(-tab_all[i]->getAlpha()/2)) << " " << s*((-tab_all[i]->getRo()*cos((M_PI/180)*(-tab_all[i]->getAlpha()/2)))-tab_all[i]->getL()) << ")\n      ";

			for(int u=-5*n/2;u<=5*n/2;u+=5) {
				f_out << "\
(xy " << tab_all[i]->getRo()*sin((M_PI/180)*(u)) << " " <<  s*((-tab_all[i]->getRo()*cos((M_PI/180)*(u)))-tab_all[i]->getL()) << ")\n      ";
				}
				f_out << "\
(xy " << -tab_all[i]->getRo()*sin((M_PI/180)*(-tab_all[i]->getAlpha()/2)) << " " << s*((-tab_all[i]->getRo()*cos((M_PI/180)*(-tab_all[i]->getAlpha()/2)))-tab_all[i]->getL()) << ")) (layer F.Cu) (width 0))\n\
  )\n\n";
		} else if(type=="MTEE") {///////////////////////////////////////////////
			if(tab_all[i]->getMirrorx()==0) {
				s1="";
				s2="-";
			} else if(tab_all[i]->getMirrorx()==1) {
				s1="-";
				s2="";
				}
			Wlong= (tab_all[i]->getW1()>tab_all[i]->getW2()) ? tab_all[i]->getW1() : tab_all[i]->getW2();
			f_out << "\
  (module " << tab_all[i]->getType() << " (layer F.Cu) (tedit 0) (tstamp 0)\n\
    (at " << tab_all[i]->getX() << " " << tab_all[i]->getY() << " " << tab_all[i]->getR() << ")\n\
    (fp_text reference " << tab_all[i]->getLabel() << " (at 0 0.5) (layer F.SilkS)\n\
      (effects (font (size 0.25 0.25) (thickness 0.05)))\n\
    )\n\
    (fp_text value micostrip_tee (at 0 -0.5 360) (layer F.Fab)\n\
      (effects (font (size 0.25 0.25) (thickness 0.05)))\n\
    )\n\
    (fp_poly (pts \
(xy " << -tab_all[i]->getW3()/2 << " " << s2 << tab_all[i]->getW1()/2 << ") \
(xy 0 " << s2 << tab_all[i]->getW1()/2 << ") \
(xy 0 " << s2 << tab_all[i]->getW2()/2 << ") \
(xy " << tab_all[i]->getW3()/2 << " " << s2 << tab_all[i]->getW2()/2 << ")\n      \
(xy " << tab_all[i]->getW3()/2 << " " << s1 << Wlong/2 << ") \
(xy " << -tab_all[i]->getW3()/2 << " " << s1 << Wlong/2 << ")) (layer F.Cu) (width 0))\n\
  )\n\n";
		} else if(type=="MVIA") {///////////////////////////////////////////////
			f_out << "\
  (via (at " << tab_all[i]->getX() << " " << tab_all[i]->getY() << ") (size " << tab_all[i]->getD() << ") (drill " << tab_all[i]->getD() << ") (layers F.Cu B.Cu))\n\n";
			}
		}

	f_out << ")\n";
	return(0);
	}

int write_kicad_mod(Element** const& tab_all, int const& nelem, string const& name, ofstream& f_out) {
	string type;
	signed int s;
	signed int s1;
	signed int s2;
	signed int n;
	long double Wlong;
	long double Wlong13;
	long double Wlong24;

	f_out << "\
(module " << name << " (layer F.Cu) (tedit 5BD7B6BE)\n\
  (fp_text reference REF** (at 0 0.5) (layer F.SilkS)\n\
    (effects (font (size 1 1) (thickness 0.15)))\n\
  )\n\
  (fp_text value " << name << " (at 0 -0.5) (layer F.Fab)\n\
    (effects (font (size 1 1) (thickness 0.15)))\n\
  )\n";

	for(int i=0;i<nelem;i++) {
		type=tab_all[i]->getType();
		if(type=="Eqn" || type=="MGAP" || type=="MOPEN" || type=="MSTEP") {
			//nothing to do
		} else if(type=="Pac") {////////////////////////////////////////////////
			//things to do
		} else if(type=="MCORN") {//////////////////////////////////////////////
			f_out << "\
    (pad \"\" smd rect (at " << tab_all[i]->getX() << " " << tab_all[i]->getY() << " " << tab_all[i]->getR() << ") (size " << tab_all[i]->getW() << " " << tab_all[i]->getW() << ") (layers F.Cu))\n";
		} else if(type=="MCROSS") {/////////////////////////////////////////////
			if(tab_all[i]->getMirrorx()==0) {
				s1=1;
				s2=-1;
			} else if(tab_all[i]->getMirrorx()==1) {
				s1=-1;
				s2=1;
				}
			Wlong13= (tab_all[i]->getW1()>tab_all[i]->getW3()) ? tab_all[i]->getW1() : tab_all[i]->getW3();
			Wlong24= (tab_all[i]->getW2()>tab_all[i]->getW4()) ? tab_all[i]->getW2() : tab_all[i]->getW4();
			f_out << "\
    (fp_poly (pts \
(xy " << tab_all[i]->getX()-Wlong24/2 << " " << tab_all[i]->getY()+s1*(tab_all[i]->getW1()/2) << ") \
(xy " << tab_all[i]->getX()-Wlong24/2 << " " << tab_all[i]->getY()+s2*(tab_all[i]->getW1()/2) << ")\n      ";
			if(Wlong13==tab_all[i]->getW3() && Wlong24==tab_all[i]->getW4()) f_out << "(xy " << tab_all[i]->getX()-tab_all[i]->getW2()/2 << " " << tab_all[i]->getY()+s2*(tab_all[i]->getW1()/2) << ")\n      ";
			f_out << "\
(xy " << tab_all[i]->getX()-tab_all[i]->getW2()/2 << " " << tab_all[i]->getY()+s2*(Wlong13/2) << ") \
(xy " << tab_all[i]->getX()+tab_all[i]->getW2()/2 << " " << tab_all[i]->getY()+s2*(Wlong13/2) << ")\n      ";
			if(Wlong13==tab_all[i]->getW1() && Wlong24==tab_all[i]->getW4()) f_out << "(xy " << tab_all[i]->getX()+tab_all[i]->getW2()/2 << " " << tab_all[i]->getY()+s2*(tab_all[i]->getW3()/2) << ")\n      ";
			f_out << "\
(xy " << tab_all[i]->getX()+Wlong24/2 << " " << tab_all[i]->getY()+s1*(tab_all[i]->getW3()/2) << ") \
(xy " << tab_all[i]->getX()+Wlong24/2 << " " << tab_all[i]->getY()+s1*(tab_all[i]->getW3()/2) << ")\n      ";
			if(Wlong13==tab_all[i]->getW1() && Wlong24==tab_all[i]->getW2()) f_out << "(xy " << tab_all[i]->getX()+tab_all[i]->getW4()/2 << " " << tab_all[i]->getY()+s1*(tab_all[i]->getW3()/2) << ")\n      ";
			f_out << "\
(xy " << tab_all[i]->getX()+tab_all[i]->getW4()/2 << " " << tab_all[i]->getY()+s1*(Wlong13/2) << ") \
(xy " << tab_all[i]->getX()-tab_all[i]->getW4()/2 << " " << tab_all[i]->getY()+s1*(Wlong13/2) << ")\n      ";
			if(Wlong13==tab_all[i]->getW3() && Wlong24==tab_all[i]->getW2()) f_out << "(xy " << tab_all[i]->getX()-tab_all[i]->getW4()/2 << " " << tab_all[i]->getY()+s1*(tab_all[i]->getW1()/2) << ")\n      ";
			f_out << "\
) (layer F.Cu) (width 0))\n";
		} else if(type=="MCOUPLED") {///////////////////////////////////////////
			f_out << "\
    (pad \"\" smd rect (at " << tab_all[i]->getX() << " " << tab_all[i]->getY()+(tab_all[i]->getS()/2)+(tab_all[i]->getW()/2) << " " << tab_all[i]->getR() << ") (size " << tab_all[i]->getL() << " " << tab_all[i]->getW() << ") (layers F.Cu))\n\
    (pad \"\" smd rect (at " << tab_all[i]->getX() << " " << tab_all[i]->getY()-(tab_all[i]->getS()/2)-(tab_all[i]->getW()/2) << " " << tab_all[i]->getR() << ") (size " << tab_all[i]->getL() << " " << tab_all[i]->getW() << ") (layers F.Cu))\n";
		} else if(type=="MMBEND") {/////////////////////////////////////////////
			if(tab_all[i]->getMirrorx()==0) {
				s1=1;
				s2=-1;
			} else if(tab_all[i]->getMirrorx()==1) {
				s1=-1;
				s2=1;
				}
			f_out << "\
    (fp_poly (pts \
(xy " << tab_all[i]->getX()+tab_all[i]->getW()/2 << " " << tab_all[i]->getY()+s1*(tab_all[i]->getW()/2) << ") \
(xy " << tab_all[i]->getX()-tab_all[i]->getW()/2 << " " << tab_all[i]->getY()+s2*(tab_all[i]->getW()/2) << ")\n      \
(xy " << tab_all[i]->getX()-tab_all[i]->getW()/2 << " " << tab_all[i]->getY()+s1*(tab_all[i]->getW()/2) << ")) (layer F.Cu) (width 0))\n";
		} else if(type=="MLIN") {///////////////////////////////////////////////
			f_out << "\
    (pad \"\" smd rect (at " << tab_all[i]->getX() << " " << tab_all[i]->getY() << " " << tab_all[i]->getR() << ") (size " << tab_all[i]->getL() << " " << tab_all[i]->getW() << ") (layers F.Cu))\n";
		} else if(type=="MRSTUB") {/////////////////////////////////////////////
			n=int(tab_all[i]->getAlpha())/5;
			if(tab_all[i]->getMirrorx()==0) s=1;
			if(tab_all[i]->getMirrorx()==1) s=-1;
			f_out << "\
    (fp_poly (pts \
(xy " << tab_all[i]->getX()+tab_all[i]->getW()/2 << " " << tab_all[i]->getY() << ") \
(xy " << tab_all[i]->getX()-tab_all[i]->getW()/2 << " " << tab_all[i]->getY() << ")\n      \
(xy " << tab_all[i]->getX()+tab_all[i]->getRo()*sin((M_PI/180)*(-tab_all[i]->getAlpha()/2)) << " " << tab_all[i]->getY()+s*((-tab_all[i]->getRo()*cos((M_PI/180)*(-tab_all[i]->getAlpha()/2)))-tab_all[i]->getL()) << ")\n      ";

			for(int u=-5*n/2;u<=5*n/2;u+=5) {
				f_out << "\
(xy " << tab_all[i]->getX()+tab_all[i]->getRo()*sin((M_PI/180)*(u)) << " " << tab_all[i]->getY()+s*((-tab_all[i]->getRo()*cos((M_PI/180)*(u)))-tab_all[i]->getL()) << ")\n      ";
				}
				f_out << "\
(xy " << tab_all[i]->getX()-tab_all[i]->getRo()*sin((M_PI/180)*(-tab_all[i]->getAlpha()/2)) << " " << tab_all[i]->getY()+s*((-tab_all[i]->getRo()*cos((M_PI/180)*(-tab_all[i]->getAlpha()/2)))-tab_all[i]->getL()) << ")) (layer F.Cu) (width 0))\n";
		} else if(type=="MTEE") {///////////////////////////////////////////////
			if(tab_all[i]->getMirrorx()==0) {
				s1=1;
				s2=-1;
			} else if(tab_all[i]->getMirrorx()==1) {
				s1=-1;
				s2=1;
				}
			Wlong= (tab_all[i]->getW1()>tab_all[i]->getW2()) ? tab_all[i]->getW1() : tab_all[i]->getW2();
			f_out << "\
    (fp_poly (pts \
(xy " << tab_all[i]->getX()-tab_all[i]->getW3()/2 << " " << tab_all[i]->getY()+s2*(tab_all[i]->getW1()/2) << ") \
(xy " << tab_all[i]->getX() << " " << tab_all[i]->getY()+s2*(tab_all[i]->getW1()/2) << ") \
(xy " << tab_all[i]->getX() << " " << tab_all[i]->getY()+s2*(tab_all[i]->getW2()/2) << ") \
(xy " << tab_all[i]->getX()+tab_all[i]->getW3()/2 << " " << tab_all[i]->getY()+s2*(tab_all[i]->getW2()/2) << ")\n      \
(xy " << tab_all[i]->getX()+tab_all[i]->getW3()/2 << " " << tab_all[i]->getY()+s1*(Wlong/2) << ") \
(xy " << tab_all[i]->getX()-tab_all[i]->getW3()/2 << " " << tab_all[i]->getY()+s1*(Wlong/2) << ")) (layer F.Cu) (width 0))\n";
		} else if(type=="MVIA") {///////////////////////////////////////////////
			f_out << "\
  (pad \"\" thru_hole circle (at " << tab_all[i]->getX() << " " << tab_all[i]->getY() << ") (size " << tab_all[i]->getD() << ") (drill " << tab_all[i]->getD() << ") (layers *.Cu))\n";
			}
		}

	f_out << ")\n";
	return(0);
	}
