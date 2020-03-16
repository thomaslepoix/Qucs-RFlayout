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

#include "pac.hpp"
using namespace std;

Pac::Pac(string _label,
			string _type,
			bool _mirrorx,
			short _r,
			short _n,
			long double _z,
			long double _p,
			long double _f) :
	Element(_label, _type, _mirrorx, _r, 2, ""),
	m_n(_n),
	m_z(_z),
	m_p(_p),
	m_f(_f)
	{}

Pac::~Pac() {
	}

string Pac::getDescriptor(void) {
	return(m_descriptor);
	}

long double Pac::getZ(void) {
	return(m_z);
	}

long double Pac::getDbm(void) {
	return(m_p);
	}

long double Pac::getF(void) {
	return(m_f);
	}

short Pac::getN(void) {
	return(m_n);
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
