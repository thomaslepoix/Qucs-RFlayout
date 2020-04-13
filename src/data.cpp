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
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "data.hpp"
using namespace std;

Data::Data(void) :
	extrem_pos({0.0, 0.0, 0.0, 0.0}),
	is_volume_error(false)
	{}

void Data::clear(void) {
	tab_all.clear();
	tab_all.shrink_to_fit();
	is_volume_error=false;
	volume_error.clear();
	}
