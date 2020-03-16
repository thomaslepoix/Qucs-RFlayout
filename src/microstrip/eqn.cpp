/***************************************************************************
                               eqn.cpp
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

#include "eqn.hpp"
using namespace std;

Eqn::Eqn(string _label,
			string _type,
			bool _mirrorx,
			short _r) :
	Element(_label, _type, _mirrorx, _r, 0, "")
	{}

Eqn::~Eqn() {
	}

string Eqn::getDescriptor(void) {
	return(m_descriptor);
	}
