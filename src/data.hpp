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

class Data {
public:
	std::vector<std::shared_ptr<Element>> tab_all;
//	std::vector<std::shared_ptr<Element>> all_elem;
//	std::vector<std::vector<std::shared_ptr<Element>>> all_elem_block;
//	std::vector<std::vector<std::shared_ptr<Element>>> all_elem_subst;

	std::array<long double, 4> extrem_pos;
	std::string n_sch;
	std::string out_dir;
	std::string out_format;

	bool is_volume_error=false;
//	std::string volume_warning;
	std::string volume_error;

	Data(void);
	void clear(void);
};

#endif // DATA_HPP
