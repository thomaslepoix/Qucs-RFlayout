///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#include <iostream>

#include "data.hpp"
using namespace std;

//******************************************************************************
Block::Block() :
	metal_boundary({ 0.0, 0.0, 0.0, 0.0 }),
	margin_boundary({ 0.0, 0.0, 0.0, 0.0 }),
	margin(0.0)
	{}

//******************************************************************************
void Block::calcul_boundaries() {
	// Reset metal_boundary to a random existant point
	for(shared_ptr<Element> it : elements) {
		if(it->getNpoint()
		&& it->getType()!="SUBST") {
			metal_boundary[XMIN]=it->getP(1, X, R, ABS, false);
			metal_boundary[XMAX]=it->getP(1, X, R, ABS, false);
			metal_boundary[YMIN]=it->getP(1, Y, R, ABS, false);
			metal_boundary[YMAX]=it->getP(1, Y, R, ABS, false);
			break;
			}
		}
	// Set metal_boundary
	for(shared_ptr<Element> it : elements) {
		it->setP();
		if(it->getType()=="SUBST") continue;
		for(int i=0;i<it->getNpoint();i++) {
			if(it->getP(i, X, R, ABS, false)<metal_boundary[XMIN]) metal_boundary[XMIN]=it->getP(i, X, R, ABS, false);
			if(it->getP(i, X, R, ABS, false)>metal_boundary[XMAX]) metal_boundary[XMAX]=it->getP(i, X, R, ABS, false);
			if(it->getP(i, Y, R, ABS, false)<metal_boundary[YMIN]) metal_boundary[YMIN]=it->getP(i, Y, R, ABS, false);
			if(it->getP(i, Y, R, ABS, false)>metal_boundary[YMAX]) metal_boundary[YMAX]=it->getP(i, Y, R, ABS, false);
			}
		}
	// Set margin_boundary
	margin_boundary[XMIN]=metal_boundary[XMIN]-margin;
	margin_boundary[XMAX]=metal_boundary[XMAX]+margin;
	margin_boundary[YMIN]=metal_boundary[YMIN]-margin;
	margin_boundary[YMAX]=metal_boundary[YMAX]+margin;
	}

//******************************************************************************
void Block::shift(long double const x, long double const y) {
	for(shared_ptr<Element> it : elements) {
		it->setX(it->getX(false)+x);
		it->setY(it->getY(false)+y);
		}
	calcul_boundaries();
	}

//******************************************************************************
void Block::print_extrem_pos() const {
	cout << "\tXmin : " << metal_boundary[XMIN] << "\n"
	        "\tXmax : " << metal_boundary[XMAX] << "\n"
	        "\tYmin : " << metal_boundary[YMIN] << "\n"
	        "\tYmax : " << metal_boundary[YMAX] << "\n";
	}

//******************************************************************************
void Block::print() const {
	cout << "Elements :" << endl;
	for(shared_ptr<Element> it : elements) {
		cout << "\t" << it->getLabel() << "\t" << it->getType() << endl;
		}

	cout << "Substrate :" << endl;
	if(subst)
		cout << "\t" << subst->getLabel() << endl;

	cout << "Extrem positions :\n";
	print_extrem_pos();
	cout << endl;
	}

//******************************************************************************
Data::Data() :
	metal_boundary({ 0.0, 0.0, 0.0, 0.0 }),
	margin_boundary({ 0.0, 0.0, 0.0, 0.0 }),
	is_volume_error(false),
	out_format(".kicad_pcb"),
	export_each_block(false),
	export_each_subst(false),
	keep_tmp_files(false),
	subst_margin_factor(10),
	port_default_l(0.2),
	oems_boundary_factor(3),
	oems_highres_div(200),
	oems_metalres_div(60),
	oems_substres_div(30),
	oems_timeres(300000),
	oems_end_criteria("1e-4"),
	oems_sort_metalresmesh(false),
	oems_pkg(false)
	{}

// Reset elements but not parameters
//******************************************************************************
void Data::reset() {
	all_elements.clear();
	all_blocks.clear();
	volume_error.clear();
	margin_boundary={};
	metal_boundary={};
	is_volume_error=false;
	}
