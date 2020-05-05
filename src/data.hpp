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
#include <vector>

#include "microstrip/element.hpp"

class Block {
public:
	std::vector<std::shared_ptr<Element>> elements;
	std::shared_ptr<Element> subst;
	std::shared_ptr<Element> subst_local;
	std::array<long double, 4> extrem_pos; // extrem coords of elements
	std::array<long double, 4> boundary;   // extrem_pos with margin
	long double margin;

	Block(void);
	void shift(long double const x, long double const y);
	void set_extrem_pos(void);
	void print_extrem_pos(void);
	void print(void);
};

class Data {
public:
	std::vector<std::shared_ptr<Element>> tab_all;
	std::vector<std::shared_ptr<Block>> all_blocks;
//	std::vector<std::shared_ptr<Substrate>> all_substrates;

//	std::vector<std::shared_ptr<Element>> all_elem;
//	std::vector<std::vector<std::shared_ptr<Element>>> all_elem_block;
//	std::vector<std::vector<std::shared_ptr<Element>>> all_elem_subst;

	std::array<long double, 4> extrem_pos; // extrem coords of elements (subst included) + margins
	std::string n_sch;
	std::string out_dir;
	std::string out_format;
	bool export_each_block;
	bool export_each_subst;

	bool is_volume_error=false; // is 3D representation possible?
	std::string volume_error; // 3D error messages buffer

	Data(void);
	~Data(void);
	void clear(void);
};

#endif // DATA_HPP
