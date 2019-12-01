/***************************************************************************
                               pac.cpp
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

#include "pac.h"
using namespace std;

Pac::Pac(string _label,
			string _type,
			bool _mirrorx,
			short _r,
			short _nport) :
	Element(_label, _type, _mirrorx, _r, _nport)
	{}

Pac::~Pac() {
	}

string Pac::getDescriptor(void) {
	return(m_descriptor);
	}

string Pac::getNet1(void) {
	return(m_net1);
	}

string Pac::getNet2(void) {
	return(m_net2);
	}

int Pac::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

int Pac::setNet2(string _net2) {
	m_net2=_net2;
	return(0);
	}
