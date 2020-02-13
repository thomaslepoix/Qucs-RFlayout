/***************************************************************************
                               mopen.cpp
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

#include "mopen.hpp"
using namespace std;

Mopen::Mopen(string _label,
			string _type,
			bool _mirrorx,
			short _r,
			short _nport,
			long double _w) :
	Element(_label, _type, _mirrorx, _r, _nport),
	m_w(_w)
	{}

Mopen::~Mopen() {
	}

string Mopen::getDescriptor(void) {
	return(m_descriptor);
	}

long double Mopen::getW(void) {
	return(m_w);
	}

string Mopen::getNet1(void) {
	return(m_net1);
	}

int Mopen::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}
