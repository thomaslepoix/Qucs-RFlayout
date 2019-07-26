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

#include "mopen.h"
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

////////////////////////////////////////////////////////////////////////////////
long double Mopen::getW1(void) {
	return(0);
	}
long double Mopen::getW2(void) {
	return(0);
	}
long double Mopen::getW3(void) {
	return(0);
	}
long double Mopen::getW4(void) {
	return(0);
	}
long double Mopen::getL(void) {
	return(0);
	}
long double Mopen::getD(void) {
	return(0);
	}
long double Mopen::getS(void) {
	return(0);
	}
long double Mopen::getRi(void) {
	return(0);
	}
long double Mopen::getRo(void) {
	return(0);
	}
short Mopen::getAlpha(void) {
	return(0);
	}
string Mopen::getNet2(void) {
	return("");
	}
string Mopen::getNet3(void) {
	return("");
	}
string Mopen::getNet4(void) {
	return("");
	}
int Mopen::getNpoint(void) {
	return(0);
	}
long double Mopen::getP(int _n, bool _xy, bool _r, bool _abs) {
	(void) _n;
	(void) _xy;
	(void) _r;
	(void) _abs;
	return(1);
	}
int Mopen::setNet2(string _net2) {
	(void) _net2;
	return(1);
	}
int Mopen::setNet3(string _net3) {
	(void) _net3;
	return(1);
	}
int Mopen::setNet4(string _net4) {
	(void) _net4;
	return(1);
	}
int Mopen::setP(void) {
	return(1);
	}
