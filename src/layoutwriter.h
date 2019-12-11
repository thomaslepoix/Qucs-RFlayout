/***************************************************************************
                               layoutwriter.h
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

#ifndef LAYOUTWRITER_H
#define LAYOUTWRITER_H

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <regex>
#include <cmath>
#include <array>

#include "microstrip/microstrip.h"

class LayoutWriter {
private:
	std::vector<std::shared_ptr<Element>> const& tab_all;
	std::array<long double, 4> const& extrem_pos;
	std::string const& n_sch;
	std::string const& out_dir;
	std::string const& out_format;

	int write_kicad_pcb(std::ofstream& f_out);
	int write_kicad_mod(std::string const& name, std::ofstream& f_out);
	int write_lht(std::ofstream& f_out);

public:
	LayoutWriter(std::vector<std::shared_ptr<Element>> const& _tab_all, std::array<long double, 4> const& _extrem_pos, std::string const& _n_sch, std::string const& _out_dir, std::string const& _out_format);
	int run(void);
};

#endif // LAYOUTWRITER_H
