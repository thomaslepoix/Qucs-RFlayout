/***************************************************************************
                               data.cpp
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

#include <iostream>

#include "data.hpp"
using namespace std;

//******************************************************************************
Block::Block() :
	elements(vector<shared_ptr<Element>>()),
	subst(shared_ptr<Element>()),
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

// Copy an object to a new object with all parameters set but no elements.
//******************************************************************************
Data::Data(Data const& data) :
	metal_boundary({ 0.0, 0.0, 0.0, 0.0 }),
	margin_boundary({ 0.0, 0.0, 0.0, 0.0 }),
	is_volume_error(false),
	n_sch(data.n_sch),
	n_net(data.n_net),
	out_dir(data.out_dir),
	out_format(data.out_format),
	export_each_block(data.export_each_block),
	export_each_subst(data.export_each_subst),
	keep_tmp_files(data.keep_tmp_files),
	subst_margin_factor(data.subst_margin_factor),
	port_default_l(data.port_default_l),
	oems_boundary_factor(data.oems_boundary_factor),
	oems_highres_div(data.oems_highres_div),
	oems_metalres_div(data.oems_metalres_div),
	oems_substres_div(data.oems_substres_div),
	oems_timeres(data.oems_timeres),
	oems_end_criteria(data.oems_end_criteria),
	oems_sort_metalresmesh(data.oems_sort_metalresmesh),
	oems_pkg(data.oems_pkg)
	{}

//******************************************************************************
Data::~Data() {
	for(shared_ptr<Element> it : tab_all) {
		it->prev=nullptr;
		it->setAdjacent(1, nullptr, 0);
		it->setAdjacent(2, nullptr, 0);
		it->setAdjacent(3, nullptr, 0);
		it->setAdjacent(4, nullptr, 0);
		}
	}
