/***************************************************************************
                               converter.hpp
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

#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <array>
#include <memory>
#include <vector>

#include "schparser.hpp"
#include "xycalculator.hpp"
#include "layoutwriter.hpp"

class Converter {
private:
	SchParser parser;
	XyCalculator xycalculator;
	LayoutWriter layoutwriter;

	std::vector<std::shared_ptr<Element>> tab_all;
	std::array<long double, 4> extrem_pos={0.0, 0.0, 0.0, 0.0};
	std::string n_sch;
	std::string out_dir;
	std::string out_format;

public:
	Converter(std::string _n_sch, std::string _out_dir, std::string _out_format);
	~Converter(void);

	void reset(std::string _n_sch, std::string _out_dir, std::string _out_format);
	void clear(void);
	int run(void);
	int read(void);
	int write(std::string& out_name);
	int size(void);

	std::vector<std::shared_ptr<Element>> const& get_tab_all(void);
	std::array<long double, 4> const& get_extrem_pos(void);
};

#endif // CONVERTER_HPP
