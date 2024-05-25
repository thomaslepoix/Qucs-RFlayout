/***************************************************************************
                               layoutwriter.hpp
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

#ifndef LAYOUTWRITER_HPP
#define LAYOUTWRITER_HPP

#define _USE_MATH_DEFINES

#include <fstream>
#include <memory>

#include "data.hpp"

//******************************************************************************
class LayoutWriter {
private:
	Data const& data;

	int check_m() const;
	int write(Block& block, long double const offset_x, long double const offset_y, std::string const& n_out, std::string const& name, std::vector<std::string>* out_names) const;
	//TODO array<long double, 2> offset ?
	void write_kicad_pcb(Block& block, std::ofstream& f_out, long double const offset_x, long double const offset_y, std::string const& name) const;
	void write_kicad_mod(Block& block, std::ofstream& f_out, long double const offset_x, long double const offset_y, std::string const& name) const;
	void write_svg(Block& block, std::ofstream& f_out, long double const offset_x, long double const offset_y, std::string const& name) const;
	void write_lht(Block& block, std::ofstream& f_out, long double const offset_x, long double const offset_y, std::string const& name) const;
	void write_m(Block& block, std::ofstream& f_out, long double const offset_x, long double const offset_y, std::string const& name) const;

public:
	LayoutWriter(Data const& _data);
	~LayoutWriter()=default;
	int run(std::vector<std::string>* out_names=nullptr) const;
};

#endif // LAYOUTWRITER_HPP
