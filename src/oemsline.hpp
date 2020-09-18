/***************************************************************************
                               oemsline.hpp
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

#ifndef OEMSLINE_HPP
#define OEMSLINE_HPP

#include <memory>
#include <string>

// High resolution meshlines work by pair. To be printed as hres lines, it is
// required that both lines of a pair are contiguous in a OemsMesh.dir vector
// Otherwise both will be printed as regular metal resolution lines

//******************************************************************************
struct OemsLine {
	long double position;
	int direction;
	bool third_rule;
	bool high_res=false;
	std::string label;
	std::string type;
};

#endif // OEMSLINE_HPP
