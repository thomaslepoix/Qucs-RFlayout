/***************************************************************************
                               mstep.cpp
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

#include "mstep.hpp"
using namespace std;

Mstep::Mstep(string _label,
			string _type,
			bool _mirrorx,
			short _r,
			string _subst,
			long double _w1,
			long double _w2) :
	Element(_label, _type, _mirrorx, _r, 2, _subst),
	m_w1(_w1),
	m_w2(_w2)
	{}

Mstep::~Mstep() {
	}

string Mstep::getDescriptor(void) {
	return(m_descriptor);
	}

long double Mstep::getW1(void) {
	return(m_w1);
	}

long double Mstep::getW2(void) {
	return(m_w2);
	}

string Mstep::getNet1(void) {
	return(m_net1);
	}

string Mstep::getNet2(void) {
	return(m_net2);
	}

int Mstep::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

int Mstep::setNet2(string _net2) {
	m_net2=_net2;
	return(0);
	}
