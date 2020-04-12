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
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef LAYOUTWRITER_HPP
#define LAYOUTWRITER_HPP

#define _USE_MATH_DEFINES

#include <fstream>

#include "data.hpp"

class LayoutWriter {
private:
	Data& data;

	int write_kicad_pcb(std::ofstream& f_out);
	int write_kicad_mod(std::string const& name, std::ofstream& f_out);
	int write_lht(std::ofstream& f_out);

public:
	LayoutWriter(Data& _data);
	int run(std::string* out_name=nullptr);
};

#endif // LAYOUTWRITER_HPP
