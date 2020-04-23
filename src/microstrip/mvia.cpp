/***************************************************************************
                               mvia.cpp
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

#include "mvia.hpp"
using namespace std;

Mvia::Mvia(string _label,
			string _type,
			bool _active,
			bool _mirrorx,
			short _r,
			string _subst,
			long double _d) :
	Element(_label, _type, _active, _mirrorx, _r, 1, _subst),
	m_d(_d)
	{}

Mvia::~Mvia() {
	}

string Mvia::getDescriptor(void) {
	return(m_descriptor);
	}

long double Mvia::getD(void) {
	return(m_d);
	}

string Mvia::getNet1(void) {
	return(m_net1);
	}

int Mvia::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

void Mvia::getEdge(int const /*_net*/, long double& edge, short& dir) {
	edge=m_d;
	switch(m_r) {
		case 0: dir=XMIN; break;
		case 90: dir=YMAX; break;
		case 180: dir=XMAX; break;
		case 270: dir=YMIN; break;
		}
	}
