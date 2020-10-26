/***************************************************************************
                               data.hpp
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

#ifndef DATA_HPP
#define DATA_HPP

#include <array>
#include <memory>
#include <sstream>
#include <tuple>
#include <vector>

#include "microstrip/element.hpp"

//******************************************************************************
class Block {
public:
	std::vector<std::shared_ptr<Element>> elements;
	std::shared_ptr<Element> subst;
	std::shared_ptr<Element> subst_local; // Substrate adjusted to each block
	std::array<long double, 4> metal_boundary;
	std::array<long double, 4> margin_boundary;
	long double margin;

	Block();
	~Block()=default;
	void shift(long double const x, long double const y);
//	void shift(long double const x, long double const y, bool const apply_shift); //TODO apply_shift : adapt subst size to shifted ports
	void calcul_boundaries();
//	void calcul_boundaries(bool const apply_shift=false); //TODO apply_shift : adapt subst size to shifted ports
	void print_extrem_pos() const;
	void print() const;
};

//******************************************************************************
class Data {
public:

	// Discarded on reset
	std::vector<std::shared_ptr<Element>> tab_all;
	std::vector<std::shared_ptr<Block>> all_blocks;
//	std::vector<std::shared_ptr<Substrate>> all_substrates;

//	std::vector<std::shared_ptr<Element>> all_elem;
//	std::vector<std::vector<std::shared_ptr<Element>>> all_elem_block;
//	std::vector<std::vector<std::shared_ptr<Element>>> all_elem_subst;

	std::array<long double, 4> metal_boundary;
	std::array<long double, 4> margin_boundary; // extrem coords of elements (subst included) + margins

	bool is_volume_error; // is 3D representation possible?
	std::string volume_error; // 3D error messages buffer

	std::vector<std::string> excluded_elements;
	std::vector<std::string> used_elements;

	// Handles '--port-shift N X Y' arg.
	std::vector<std::tuple<unsigned long, std::string, std::string>> port_shift_args;
	// Handles '--port-size N L W' arg.
	std::vector<std::tuple<unsigned long, std::string, std::string>> port_size_args;

	// Saved on reset
	std::string n_sch;
	std::string n_net;
	std::string out_dir;
	std::string out_format;
	bool export_each_block;
	bool export_each_subst;
	bool keep_tmp_files;

	unsigned int subst_margin_factor;
	long double port_default_l;

	unsigned int oems_boundary_factor;
	unsigned int oems_highres_div;
	unsigned int oems_metalres_div;
	unsigned int oems_substres_div;
	unsigned int oems_timeres;
	std::string oems_end_criteria;
	std::string oems_nf2ff_center;
	bool oems_sort_metalresmesh;

	Data();
	Data(Data const& data);
	Data& operator=(Data const&)=default;
	~Data();
};

#endif // DATA_HPP
