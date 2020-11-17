/***************************************************************************
                               layoutwriter.cpp
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

#include <algorithm>
#include <iostream>
#include <iterator>
#include <regex>
#include <utility>

#include "layoutstrings.hpp"
#include "logger.hpp"
#include "oemsmesh.hpp"
#include "microstrip/element.hpp"
#include "microstrip/pac.hpp"
#include "microstrip/subst.hpp"
#include "layoutwriter.hpp"
using namespace std;

//******************************************************************************
LayoutWriter::LayoutWriter(Data const& _data) :
	data(_data)
	{}

//******************************************************************************
int LayoutWriter::run(vector<string>* out_names) const {

//variables
	static regex const r_sch("\\.sch$");
	static regex const r_basename("^.*?([^\\/]*)\\.sch$"); // g1 basename
	static regex const r_out("(^.*?)\\/?$");
	static regex const r_empty("^$");
	string name=regex_replace(regex_replace(data.n_sch, r_basename, "$1"), r_sch, "");
	string n_out=regex_replace(data.out_dir, r_empty, "./");
	n_out=regex_replace(n_out, r_out, "$1/") + regex_replace(data.n_sch, r_basename, "$1");

//check
	int ret=0;
	if(data.out_format==".m") ret=check_m();
	if(ret) return(ret);

	cout << endl;
	cout << "Input schematic : " << data.n_sch << endl;

	if(data.export_each_block) {
		unsigned int i=-1; // not a mistake
		for(shared_ptr<Block> it : data.all_blocks) {
			string out=n_out+"-b"+to_string(++i)+data.out_format;

			Block block;
			block.elements=it->elements;
			block.calcul_boundaries();
			block.elements.push_back(it->subst_local);
			for(shared_ptr<Element> element : data.tab_all) {
				if(element->getType()==".SP")
					block.elements.push_back(element);
				}

			int ret=write(block, -block.margin_boundary[XMIN], -block.margin_boundary[YMIN], out, name+"-b"+to_string(i), out_names);
			if(ret) return(ret);
			}
	} else if(data.export_each_subst) {
		unsigned int i=-1; // not a mistake
		shared_ptr<Block> prev=nullptr;
		string out;
		Block block;
		for(shared_ptr<Block> it : data.all_blocks) {
			if(prev==nullptr || it->subst!=prev->subst) {
				if(prev!=nullptr) {
					// End & write
					block.calcul_boundaries();
					out=n_out+"-s"+to_string(++i)+data.out_format;
					int ret=write(block, -block.margin_boundary[XMIN], -block.margin_boundary[YMIN], out, name+"-s"+to_string(i), out_names);
					if(ret) return(ret);
					}

				// Begin & feed
				block.elements.clear();
				block.elements=it->elements;
				block.elements.push_back(it->subst);
				for(shared_ptr<Element> element : data.tab_all) {
					if(element->getType()==".SP")
						block.elements.push_back(element);
					}
			} else {
				// Middle feed
				block.elements.insert(block.elements.end(), it->elements.begin(), it->elements.end());
				}
			prev=it;
			}
		// Last end & write
		block.calcul_boundaries();
		out=n_out+"-s"+to_string(++i)+data.out_format;
		int ret=write(block, -block.margin_boundary[XMIN], -block.margin_boundary[YMIN], out, name+"-s"+to_string(i), out_names);
		if(ret) return(ret);
	} else {
		Block block;
		block.elements=data.tab_all;
		block.calcul_boundaries();

		n_out+=data.out_format;
		return(write(block, 0, 0, n_out, name, out_names));
		}

	return(0);
	}

//******************************************************************************
int LayoutWriter::write(Block& block, long double const offset_x, long double const offset_y, string const& n_out, string const& name, vector<string>* out_names) const {
	cout << "Output layout : " << n_out << endl;
	ofstream f_out(n_out.c_str());
	if(f_out.fail()) {
		log_err << "ERROR : Unable to write " << n_out << "\n";
		return(1);
		}

	if(data.out_format==".kicad_pcb") write_kicad_pcb(block, f_out, offset_x, offset_y, name);
	else if(data.out_format==".kicad_mod") write_kicad_mod(block, f_out, offset_x, offset_y, name);
	else if(data.out_format==".lht") write_lht(block, f_out, offset_x, offset_y, name);
	else if(data.out_format==".m") write_m(block, f_out, offset_x, offset_y, name);
	if(out_names) out_names->push_back(n_out); // Success message to stdout in GUI mode

	if(f_out.fail()) {
		log_err << "ERROR : Error occured while writing " << n_out << "\n";
		return(1);
		}

	return(0);
	}

//******************************************************************************
void LayoutWriter::write_kicad_pcb(Block& block, ofstream& f_out, long double const offset_x, long double const offset_y, string const& name) const {
	string type;

	f_out << "# Generated by Qucs-RFlayout from : " << name << ".sch\n"
	         "\n"
	         "(kicad_pcb (version 0) (host pcbnew 0.0.0)\n"
	         "\n"
	         "  (general\n"
	         "    (thickness 1.6)\n"
	         "    (drawings 0)\n"
	         "    (tracks 0)\n"
	         "    (zones 0)\n"
	         "    (modules 0)\n"
	         "    (nets 1)\n"
	         "  )\n"
	         "\n"
	         "  (page A4)\n"
	         "  (layers\n"
	         "    (0 F.Cu signal)\n"
	         "    (31 B.Cu signal)\n"
	         "    (32 B.Adhes user)\n"
	         "    (33 F.Adhes user)\n"
	         "    (34 B.Paste user)\n"
	         "    (35 F.Paste user)\n"
	         "    (36 B.SilkS user)\n"
	         "    (37 F.SilkS user)\n"
	         "    (38 B.Mask user)\n"
	         "    (39 F.Mask user)\n"
	         "    (40 Dwgs.User user)\n"
	         "    (41 Cmts.User user)\n"
	         "    (42 Eco1.User user)\n"
	         "    (43 Eco2.User user)\n"
	         "    (44 Edge.Cuts user)\n"
	         "    (45 Margin user)\n"
	         "    (46 B.CrtYd user)\n"
	         "    (47 F.CrtYd user)\n"
	         "    (48 B.Fab user)\n"
	         "    (49 F.Fab user)\n"
	         "  )\n"
	         "\n"
	         "  (setup\n"
	         "    (last_trace_width 0.25)\n"
	         "    (trace_clearance 0.2)\n"
	         "    (zone_clearance 0.508)\n"
	         "    (zone_45_only no)\n"
	         "    (trace_min 0.2)\n"
	         "    (segment_width 0.2)\n"
	         "    (edge_width 0.15)\n"
	         "    (via_size 0.8)\n"
	         "    (via_drill 0.4)\n"
	         "    (via_min_size 0.4)\n"
	         "    (via_min_drill 0.3)\n"
	         "    (uvia_size 0.3)\n"
	         "    (uvia_drill 0.1)\n"
	         "    (uvias_allowed no)\n"
	         "    (uvia_min_size 0.2)\n"
	         "    (uvia_min_drill 0.1)\n"
	         "    (pcb_text_width 0.3)\n"
	         "    (pcb_text_size 1.5 1.5)\n"
	         "    (mod_edge_width 0.15)\n"
	         "    (mod_text_size 1 1)\n"
	         "    (mod_text_width 0.15)\n"
	         "    (pad_size 1.524 1.524)\n"
	         "    (pad_drill 0.762)\n"
	         "    (pad_to_mask_clearance 0.051)\n"
	         "    (solder_mask_min_width 0.25)\n"
	         "    (aux_axis_origin 0 0)\n"
	         "    (visible_elements FFFFFF7F)\n"
	         "    (pcbplotparams\n"
	         "      (layerselection 0x010fc_ffffffff)\n"
	         "      (usegerberextensions false)\n"
	         "      (usegerberattributes false)\n"
	         "      (usegerberadvancedattributes false)\n"
	         "      (creategerberjobfile false)\n"
	         "      (excludeedgelayer true)\n"
	         "      (linewidth 0.150000)\n"
	         "      (plotframeref false)\n"
	         "      (viasonmask false)\n"
	         "      (mode 1)\n"
	         "      (useauxorigin false)\n"
	         "      (hpglpennumber 1)\n"
	         "      (hpglpenspeed 20)\n"
	         "      (hpglpendiameter 15.000000)\n"
	         "      (psnegative false)\n"
	         "      (psa4output false)\n"
	         "      (plotreference true)\n"
	         "      (plotvalue true)\n"
	         "      (plotinvisibletext false)\n"
	         "      (padsonsilk false)\n"
	         "      (subtractmaskfromsilk false)\n"
	         "      (outputformat 1)\n"
	         "      (mirror false)\n"
	         "      (drillshape 1)\n"
	         "      (scaleselection 1)\n"
	         "      (outputdirectory \"\"))\n"
	         "  )\n"
	         "\n"
	         "  (net 0 \"\")\n"
	         "\n"
	         "  (net_class Default \"This is the default net class.\"\n"
	         "    (clearance 0.2)\n"
	         "    (trace_width 0.25)\n"
	         "    (via_dia 0.8)\n"
	         "    (via_drill 0.4)\n"
	         "    (uvia_dia 0.3)\n"
	         "    (uvia_drill 0.1)\n"
	         "  )\n\n";

	for(shared_ptr<Element> it : block.elements) {
		if(!it->getActive())
			continue;
		type=it->getType();
		if(type=="Pac" || type=="SUBST" || type=="MGAP" || type=="MOPEN" || type=="MSTEP") {
			//nothing to do
		} else if(type=="MCORN"
				||type=="MCROSS"
				||type=="MCOUPLED"
				||type=="MMBEND"
				||type=="MLIN"
				||type=="MRSTUB"
				||type=="MTEE") {///////////////////////////////////////////////
			f_out << "  (module " << it->getType() << " (layer F.Cu) (tedit 0) (tstamp 0)\n"
			         "    (at " << it->getX()+offset_x << " " << it->getY()+offset_y << " " << it->getR() << ")\n"
			         "    (fp_text reference " << it->getLabel() << " (at 0 0.5) (layer F.SilkS) hide\n"
			         "      (effects (font (size 0.25 0.25) (thickness 0.05)))\n"
			         "    )\n"
			         "    (fp_text value " << it->getDescriptor() << " (at 0 -0.5) (layer F.Fab) hide\n"
			         "      (effects (font (size 0.25 0.25) (thickness 0.05)))\n"
			         "    )\n";
			if(type=="MCOUPLED") {//////////////////////////////////////////////
				f_out << "    (fp_poly (pts\n";
				for(int i=0;i<it->getNpoint()/2;i++) {
					f_out << "      (xy " << it->getP(i, X, NOR, REL)
					      << " "          << it->getP(i, Y, NOR, REL) << ")\n";
					}
				f_out << "      ) (layer F.Cu) (width 0)\n    )\n"
				         "    (fp_poly (pts\n";
				for(int i=it->getNpoint()/2;i<it->getNpoint();i++) {
					f_out << "      (xy " << it->getP(i, X, NOR, REL)
					      << " "          << it->getP(i, Y, NOR, REL) << ")\n";
					}
				f_out << "      ) (layer F.Cu) (width 0)\n    )\n  )\n\n";
			} else {////////////////////////////////////////////////////////////
				f_out << "    (fp_poly (pts\n";
				for(int i=0;i<it->getNpoint();i++) {
					f_out << "      (xy " << it->getP(i, X, NOR, REL)
					      << " "          << it->getP(i, Y, NOR, REL) << ")\n";
					}
				f_out << "      ) (layer F.Cu) (width 0)\n    )\n  )\n\n";
				}
		} else if(type=="MVIA") {///////////////////////////////////////////////
			f_out << "  (via (at " << it->getX()+offset_x << " " << it->getY()+offset_y
			      << ") (size " << it->getD() << ") (drill " << it->getD() << ") (layers F.Cu B.Cu))\n\n";
			}
		}

	f_out << ")\n";
	}

//******************************************************************************
void LayoutWriter::write_kicad_mod(Block& block, ofstream& f_out, long double const offset_x, long double const offset_y, string const& name) const {
	string type;
	string label;
	smatch match;
	regex r_pac("^P([0-9]*)$"); //g1 number // TODO getN() ?

	f_out << "# Generated by Qucs-RFlayout from : " << name << ".sch\n"
	         "\n"
	         "(module " << name << " (layer F.Cu) (tedit 5BD7B6BE)\n"
	         "  (fp_text reference REF** (at 0 0.5) (layer F.SilkS)\n"
	         "    (effects (font (size 1 1) (thickness 0.15)))\n"
	         "  )\n"
	         "  (fp_text value " << name << " (at 0 -0.5) (layer F.Fab)\n"
	         "    (effects (font (size 1 1) (thickness 0.15)))\n"
	         "  )\n";

	for(shared_ptr<Element> it : block.elements) {
		if(!it->getActive())
			continue;
		type=it->getType();
		if(type=="SUBST" || type=="MGAP" || type=="MOPEN" || type=="MSTEP") {
			//nothing to do
		} else if(type=="Pac") {////////////////////////////////////////////////
			label=it->getLabel();
			Pac* pac=dynamic_cast<Pac*>(it.get());
			regex_search(label, match, r_pac);
			f_out << "    (pad \"" << match.str(1) << "\" smd rect (at " << it->getX()+offset_x << " " << it->getY()+offset_y
			      << " " << it->getR() << ") (size " << (pac->is_size_set ? it->getW() : 0.01) << " " << (pac->is_size_set ? it->getL() : 0.01) << ") (layers F.Cu))\n";
		} else if(type=="MCORN"
				||type=="MCROSS"
				||type=="MMBEND"
				||type=="MLIN"
				||type=="MRSTUB"
				||type=="MTEE") {///////////////////////////////////////////////
			f_out << "    (fp_poly (pts\n";
			for(int i=0;i<it->getNpoint();i++) {
				f_out << "      (xy " << it->getP(i, X, R, ABS)+offset_x
				      << " "          << it->getP(i, Y, R, ABS)+offset_y << ")\n";
				}
			f_out << "      ) (layer F.Cu) (width 0)\n    )\n";
		} else if(type=="MCOUPLED") {///////////////////////////////////////////
			f_out << "    (fp_poly (pts\n";
			for(int i=0;i<it->getNpoint()/2;i++) {
				f_out << "      (xy " << it->getP(i, X, R, ABS)+offset_x
				      << " "          << it->getP(i, Y, R, ABS)+offset_y << ")\n";
				}
			f_out << "      ) (layer F.Cu) (width 0)\n    )\n"
			         "    (fp_poly (pts\n";
			for(int i=it->getNpoint()/2;i<it->getNpoint();i++) {
				f_out << "      (xy " << it->getP(i, X, R, ABS)+offset_x
				      << " "          << it->getP(i, Y, R, ABS)+offset_y << ")\n";
				}
			f_out << "      ) (layer F.Cu) (width 0)\n    )\n";
		} else if(type=="MVIA") {///////////////////////////////////////////////
			f_out << "  (pad \"\" thru_hole circle (at " << it->getX()+offset_x << " " << it->getY()+offset_y
			      << ") (size " << it->getD() << " " << it->getD() << ") (drill " << it->getD() << ") (layers *.Cu))\n";
			}
		}

	f_out << ")\n";
	}

//******************************************************************************
void LayoutWriter::write_lht(Block& block, ofstream& f_out, long double const offset_x, long double const offset_y, string const& name) const {
	string type;
	unsigned int n=0;

	f_out << "# Generated by Qucs-RFlayout from : " << name << ".sch\n"
	         "\n"
	         "ha:pcb-rnd-board-v4 {\n"
	         "\n"
	         " ha:attributes {\n"
	         "   {PCB::grid::unit}=mm\n"
	         " }\n"
	         "\n"
	         " li:styles {\n"
	         "   ha:Signal {\n"
	         "    diameter = 2.0mm\n"
	         "    thickness = 10.0mil\n"
	         "    hole = 31.5mil\n"
	         "    clearance = 20.0mil\n"
	         "   }\n"
	         "   ha:Power {\n"
	         "    diameter = 2.2mm\n"
	         "    thickness = 20.0mil\n"
	         "    hole = 1.0mm\n"
	         "    clearance = 20.0mil\n"
	         "   }\n"
	         "   ha:Fat {\n"
	         "    diameter = 137.8mil\n"
	         "    thickness = 80.0mil\n"
	         "    hole = 47.24mil\n"
	         "    clearance = 25.0mil\n"
	         "   }\n"
	         "   ha:Sig-tight {\n"
	         "    diameter = 64.0mil\n"
	         "    thickness = 10.0mil\n"
	         "    hole = 31.5mil\n"
	         "    clearance = 12.0mil\n"
	         "   }\n"
	         " }\n"
	         "\n"
	         " ha:meta {\n"
	         "   ha:size {\n"
	         "    thermal_scale = 0.500000\n"
	         "    x = " << block.margin_boundary[XMAX]+offset_x << "mm\n" //TODO
	         "    y = " << block.margin_boundary[YMAX]+offset_y << "mm\n"
	         "    isle_area_nm2 = 200000000.000000\n"
	         "   }\n"
	         "   ha:cursor {\n"
	         "    zoom = 1.000000\n"
	         "    x = 0.0\n"
	         "    y = 0.0\n"
	         "   }\n"
	         "   ha:drc {\n"
	         "    min_drill = 15.0mil\n"
	         "    min_ring = 10.0mil\n"
	         "    bloat = 12.0mil\n"
	         "    shrink = 9.0mil\n"
	         "    min_width = 10.0mil\n"
	         "    min_silk = 7.0mil\n"
	         "   }\n"
	         "   ha:grid {\n"
	         "    spacing = 0.1mm\n"
	         "    offs_x = 0.0\n"
	         "    offs_y = 0.0\n"
	         "   }\n"
	         " }\n"
	         "\n"
	         " ha:data {\n"
	         "  li:padstack_prototypes {\n"
	         "  }\n"
	         "\n"
	         "   li:objects {\n";

	for(shared_ptr<Element> it : block.elements) {
		if(!it->getActive())
			continue;
		type=it->getType();
		//if(type=="Pac" || type=="SUBST" || type=="MGAP" || type=="MOPEN" || type=="MSTEP")
			//nothing to do
		if(type=="MVIA") {
			f_out << "    ha:via." << n++ << " {"
			         "     x=" << it->getX()+offset_x << "mm; y=" << it->getY()+offset_y << "mm; hole=" << it->getD() << "mm; mask=0.0; thickness=" << it->getR() << "mm; clearance=0mm;\n"
			         "     ha:flags {\n"
			         "      via=1\n"
			         "     }\n"
			         "    }\n";
			}
		}

	f_out << "   }\n"
	         "   li:layers {\n"
	         "\n"
	         "    ha:top-sig {\n"
	         "     lid=0\n"
	         "     group=3\n"
	         "     ha:combining {     }\n"
	         "     visible=1\n"
	         "\n"
	         "      li:objects {\n";

	for(shared_ptr<Element> it : block.elements) {
		if(!it->getActive())
			continue;
		type=it->getType();
		if(type=="MCORN"
        || type=="MCROSS"
        || type=="MMBEND"
        || type=="MLIN"
        || type=="MRSTUB"
        || type=="MTEE") {
			f_out << "       ha:polygon." << n++ << " { clearance=0mm;\n"
			         "        li:geometry {\n"
			         "          ta:contour {\n";
			for(int i=0;i<it->getNpoint();i++) {
				f_out << "           { "
					  << it->getP(i, X, R, ABS)+offset_x << "mm; "
					  << it->getP(i, Y, R, ABS)+offset_y << "mm }\n";
				}
			f_out << "          }\n"
			         "        }\n"
			         "\n"
			         "        ha:flags {\n"
			         "         clearpoly=1\n"
			         "        }\n"
			         "       }\n";
		} else if(type=="MCOUPLED") {
			f_out << "       ha:polygon." << n++ << " { clearance=0mm;\n"
			         "        li:geometry {\n"
			         "          ta:contour {\n";
			for(int i=0;i<it->getNpoint()/2;i++) {
				f_out << "           { "
					  << it->getP(i, X, R, ABS)+offset_x << "mm; "
					  << it->getP(i, Y, R, ABS)+offset_y << "mm }\n";
				}
			f_out << "          }\n"
			         "        }\n"
			         "\n"
			         "        ha:flags {\n"
			         "         clearpoly=1\n"
			         "        }\n"
			         "       }\n";
			f_out << "       ha:polygon." << n++ << " { clearance=0mm;\n"
			         "        li:geometry {\n"
			         "          ta:contour {\n";
			for(int i=it->getNpoint()/2;i<it->getNpoint();i++) {
				f_out << "           { "
					  << it->getP(i, X, R, ABS)+offset_x << "mm; "
					  << it->getP(i, Y, R, ABS)+offset_y << "mm }\n";
				}
			f_out << "          }\n"
			         "        }\n"
			         "\n"
			         "        ha:flags {\n"
			         "         clearpoly=1\n"
			         "        }\n"
			         "       }\n";
			}
		}

	f_out << "      }\n"
	         "    }\n"
	         "\n"
	         "    ha:bottom-sig {\n"
	         "     lid=1\n"
	         "     group=10\n"
	         "     ha:combining {     }\n"
	         "     visible=1\n"
	         "\n"
	         "      li:objects {\n"
	         "      }\n"
	         "    }\n"
	         "\n"
	         "    ha:top-gnd {\n"
	         "     lid=2\n"
	         "     group=3\n"
	         "     ha:combining {     }\n"
	         "     visible=1\n"
	         "\n"
	         "      li:objects {\n"
	         "      }\n"
	         "    }\n"
	         "\n"
	         "    ha:bottom-gnd {\n"
	         "     lid=3\n"
	         "     group=10\n"
	         "     ha:combining {     }\n"
	         "     visible=1\n"
	         "\n"
	         "      li:objects {\n"
	         "      }\n"
	         "    }\n"
	         "\n"
	         "    ha:int-sig2 {\n"
	         "     lid=4\n"
	         "     group=7\n"
	         "     ha:combining {     }\n"
	         "     visible=1\n"
	         "\n"
	         "      li:objects {\n"
	         "      }\n"
	         "    }\n"
	         "\n"
	         "    ha:int-sig1 {\n"
	         "     lid=5\n"
	         "     group=5\n"
	         "     ha:combining {     }\n"
	         "     visible=1\n"
	         "\n"
	         "      li:objects {\n"
	         "      }\n"
	         "    }\n"
	         "\n"
	         "    ha:outline {\n"
	         "     lid=6\n"
	         "     group=9\n"
	         "     ha:combining {     }\n"
	         "     visible=1\n"
	         "\n"
	         "      li:objects {\n"
	         "      }\n"
	         "    }\n"
	         "\n"
	         "    ha:bottom-silk {\n"
	         "     lid=7\n"
	         "     group=12\n"
	         "     ha:combining { auto=1;     }\n"
	         "     visible=1\n"
	         "\n"
	         "      li:objects {\n"
	         "      }\n"
	         "    }\n"
	         "\n"
	         "    ha:top-silk {\n"
	         "     lid=8\n"
	         "     group=1\n"
	         "     ha:combining { auto=1;     }\n"
	         "     visible=1\n"
	         "\n"
	         "      li:objects {\n"
	         "      }\n"
	         "    }\n"
	         "\n"
	         "    ha:top-paste {\n"
	         "     lid=9\n"
	         "     group=0\n"
	         "     ha:combining { auto=1;     }\n"
	         "     visible=0\n"
	         "\n"
	         "      li:objects {\n"
	         "      }\n"
	         "    }\n"
	         "\n"
	         "    ha:top-mask {\n"
	         "     lid=10\n"
	         "     group=2\n"
	         "     ha:combining { sub=1; auto=1;     }\n"
	         "     visible=0\n"
	         "\n"
	         "      li:objects {\n"
	         "      }\n"
	         "    }\n"
	         "\n"
	         "    ha:bottom-mask {\n"
	         "     lid=11\n"
	         "     group=11\n"
	         "     ha:combining { sub=1; auto=1;     }\n"
	         "     visible=0\n"
	         "\n"
	         "      li:objects {\n"
	         "      }\n"
	         "    }\n"
	         "\n"
	         "    ha:bottom-paste {\n"
	         "     lid=12\n"
	         "     group=13\n"
	         "     ha:combining { auto=1;     }\n"
	         "     visible=0\n"
	         "\n"
	         "      li:objects {\n"
	         "      }\n"
	         "    }\n"
	         "   }\n"
	         " }\n"
	         "\n" +
	         pcbrnd_lht::fonts +
	         "\n"
	         " ha:netlists {\n"
	         "   li:input {\n"
	         "   }\n"
	         " }\n"
	         " ha:layer_stack {\n"
	         "  li:groups {\n"
	         "   ha:0 {\n"
	         "    name = top_paste\n"
	         "    ha:type { top=1; paste=1;    }\n"
	         "    li:layers { 9;    }\n"
	         "   }\n"
	         "   ha:1 {\n"
	         "    name = top_silk\n"
	         "    ha:type { silk=1; top=1;    }\n"
	         "    li:layers { 8;    }\n"
	         "   }\n"
	         "   ha:2 {\n"
	         "    name = top_mask\n"
	         "    ha:type { top=1; mask=1;    }\n"
	         "    li:layers { 10;    }\n"
	         "   }\n"
	         "   ha:3 {\n"
	         "    name = top_copper\n"
	         "    ha:type { copper=1; top=1;    }\n"
	         "    li:layers { 0; 2;    }\n"
	         "   }\n"
	         "   ha:4 {\n"
	         "    name = grp_4\n"
	         "    ha:type { substrate=1; intern=1;    }\n"
	         "    li:layers {    }\n"
	         "   }\n"
	         "   ha:5 {\n"
	         "    name = Intern\n"
	         "    ha:type { copper=1; intern=1;    }\n"
	         "    li:layers { 5;    }\n"
	         "   }\n"
	         "   ha:6 {\n"
	         "    name = grp_6\n"
	         "    ha:type { substrate=1; intern=1;    }\n"
	         "    li:layers {    }\n"
	         "   }\n"
	         "   ha:7 {\n"
	         "    name = Intern\n"
	         "    ha:type { copper=1; intern=1;    }\n"
	         "    li:layers { 4;    }\n"
	         "   }\n"
	         "   ha:8 {\n"
	         "    name = grp_8\n"
	         "    ha:type { substrate=1; intern=1;    }\n"
	         "    li:layers {    }\n"
	         "   }\n"
	         "   ha:9 {\n"
	         "    name = global outline\n"
	         "    ha:type { outline=1; intern=1;    }\n"
	         "    li:layers { 6;    }\n"
	         "   }\n"
	         "   ha:10 {\n"
	         "    name = bottom_copper\n"
	         "    ha:type { bottom=1; copper=1;    }\n"
	         "    li:layers { 1; 3;    }\n"
	         "   }\n"
	         "   ha:11 {\n"
	         "    name = bottom_mask\n"
	         "    ha:type { bottom=1; mask=1;    }\n"
	         "    li:layers { 11;    }\n"
	         "   }\n"
	         "   ha:12 {\n"
	         "    name = bottom_silk\n"
	         "    ha:type { silk=1; bottom=1;    }\n"
	         "    li:layers { 7;    }\n"
	         "   }\n"
	         "   ha:13 {\n"
	         "    name = bottom_paste\n"
	         "    ha:type { bottom=1; paste=1;    }\n"
	         "    li:layers { 12;    }\n"
	         "   }\n"
	         "  }\n"
	         " }\n"
	         " li:pcb-rnd-conf-v1 {\n"
	         "  ha:overwrite {\n"
	         "   ha:design {\n"
	         "    min_ring = 10.00 mil\n"
	         "    clearance = 0 mil\n"
	         "    via_thickness = 2.0000 mm\n"
	         "    via_drilling_hole = 31.50 mil\n"
	         "    min_slk = 0 mil\n"
	         "    max_height = 5.00000 in\n"
	         "    line_thickness = 0 mil\n"
	         "    shrink = 9.00 mil\n"
	         "    poly_isle_area = 200000000.2\n"
	         "    max_width = 6.00000 in\n"
	         "    min_wid = 0 mil\n"
	         "    bloat = 12.00 mil\n"
	         "    min_drill = 15.00 mil\n"
	         "   }\n"
	         "   ha:editor {\n"
	         "    grid_unit = mm\n"
	         "     grid = 0.01 mil\n"
	         "   }\n"
	         "  }\n"
	         " }\n"
	         "}\n";
	}

//******************************************************************************
int LayoutWriter::check_m() const {
	if(data.is_volume_error) {
		log_err << data.volume_error;
		return(1);
		}

	bool is_first_sp=true;
	for(shared_ptr<Element> it : data.tab_all) {
		if(it->getType()==".SP") {
			if(is_first_sp==false) {
				log_err << "ERROR : More than 1 active S parameter simulation.\n";
				return(1);
				}
			is_first_sp=false;
			}
		}

	if(data.oems_nf2ff_center!="") {
		bool is_nf2ff_center_valid=false;
		for(shared_ptr<Element> it : data.tab_all) {
			if(it->getLabel()==data.oems_nf2ff_center) {
				is_nf2ff_center_valid=true;
				break;
				}
			}
		if(!is_nf2ff_center_valid) {
			log_err << "ERROR : Invalid NF2FF center : " << data.oems_nf2ff_center << ".\n";
			return(1);
			}
		}

	return(0);
	}

//******************************************************************************
void LayoutWriter::write_m(Block& block, std::ofstream& f_out, long double const offset_x, long double const offset_y, std::string const& name) const {
	string type;
	string label;
	long double extrem_pos_zmin=0.0;
	long double extrem_pos_zmax=0.0;

	OemsMesh const mesh(block.elements, data.oems_sort_metalresmesh);

	// Need to store ports ordered.
	vector<pair<unsigned int, shared_ptr<Element>>> ports;
	for(shared_ptr<Element> it : block.elements) {
		if(it->getType()=="Pac") {
			ports.push_back(make_pair((unsigned int)it->getN(), it));
			}
		}
	sort(begin(ports), end(ports));

	f_out << "#!/usr/bin/octave\n"
	         "\n"
	         "%%%% OpenEMS script generated by Qucs-RFlayout from : " << name << ".sch\n"
	         "\n"
	         "clear;\n"
	         "close all;\n"
	         "% Uncomment to use the Debian 10 openems package\n" <<
	         (data.oems_pkg ? "" : "%") << "pkg load openems;\n" <<
	         (data.oems_pkg ? "" : "%") << "pkg load csxcad;\n"
	         "\n";

	f_out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FUNCTIONS\n"
	         "\n"
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n" + 
	         oems_m::write_touchstone_m +
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
	         "\n"
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n" + 
	         oems_m::plotFF3D_frames +
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
	         "\n"
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n" +
	         oems_m::plotSmith +
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
	         "\n"
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n" + 
	         oems_m::oemsgen_cli +
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
	         "\n"
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n" +
	         oems_m::oemsgen_plotVSWR +
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
	         "\n"
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n" +
	         oems_m::oemsgen_plotFeedImpedance +
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
	         "\n"
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n" +
	         oems_m::oemsgen_plotSParameters +
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
	         "\n"
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n" +
	         oems_m::oemsgen_plotSmithChart +
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
	         "\n"
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n" +
	         oems_m::oemsgen_plotPhaseResponse +
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
	         "\n"
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n" +
	         oems_m::oemsgen_plotPhaseDelay +
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
	         "\n"
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n" +
	         oems_m::oemsgen_plotGroupDelay +
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
	         "\n"
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n" +
	         oems_m::oemsgen_postProcess +
	         "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n"
	         "\n";

	f_out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% CLI\n"
	         "\n"
	         "cli = oemsgen_cli(argv(), '" << name << "', [";
	for(pair<unsigned int, shared_ptr<Element>> it : ports) {
		f_out << it.first << (it==ports.back() ? "" : ", ");
		}
	f_out << "], ...\n"
	         "\t'header', 'OpenEMS Octave script generated by Qucs-RFlayout from : " << name << ".sch');\n"
	         "\n";

	f_out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% PREPROCESSING\n"
	         "\n";

	f_out << "%%%% VARIABLES\n"
	         "t_preprocess_start = clock();\n"
	         "physical_constants;\n";
	bool is_there_sp=false;
	for(shared_ptr<Element> it : block.elements) {
		if(it->getType()==".SP") {
			is_there_sp=true;
			f_out << "fstart = " << it->getFstart() << ";\n"
			         "fstop = " << it->getFstop() << ";\n"
			         "points = " << it->getN() << ";\n";
			}
		}
	if(!is_there_sp) {
		f_out << "fstart = ;\n"
		         "fstop = ;\n"
		         "points = ;\n";
		log_err << "WARNING : No active S parameter simulation in the schematic, you will have to set simulation frequencies manually.\n"; //TODO disp("set & rm this plz")
		}
	f_out << "f0 = (fstop + fstart) / 2; % Center frequency\n"
	         "fc = (fstop - fstart) / 2; % Cutoff frequency\n"
	         "unit = 1e-3;\n"
	         "lambda = c0 / (f0 + fc) / unit;\n"
	         "high_div = " << data.oems_highres_div << ";        % Depend on your simulation, you may want to tweak this value\n"
	         "metal_div = " << data.oems_metalres_div << ";        % Depend on your simulation, you may want to tweak this value\n"
	         "substrate_div = "<< data.oems_substres_div << ";    % Depend on your simulation, you may want to tweak this value\n"
	         "time_res = " << data.oems_timeres << ";     % Depend on your simulation, you may want to tweak this value\n"
	         "high_res = lambda / high_div;\n"
	         "metal_res = lambda / metal_div;\n"
	         "substrate_res = lambda / substrate_div;\n"
	         "end_criteria = " << data.oems_end_criteria << ";\n"
	         "csx_file = '" << name << ".csx';\n"
	         "\n";

	f_out << "%%%% SUBSTRATES\n"
	         "CSX = InitCSX();\n"
	         "if cli.preprocess\n"
	         "\n";

	for(shared_ptr<Element> it : block.elements) {
		type=it->getType();
		if(type=="SUBST") {
//			if(-it->getH()-it->getT()-it->getMargin()<extrem_pos_zmin) extrem_pos_zmin=-it->getH()-it->getT()-it->getMargin();
//			if(it->getT()+it->getMargin()>extrem_pos_zmax) extrem_pos_zmax=it->getT()+it->getMargin();
			if(-it->getH()-it->getT()<extrem_pos_zmin) extrem_pos_zmin=-it->getH()-it->getT();
			if(it->getT()>extrem_pos_zmax) extrem_pos_zmax=it->getT();
			f_out << "% " << it->getLabel() << " : " << type << "\n"
			         "endif % cli.preprocess\n" <<
			         it->getLabel() << ".metal.t = (" << it->getT() << ");\n" <<
			         it->getLabel() << ".metal.rho = (" << it->getRho() << ");\n" <<
			         it->getLabel() << ".metal.cond = (1 / " << it->getLabel() << ".metal.rho);\n" <<
			         it->getLabel() << ".center = [" << it->getX()+offset_x << ", " << -(it->getY()+offset_y) << ", " << it->getLabel() << ".metal.t];\n" <<
			         it->getLabel() << ".substrate.tand = (" << it->getTand() << ");\n" <<
			         it->getLabel() << ".substrate.Er = (" << it->getEr() << ");\n" <<
			         it->getLabel() << ".substrate.K = (" << it->getLabel() << ".substrate.tand * 2 * pi * f0 * EPS0 * " << it->getLabel() << ".substrate.Er);\n" <<
			         it->getLabel() << ".substrate.h = (" << it->getH() << ");\n" <<
			         it->getLabel() << ".substrate.L = (" << it->getL() << ");\n" <<
			         it->getLabel() << ".substrate.W = (" << it->getW() << ");\n" <<
			         it->getLabel() << ".dump.start = [" << it->getP(0, X, R, ABS)+offset_x << ", " << -(it->getP(0, Y, R, ABS)+offset_y) << ", (" << it->getLabel() << ".metal.t/2)];\n" <<
			         it->getLabel() << ".dump.stop = [" << it->getP(2, X, R, ABS)+offset_x << ", " << -(it->getP(2, Y, R, ABS)+offset_y) << ", (" << it->getLabel() << ".metal.t/2)];\n"
//			         it->getLabel() << ".cells = (" << "" << ");\n" << //TODO z mesh division
			         "if cli.preprocess\n"
			         "CSX = AddMaterial(CSX, '" << it->getLabel() << ".substrate');\n"
			         "CSX = SetMaterialProperty(CSX, '" << it->getLabel() << ".substrate', ...\n"
			         "\t'Epsilon', " << it->getLabel() << ".substrate.Er, ...\n"
			         "\t'Kappa', " << it->getLabel() << ".substrate.K);\n"
			         "CSX = AddBox(CSX, '" << it->getLabel() << ".substrate', 1, ...\n"
			         "\t[" << it->getP(0, X, R, ABS)+offset_x << ", " << -(it->getP(0, Y, R, ABS)+offset_y) << ", -" << it->getLabel() << ".substrate.h], ...\n"
			         "\t[" << it->getP(2, X, R, ABS)+offset_x << ", " << -(it->getP(2, Y, R, ABS)+offset_y) << ", 0]);\n"
//			         "CSX = AddMetal(CSX, '" << it->getLabel() << ".metal');\n"
//			         "%CSX = AddConductingSheet(CSX, '" << it->getLabel() << ".metal', " << it->getLabel() << ".metal.cond, " << it->getLabel() << ".metal.t*unit);\n" //TODO thickness? wtf & not well tested
//			         "if cli.smallbox == false\n"
			         "if cli.conductingsheet\n"
			         "CSX = AddConductingSheet(CSX, '" << it->getLabel() << ".ground', " << it->getLabel() << ".metal.cond, " << it->getLabel() << ".metal.t*unit);\n"
			         "CSX = AddBox(CSX, '" << it->getLabel() << ".ground', 2, ...\n"
			         "\t[" << it->getP(0, X, R, ABS)+offset_x << ", " << -(it->getP(0, Y, R, ABS)+offset_y) << ", -" << it->getLabel() << ".substrate.h], ...\n"
			         "\t[" << it->getP(2, X, R, ABS)+offset_x << ", " << -(it->getP(2, Y, R, ABS)+offset_y) << ", -" << it->getLabel() << ".substrate.h]);\n"
			         "else % cli.conductingsheet\n"
			         "CSX = AddMetal(CSX, '" << it->getLabel() << ".ground');\n"
			         "CSX = AddBox(CSX, '" << it->getLabel() << ".ground', 2, ...\n"
			         "\t[" << it->getP(0, X, R, ABS)+offset_x << ", " << -(it->getP(0, Y, R, ABS)+offset_y) << ", (-" << it->getLabel() << ".substrate.h - " << it->getLabel() << ".metal.t)], ...\n"
			         "\t[" << it->getP(2, X, R, ABS)+offset_x << ", " << -(it->getP(2, Y, R, ABS)+offset_y) << ", -" << it->getLabel() << ".substrate.h]);\n"
			         "endif % cli.conductingsheet\n"
//			         "endif % cli.smallbox == false\n"
			         "\n";
			}
		}

	f_out << "%%%% SHAPES\n";
	for(shared_ptr<Element> it : block.elements) {
		if(!it->getActive())
			continue;
		type=it->getType();
		if(type=="MGAP" || type=="MOPEN" || type=="MSTEP") {
			//nothing to do
		} else if(type=="MCORN"
		       || type=="MLIN") {
			f_out << "% " << it->getLabel() << " : " << type << "\n"
			         "endif % cli.preprocess\n" <<
			         it->getLabel() << ".center = [" << it->getX()+offset_x << ", " << -(it->getY()+offset_y) << ", " << it->getSubst() << ".metal.t];\n"
			         "if cli.preprocess\n"
			         "if cli.conductingsheet\n"
			         "CSX = AddConductingSheet(CSX, '" << it->getLabel() << "', " << it->getSubst() << ".metal.cond, " << it->getSubst() << ".metal.t*unit);\n"
			         "CSX = AddBox(CSX, '" << it->getLabel() << "', 2, ...\n"
//			         "CSX = AddBox(CSX, '" << it->getSubst() << ".metal', 1, ...\n"
			         "\t[" << it->getP(0, X, R, ABS)+offset_x << ", " << -(it->getP(0, Y, R, ABS)+offset_y) << ", 0], ...\n"
			         "\t[" << it->getP(2, X, R, ABS)+offset_x << ", " << -(it->getP(2, Y, R, ABS)+offset_y) << ", 0]);\n"
			         "else % cli.conductingsheet\n"
			         "CSX = AddMetal(CSX, '" << it->getLabel() << "');\n"
			         "CSX = AddBox(CSX, '" << it->getLabel() << "', 2, ...\n"
//			         "CSX = AddBox(CSX, '" << it->getSubst() << ".metal', 1, ...\n"
			         "\t[" << it->getP(0, X, R, ABS)+offset_x << ", " << -(it->getP(0, Y, R, ABS)+offset_y) << ", 0], ...\n"
			         "\t[" << it->getP(2, X, R, ABS)+offset_x << ", " << -(it->getP(2, Y, R, ABS)+offset_y) << ", " << it->getSubst() << ".metal.t]);\n"
			         "endif % cli.conductingsheet\n"
			         "\n";
		} else if(type=="MCOUPLED") {
			f_out << "% " << it->getLabel() << " : " << type << "\n"
			         "endif % cli.preprocess\n" <<
			         it->getLabel() << ".center = [" << it->getX()+offset_x << ", " << -(it->getY()+offset_y) << ", " << it->getSubst() << ".metal.t];\n"
			         "if cli.preprocess\n"
			         "if cli.conductingsheet\n"
			         "CSX = AddConductingSheet(CSX, '" << it->getLabel() << "', " << it->getSubst() << ".metal.cond, " << it->getSubst() << ".metal.t*unit);\n"
			         "CSX = AddBox(CSX, '" << it->getLabel() << "', 2, ...\n"
//			         "CSX = AddBox(CSX, '" << it->getSubst() << ".metal', 1, ...\n"
			         "\t[" << it->getP(0, X, R, ABS)+offset_x << ", " << -(it->getP(0, Y, R, ABS)+offset_y) << ", 0], ...\n"
			         "\t[" << it->getP(2, X, R, ABS)+offset_x << ", " << -(it->getP(2, Y, R, ABS)+offset_y) << ", 0]);\n"
			         "CSX = AddBox(CSX, '" << it->getLabel() << "', 2, ...\n"
//			         "CSX = AddBox(CSX, '" << it->getSubst() << ".metal', 1, ...\n"
			         "\t[" << it->getP(4, X, R, ABS)+offset_x << ", " << -(it->getP(4, Y, R, ABS)+offset_y) << ", 0], ...\n"
			         "\t[" << it->getP(6, X, R, ABS)+offset_x << ", " << -(it->getP(6, Y, R, ABS)+offset_y) << ", 0]);\n"
			         "else % cli.conductingsheet\n"
			         "CSX = AddMetal(CSX, '" << it->getLabel() << "');\n"
			         "CSX = AddBox(CSX, '" << it->getLabel() << "', 2, ...\n"
//			         "CSX = AddBox(CSX, '" << it->getSubst() << ".metal', 1, ...\n"
			         "\t[" << it->getP(0, X, R, ABS)+offset_x << ", " << -(it->getP(0, Y, R, ABS)+offset_y) << ", 0], ...\n"
			         "\t[" << it->getP(2, X, R, ABS)+offset_x << ", " << -(it->getP(2, Y, R, ABS)+offset_y) << ", " << it->getSubst() << ".metal.t]);\n"
			         "CSX = AddBox(CSX, '" << it->getLabel() << "', 2, ...\n"
//			         "CSX = AddBox(CSX, '" << it->getSubst() << ".metal', 1, ...\n"
			         "\t[" << it->getP(4, X, R, ABS)+offset_x << ", " << -(it->getP(4, Y, R, ABS)+offset_y) << ", 0], ...\n"
			         "\t[" << it->getP(6, X, R, ABS)+offset_x << ", " << -(it->getP(6, Y, R, ABS)+offset_y) << ", " << it->getSubst() << ".metal.t]);\n"
			         "endif % cli.conductingsheet\n"
			         "\n";
		} else if(type=="MCROSS"
		       || type=="MMBEND"
		       || type=="MRSTUB"
		       || type=="MTEE") {
			f_out << "% " << it->getLabel() << " : " << type << "\n"
			         "endif % cli.preprocess\n" <<
			         it->getLabel() << ".center = [" << it->getX()+offset_x << ", " << -(it->getY()+offset_y) << ", " << it->getSubst() << ".metal.t];\n"
			         "if cli.preprocess\n"
			         "p = zeros(2, " << it->getNpoint() << ");\n";
			for(int i=0;i<it->getNpoint();i++) {
				f_out << "p(1, " << i+1 << ") = " << it->getP(i, X, R, ABS)+offset_x << "; p(2, " << i+1 << ") = " << -(it->getP(i, Y, R, ABS)+offset_y) << ";\n";
				}
			f_out << "if cli.conductingsheet\n"
			         "CSX = AddConductingSheet(CSX, '" << it->getLabel() << "', " << it->getSubst() << ".metal.cond, " << it->getSubst() << ".metal.t*unit);\n"
			         "CSX = AddLinPoly(CSX, '" << it->getLabel() << "', 2, 2, 0, p, 0);\n"
//			f_out << "CSX = AddLinPoly(CSX, '" << it->getSubst() << ".metal', 1, 2, 0, p, " << it->getSubst() << ".metal.t);\n"
			         "else % cli.conductingsheet\n"
			         "CSX = AddMetal(CSX, '" << it->getLabel() << "');\n"
			         "CSX = AddLinPoly(CSX, '" << it->getLabel() << "', 2, 2, 0, p, " << it->getSubst() << ".metal.t);\n"
//			f_out << "CSX = AddLinPoly(CSX, '" << it->getSubst() << ".metal', 1, 2, 0, p, " << it->getSubst() << ".metal.t);\n"
			         "endif % cli.conductingsheet\n"
			         "\n";
		} else if(type=="MVIA") {
			f_out << "% " << it->getLabel() << " : " << type << "\n"
			         "endif % cli.preprocess\n" <<
			         it->getLabel() << ".center = [" << it->getX()+offset_x << ", " << -(it->getY()+offset_y) << ", " << it->getSubst() << ".metal.t];\n"
			         "if cli.preprocess\n"
			         "if cli.conductingsheet\n"
			         "CSX = AddConductingSheet(CSX, '" << it->getLabel() << "', " << it->getSubst() << ".metal.cond, " << it->getSubst() << ".metal.t*unit);\n"
			         "CSX = AddBox(CSX, '" << it->getLabel() << "', 2, ...\n"
//			         "CSX = AddBox(CSX, '" << it->getSubst() << ".metal', 1, ...\n"
			         "\t[" << it->getX()+it->getD()/2+offset_x << ", " << -(it->getY()+it->getD()/2+offset_y) << ", (-" << it->getSubst() << ".substrate.h)], ...\n"
			         "\t[" << it->getX()-it->getD()/2+offset_x << ", " << -(it->getY()-it->getD()/2+offset_y) << ", 0]);\n"
			         "else % cli.conductingsheet\n"
			         "CSX = AddMetal(CSX, '" << it->getLabel() << "');\n"
			         "CSX = AddBox(CSX, '" << it->getLabel() << "', 2, ...\n"
//			         "CSX = AddBox(CSX, '" << it->getSubst() << ".metal', 1, ...\n"
			         "\t[" << it->getX()+it->getD()/2+offset_x << ", " << -(it->getY()+it->getD()/2+offset_y) << ", (-" << it->getSubst() << ".substrate.h - " << it->getSubst() << ".metal.t)], ...\n"
			         "\t[" << it->getX()-it->getD()/2+offset_x << ", " << -(it->getY()-it->getD()/2+offset_y) << ", " << it->getSubst() << ".metal.t]);\n"
			         "endif % cli.conductingsheet\n"
			         "\n";
			}
		}

	f_out << "%%%% MESH\n"
	         "endif % cli.preprocess\n"
	         "mesh.x = [];\n"
	         "mesh.y = [];\n"
	         "mesh.z = [];\n"
	         "if cli.preprocess\n"
	         "if cli.mesh\n"
	         "\n";

	f_out << "% High resolution mesh for non orthogonal shapes\n"
	         "if cli.highresmesh\n"
	         "mesh.x = [mesh.x, ...\n";
	for(auto line=begin(mesh.x);line<end(mesh.x);++line) {
		if(line->high_res && next(line)!=end(mesh.x) && next(line)->high_res && line->label==next(line)->label) {
			f_out << "\t(linspace(";
			for(unsigned int i=0;i<2;i++) {
				advance(line, i);
				if(line->third_rule) {
					switch(line->direction) {
						case XMIN: f_out << "(" << line->position+offset_x << " - 2*high_res/3), "; break;
						case XMAX: f_out << "(" << line->position+offset_x << " + 2*high_res/3), "; break;
						}
				} else {
					f_out << "(" << line->position+offset_x << "), ";
					}
				}
			advance(line, -1);
			f_out << "(abs(";
			for(unsigned int i=0;i<2;i++) {
				advance(line, i);
				if(line->third_rule) {
					switch(line->direction) {
						case XMIN: f_out << "(" << line->position+offset_x << " - 2*high_res/3)"; break;
						case XMAX: f_out << "(" << line->position+offset_x << " + 2*high_res/3)"; break;
						}
				} else {
					f_out << "(" << line->position+offset_x << ")";
					}
				if(i==0) {
					f_out << " - ";
					}
				}
			f_out << ") / high_res))), ... % " << line->label << " : " << line->type << "\n";
			}
		}
	f_out << "\t];\n"
	         "mesh.y = [mesh.y, ...\n";
	for(auto line=begin(mesh.y);line<end(mesh.y);++line) {
		if(line->high_res && next(line)!=end(mesh.y) && next(line)->high_res && line->label==next(line)->label) {
			f_out << "\t(linspace(";
			for(unsigned int i=0;i<2;i++) {
				advance(line, i);
				if(line->third_rule) {
					switch(line->direction) {
						case YMIN: f_out << "(" << -(line->position+offset_y) << " + 2*high_res/3), "; break;
						case YMAX: f_out << "(" << -(line->position+offset_y) << " - 2*high_res/3), "; break;
						}
				} else {
					f_out << "(" << -(line->position+offset_y) << "), ";
					}
				}
			advance(line, -1);
			f_out << "(abs(";
			for(unsigned int i=0;i<2;i++) {
				advance(line, i);
				if(line->third_rule) {
					switch(line->direction) {
						case YMIN: f_out << "(" << -(line->position+offset_y) << " + 2*high_res/3)"; break;
						case YMAX: f_out << "(" << -(line->position+offset_y) << " - 2*high_res/3)"; break;
						}
				} else {
					f_out << "(" << -(line->position+offset_y) << ")";
					}
				if(i==0) {
					f_out << " - ";
					}
				}
			f_out << ") / high_res))), ... % " << line->label << " : " << line->type << "\n";
			}
		}
	f_out << "\t];\n"
	         "endif % cli.highresmesh\n"
	         "\n";

	f_out << "% Standard metal resolution mesh for orthogonal shapes\n"
	         "% First column : outer line, Second column : inner line (thirds rule)\n"
	         "% Last symbol : edge direction (from inner side to outer side)\n"
	         "if cli.metalresmesh\n"
	         "mesh.x = [mesh.x, ...\n";
	for(auto line=begin(mesh.x);line<end(mesh.x);++line) {
		if(line->high_res && next(line)!=end(mesh.x) && next(line)->high_res && line->label==next(line)->label) {
			advance(line, 1); // Skip the pair
		} else if(line->type=="Pac") {
			f_out << "\t(" << line->position+offset_x << "), ... % " << line->label << " : " << line->type << "\n";
			}
		}
	f_out << "\t];\n"
	         "mesh.y = [mesh.y, ...\n";
	for(auto line=begin(mesh.y);line<end(mesh.y);++line) {
		if(line->high_res && next(line)!=end(mesh.y) && next(line)->high_res && line->label==next(line)->label) {
			advance(line, 1); // Skip the pair
		} else if(line->type=="Pac") {
			f_out << "\t(" << -(line->position+offset_y) << ") ... % " << line->label << " : " << line->type << "\n";
			}
		}
	f_out << "\t];\n"
	         "if cli.thirdsrule\n"
	         "mesh.x = [mesh.x, ...\n";
	for(auto line=begin(mesh.x);line<end(mesh.x);++line) {
		if(line->high_res && next(line)!=end(mesh.x) && next(line)->high_res && line->label==next(line)->label) {
			advance(line, 1); // Skip the pair
		} else if(line->type!="Pac") {
			if(line->third_rule) {
				switch(line->direction) {
					case XMIN: f_out << "\t(" << line->position+offset_x << " - 2*metal_res/3), (" << line->position+offset_x << " + metal_res/3), ... % " << line->label << " : " << line->type << " : <\n"; break;
					case XMAX: f_out << "\t(" << line->position+offset_x << " + 2*metal_res/3), (" << line->position+offset_x << " - metal_res/3), ... % " << line->label << " : " << line->type << " : >\n"; break;
					}
			} else {
				f_out << "\t(" << line->position+offset_x << "), ... % " << line->label << " : " << line->type << "\n";
				}
			}
		}
	f_out << "\t];\n"
	         "mesh.y = [mesh.y, ...\n";
	for(auto line=begin(mesh.y);line<end(mesh.y);++line) {
		if(line->high_res && next(line)!=end(mesh.y) && next(line)->high_res && line->label==next(line)->label) {
			advance(line, 1); // Skip the pair
		} else if(line->type!="Pac") {
			if(line->third_rule) {
				switch(line->direction) {
					case YMIN: f_out << "\t(" << -(line->position+offset_y) << " + 2*metal_res/3), (" << -(line->position+offset_y) << " - metal_res/3), ... % " << line->label << " : " << line->type << " : ^\n"; break;
					case YMAX: f_out << "\t(" << -(line->position+offset_y) << " - 2*metal_res/3), (" << -(line->position+offset_y) << " + metal_res/3), ... % " << line->label << " : " << line->type << " : v\n"; break;
					}
			} else {
				f_out << "\t(" << -(line->position+offset_y) << ") ... % " << line->label << " : " << line->type << "\n";
				}
			}
		}
	f_out << "\t];\n"
	         "else % cli.thirdsrule\n"
	         "mesh.x = [mesh.x, " << block.metal_boundary[XMIN]+offset_x << ", " << block.metal_boundary[XMAX]+offset_x << "];\n"
	         "mesh.y = [mesh.y, " << -(block.metal_boundary[YMIN]+offset_y) << ", " << -(block.metal_boundary[YMAX]+offset_y) << "];\n"
	         "endif % cli.thirdsrule\n"
	         "mesh.z = [mesh.z, ...\n";
	for(shared_ptr<Element> it : block.elements) {
		if(it->getType()=="SUBST") {
			f_out << "\t(-" << it->getLabel() << ".substrate.h/3), ...\n"
			         "\t(-2*" << it->getLabel() << ".substrate.h/3), ...\n";
			}
		}
	f_out << "\t];\n"
	         "if cli.conductingsheet\n"
	         "mesh.z = [mesh.z, ...\n";
	for(shared_ptr<Element> it : block.elements) {
		if(it->getType()=="SUBST") {
			f_out << "\t(0), ...\n"
			         "\t(-" << it->getLabel() << ".substrate.h), ...\n";
			}
		}
	f_out << "\t];\n"
	         "else % cli.conductingsheet\n"
	         "mesh.z = [mesh.z, ...\n";
	for(shared_ptr<Element> it : block.elements) {
		if(it->getType()=="SUBST") {
			f_out << "\t(" << it->getLabel() << ".metal.t/2), ...\n"
			         "\t(-" << it->getLabel() << ".substrate.h - " << it->getLabel() << ".metal.t/2), ...\n";
			}
		}
	f_out << "\t];\n"
	         "endif % cli.conductingsheet\n";

	f_out << "if cli.smoothmesh\n"
	         "mesh = SmoothMesh(mesh, metal_res);\n"
	         "endif % cli.smoothmesh\n"
	         "endif % cli.metalresmesh\n"
	         "endif % cli.mesh\n"
	         "endif % cli.preprocess\n"
	         "\n"
	         "% Boundary box\n"
	         "if cli.mesh\n"
	         "mesh.x = [mesh.x, " << block.margin_boundary[XMIN]+offset_x << " - lambda * " << data.oems_boundary_factor << "/4, " << block.margin_boundary[XMAX]+offset_x << " + lambda * " << data.oems_boundary_factor << "/4];\n"
	         "mesh.y = [mesh.y, " << -(block.margin_boundary[YMIN]+offset_y) << " + lambda * " << data.oems_boundary_factor << "/4, " << -(block.margin_boundary[YMAX]+offset_y) << " - lambda * " << data.oems_boundary_factor << "/4];\n"
	         "mesh.z = [mesh.z, " << extrem_pos_zmin << " - lambda * " << data.oems_boundary_factor << "/4, " << extrem_pos_zmax << " + lambda * " << data.oems_boundary_factor << "/4];\n"
	         "if cli.smoothmesh\n"
	         "mesh = SmoothMesh(mesh, substrate_res);\n"
	         "endif % cli.smoothmesh\n"
	         "endif % cli.mesh\n"
	         "\n"
	         "if cli.preprocess\n"
	         "CSX = DefineRectGrid(CSX, unit, mesh);\n"
	         "endif % cli.preprocess\n"
	         "\n";

	f_out << "%%%% PORTS\n";
	for(pair<unsigned int, shared_ptr<Element>> it : ports) {
		f_out << "% " << it.second->getLabel() << " : " << it.second->getType() << "\n" <<
		         it.second->getLabel() << ".center = [" << it.second->getX()+offset_x << ", " << -(it.second->getY()+offset_y) << ", " << it.second->getSubst() << ".metal.t];\n" <<
		         it.second->getLabel() << ".Z = (" << it.second->getZ() << ");\n" <<
		         it.second->getLabel() << ".P = (" << it.second->getDbm() << ");\n" <<
		         it.second->getLabel() << ".F = (" << it.second->getF() << ");\n" <<
		         "if cli.conductingsheet\n"
		         "[CSX port{" << it.second->getN() << "}] = AddLumpedPort(CSX, 5, " << it.second->getN() << ", " << it.second->getLabel() << ".Z, ...\n"
		         "\t[" << it.second->getP(0, X, R, ABS)+offset_x << ", " << -(it.second->getP(0, Y, R, ABS)+offset_y) << ", (-" << it.second->getSubst() << ".substrate.h)" << "], ...\n"
		         "\t[" << it.second->getP(2, X, R, ABS)+offset_x << ", " << -(it.second->getP(2, Y, R, ABS)+offset_y) << ", (0)" << "], ...\n"
		         "\t[0 0 1], find(cli.active_ports == " << it.first << "));\n"
		         "else % cli.conductingsheet\n"
		         "[CSX port{" << it.second->getN() << "}] = AddLumpedPort(CSX, 5, " << it.second->getN() << ", " << it.second->getLabel() << ".Z, ...\n"
		         "\t[" << it.second->getP(0, X, R, ABS)+offset_x << ", " << -(it.second->getP(0, Y, R, ABS)+offset_y) << ", (-" << it.second->getSubst() << ".substrate.h - " << it.second->getSubst() << ".metal.t)" << "], ...\n"
		         "\t[" << it.second->getP(2, X, R, ABS)+offset_x << ", " << -(it.second->getP(2, Y, R, ABS)+offset_y) << ", (" << it.second->getSubst() << ".metal.t)" << "], ...\n"
		         "\t[0 0 1], find(cli.active_ports == " << it.first << "));\n"
		         "endif % cli.conductingsheet\n"
		         "\n";
		}

	f_out << "%%%% SIMULATION\n"
	         "if cli.preprocess\n"
	         "FDTD = InitFDTD('NrTS', time_res, 'EndCriteria', end_criteria);\n"
	         "FDTD = SetGaussExcite(FDTD, f0, fc);\n"
	         "if cli.mur\n"
	         "\tBC = {'MUR', 'MUR', 'MUR', 'MUR', 'MUR', 'MUR'};\n"
	         "else\n"
	         "\tBC = {'PML_8', 'PML_8', 'PML_8', 'PML_8', 'PML_8', 'PML_8'};\n"
	         "endif\n"
	         "FDTD = SetBoundaryCond(FDTD, BC);\n"
	         "endif % cli.preprocess\n"
	         "\n";

	f_out << "%%%% NF2FF\n"
	         "if cli.nf2ff\n"
	         "if cli.mesh\n"
	         "if cli.smoothmesh\n"
	         "% Be careful that NF2FF box boundaries are not in PML\n"
	         "[CSX nf2ff] = CreateNF2FFBox(CSX, 'nf2ff', ...\n"
	         "\t[mesh.x(10), mesh.y(10), mesh.z(10)], ...\n"
	         "\t[mesh.x(end-9), mesh.y(end-9), mesh.z(end-9)]);\n"
	         "endif % cli.smoothmesh\n"
	         "endif % cli.mesh\n"
	         "endif % cli.nf2ff\n"
	         "\n";

	f_out << "%%%% DUMPS\n"
	         "if cli.preprocess\n";
	for(shared_ptr<Element> it : block.elements) {
		if(it->getType()=="SUBST") {
			f_out << "% " << it->getLabel() << " ET\n"
			         "if cli.dump_et\n"
			         "CSX = AddDump(CSX, '" << it->getLabel() << ".Et', 'DumpType', 0);\n"
			         "CSX = AddBox(CSX, '" << it->getLabel() << ".Et', 0, " << it->getLabel() << ".dump.start, " << it->getLabel() << ".dump.stop);\n"
			         "endif % cli.dump_et\n"
			         "% " << it->getLabel() << " HT\n"
			         "if cli.dump_ht\n"
			         "CSX = AddDump(CSX, '" << it->getLabel() << ".Ht', 'DumpType', 1);\n"
			         "CSX = AddBox(CSX, '" << it->getLabel() << ".Ht', 0, " << it->getLabel() << ".dump.start, " << it->getLabel() << ".dump.stop);\n"
			         "endif % cli.dump_ht\n"
			         "% " << it->getLabel() << " CURRENT\n"
			         "if cli.dump_jt\n"
			         "CSX = AddDump(CSX, '" << it->getLabel() << ".Jt', 'DumpType', 2, 'DumpMode', 0);\n"
			         "CSX = AddBox(CSX, '" << it->getLabel() << ".Jt', 0, " << it->getLabel() << ".dump.start, " << it->getLabel() << ".dump.stop);\n"
			         "endif % cli.dump_jt\n"
			         "% " << it->getLabel() << " CURRENT DENSITY\n"
			         "if cli.dump_cdt\n"
			         "CSX = AddDump(CSX, '" << it->getLabel() << ".Cdt', 'DumpType', 3);\n"
			         "CSX = AddBox(CSX, '" << it->getLabel() << ".Cdt', 0, " << it->getLabel() << ".dump.start, " << it->getLabel() << ".dump.stop);\n"
			         "endif % cli.dump_cdt\n"
			         "\n";
			}
		}

	f_out << "%%%% RUN OPENEMS\n"
	         "WriteOpenEMS([cli.path_simulation '/' csx_file], FDTD, CSX);\n"
	         "t_preprocess_stop = clock();\n"
	         "endif % cli.preprocess\n"
	         "if cli.gui\n"
	         "CSXGeomPlot([cli.path_simulation '/' csx_file]);\n"
	         "endif % cli.gui\n"
	         "if cli.process\n"
	         "t_process_start = clock();\n"
	         "RunOpenEMS(cli.path_simulation, csx_file);\n"
	         "t_process_stop = clock();\n"
	         "endif % cli.process\n"
	         "\n";

	f_out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% POSTPROCESSING\n"
	         "\n";

	f_out << "if cli.postprocess\n"
	         "% NF2FF center should be placed at the center of the radiating element.\n" <<
	         (data.oems_nf2ff_center!=""
	         ? "%nf2ff.center = [(max(mesh.x)-min(mesh.x))/2, (max(mesh.y)-min(mesh.y))/2, 0];\n"
	           "nf2ff.center = " + data.oems_nf2ff_center + ".center;\n"
	         : "nf2ff.center = [(max(mesh.x)-min(mesh.x))/2, (max(mesh.y)-min(mesh.y))/2, 0];\n"
			 ) <<
	         "\n"
	         "t_postprocess_start = clock();\n"
	         "oemsgen_postProcess('" << name << "', cli.path_simulation, cli.path_result, port, cli.ports_index, cli.active_ports, fstart, fstop, points, ...\n"
	         "\t'legend_out', cli.legend_out, ...\n"
	         "\t'nf2ff', cli.nf2ff, ...\n"
	         "\t'nf2ff_data', nf2ff, ...\n"
	         "\t'nf2ff_mode', cli.nf2ff_mode, ...\n"
	         "\t'nf2ff_3d', cli.nf2ff_3d, ...\n"
	         "\t'nf2ff_3d_phistep', cli.nf2ff_phistep, ...\n"
	         "\t'nf2ff_3d_thetastep', cli.nf2ff_thetastep, ...\n"
	         "\t'nf2ff_3d_frames', cli.nf2ff_frames, ...\n"
	         "\t'nf2ff_3d_delay', cli.nf2ff_delay, ...\n"
	         "\t'nf2ff_3d_dump', cli.dump_ff3d, ...\n"
	         "\t'nf2ff_3d_dump_unit', unit, ...\n"
	         "\t'f_select', cli.f, ...\n"
	         "\t'f_min', cli.f_min, ...\n"
	         "\t'f_max', cli.f_max, ...\n"
	         "\t'f_equal', cli.f_equal_s, cli.f_equal_v);\n"
	         "t_postprocess_stop = clock();\n"
	         "endif % cli.postprocess\n"
	         "\n";

	f_out << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% SYSTEM\n"
	         "\n";

	f_out << "%%%% TIMES\n"
	         "disp(\"\\nDurations :\");\n"
	         "d_total = 0;\n"
	         "if cli.preprocess\n"
	         "\td_preprocess = etime(t_preprocess_stop, t_preprocess_start);\n"
	         "\th_preprocess = fix(d_preprocess / 3600);\n"
	         "\tm_preprocess = fix((d_preprocess - h_preprocess*3600) / 60);\n"
	         "\ts_preprocess = round(d_preprocess - h_preprocess*3600 - m_preprocess*60);\n"
	         "\tdisp(['Preprocessing : ', ...\n"
	         "\t\tnum2str(h_preprocess), 'h ', ...\n"
	         "\t\tnum2str(m_preprocess), 'm ', ...\n"
	         "\t\tnum2str(s_preprocess), 's']);\n"
	         "\td_total = d_total + d_preprocess;\n"
	         "endif\n"
	         "if cli.process\n"
	         "\td_process = etime(t_process_stop, t_process_start);\n"
	         "\th_process = fix(d_process / 3600);\n"
	         "\tm_process = fix((d_process - h_process*3600) / 60);\n"
	         "\ts_process = round(d_process - h_process*3600 - m_process*60);\n"
	         "\tdisp(['Processing : ', ...\n"
	         "\t\tnum2str(h_process), 'h ', ...\n"
	         "\t\tnum2str(m_process), 'm ', ...\n"
	         "\t\tnum2str(s_process), 's']);\n"
	         "\td_total = d_total + d_process;\n"
	         "endif\n"
	         "if cli.postprocess\n"
	         "\td_postprocess = etime(t_postprocess_stop, t_postprocess_start);\n"
	         "\th_postprocess = fix(d_postprocess / 3600);\n"
	         "\tm_postprocess = fix((d_postprocess - h_postprocess*3600) / 60);\n"
	         "\ts_postprocess = round(d_postprocess - h_postprocess*3600 - m_postprocess*60);\n"
	         "\tdisp(['Postprocessing : ', ...\n"
	         "\t\tnum2str(h_postprocess), 'h ', ...\n"
	         "\t\tnum2str(m_postprocess), 'm ', ...\n"
	         "\t\tnum2str(s_postprocess), 's']);\n"
	         "\td_total = d_total + d_postprocess;\n"
	         "endif\n"
	         "h_total = fix(d_total / 3600);\n"
	         "m_total = fix((d_total - h_total*3600) / 60);\n"
	         "s_total = round(d_total - h_total*3600 - m_total*60);\n"
	         "disp(['Total : ', ...\n"
	         "\tnum2str(h_total), 'h ', ...\n"
	         "\tnum2str(m_total), 'm ', ...\n"
	         "\tnum2str(s_total), 's']);\n"
	         "\n";

	f_out << "if cli.postprocess\n"
	         "if cli.batch\n"
	         "disp(\"\\nTerminated, press any key to exit.\");\n"
	         "pause();\n"
	         "endif % cli.batch\n"
	         "endif % cli.postprocess\n"
	         "return;\n";
	}
