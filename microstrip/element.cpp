/***************************************************************************
                               element.cpp
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

#include "element.h"
using namespace std;

Element::Element(string _label,
			string _type,
			bool _mirrorx,
			short _r,
			short _nport) :
	m_label(_label),
	m_type(_type),
	m_mirrorx(_mirrorx),
	m_r(_r),
	m_nport(_nport)
	{}

Element::~Element() {
	}

string Element::getLabel(void) {
	return(m_label);
	}

string Element::getType(void) {
	return(m_type);
	}

bool Element::getMirrorx(void) {
	return(m_mirrorx);
	}

short Element::getR(void) {
	return(m_r);
	}

short Element::getNport(void) {
	return(m_nport);
	}

long double Element::getX(void) {
	return(m_x);
	}

long double Element::getY(void) {
	return(m_y);
	}

int Element::setX(long double _x) {
	m_x=_x;
	return(0);
	}

int Element::setY(long double _y) {
	m_y=_y;
	return(0);
	}

long double Element::rotateX(long double _x, long double _y) {
	return(_x*cos((M_PI/180)*m_r)+_y*sin((M_PI/180)*m_r));
	}

long double Element::rotateY(long double _x, long double _y) {
	return(-_x*sin((M_PI/180)*m_r)+_y*cos((M_PI/180)*m_r));
	}
