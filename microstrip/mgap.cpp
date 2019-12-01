/***************************************************************************
                               mgap.cpp
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

#include "mgap.h"
using namespace std;

Mgap::Mgap(string _label,
			string _type,
			bool _mirrorx,
			short _r,
			short _nport,
			long double _w1,
			long double _w2,
			long double _s) :
	Element(_label, _type, _mirrorx, _r, _nport),
	m_w1(_w1),
	m_w2(_w2),
	m_s(_s)
	{}

Mgap::~Mgap() {
	}

string Mgap::getDescriptor(void) {
	return(m_descriptor);
	}

long double Mgap::getW1(void) {
	return(m_w1);
	}

long double Mgap::getW2(void) {
	return(m_w2);
	}

long double Mgap::getS(void) {
	return(m_s);
	}

string Mgap::getNet1(void) {
	return(m_net1);
	}

string Mgap::getNet2(void) {
	return(m_net2);
	}

int Mgap::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

int Mgap::setNet2(string _net2) {
	m_net2=_net2;
	return(0);
	}
