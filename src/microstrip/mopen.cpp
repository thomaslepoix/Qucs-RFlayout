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
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "mopen.hpp"
using namespace std;

//******************************************************************************
string const Mopen::m_descriptor("microstrip_open");

//******************************************************************************
Mopen::Mopen(string const _label,
			string const _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			string const _subst,
			long double const _w) :
	Element(_label, _type, _active, _mirrorx, _r, 1, _subst),
	m_w(_w)
	{}

//******************************************************************************
string Mopen::getDescriptor() const {
	return(m_descriptor);
	}

//******************************************************************************
long double Mopen::getW() const {
	return(m_w);
	}

//******************************************************************************
string Mopen::getNet1() const {
	return(m_net1);
	}

//******************************************************************************
int Mopen::setNet1(string const _net1) {
	m_net1=_net1;
	return(0);
	}

//******************************************************************************
void Mopen::getEdge(int const /*_net*/, long double& edge, short& dir) const {
	edge=m_w;
	switch(m_r) {
		case 0: dir=XMIN; break;
		case 90: dir=YMAX; break;
		case 180: dir=XMAX; break;
		case 270: dir=YMIN; break;
		}
	}

//******************************************************************************
bool Mopen::isOemsMeshInterface(int const _port, long double const /*_w*/) const {
	if(_port==1) {
		return(true);
	} else {
		return(false);
		}
	}

//******************************************************************************
int Mopen::setAdjacent(int const _port, shared_ptr<Element> const& adjacent, int const adjacent_port) {
	switch(_port) {
		case 1:
			adjacent1.first=adjacent;
			adjacent1.second=adjacent_port;
			break;
		default:
			return(1);
		}
	return(0);
	}