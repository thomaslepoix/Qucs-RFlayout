/***************************************************************************
                               mvia.cpp
                             ------------------
    begin                : Thu Oct 25 2018
    copyright            : (C) 2018 by Thomas Lepoix
    email                : thomas.lepoix@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "mvia.h"
using namespace std;

Mvia::Mvia(string _label,
			string _type,
			bool _mirrorx,
			short _r,
			string _subst,
			long double _d) :
	Element(_label, _type, _mirrorx, _r, 1, _subst),
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

////////////////////////////////////////////////////////////////////////////////

long double Mvia::getW(void) {
	return(0);
	}
long double Mvia::getW1(void) {
	return(0);
	}
long double Mvia::getW2(void) {
	return(0);
	}
long double Mvia::getW3(void) {
	return(0);
	}
long double Mvia::getW4(void) {
	return(0);
	}
long double Mvia::getL(void) {
	return(0);
	}
long double Mvia::getS(void) {
	return(0);
	}
long double Mvia::getRi(void) {
	return(0);
	}
long double Mvia::getRo(void) {
	return(0);
	}
long double Mvia::getZ(void) {
	return(0);
	}
long double Mvia::getDbm(void) {
	return(0);
	}
long double Mvia::getF(void) {
	return(0);
	}
long double Mvia::getEr(void) {
	return(0);
	}
long double Mvia::getH(void) {
	return(0);
	}
long double Mvia::getT(void) {
	return(0);
	}
long double Mvia::getTand(void) {
	return(0);
	}
long double Mvia::getRho(void) {
	return(0);
	}
short Mvia::getN(void) {
	return(0);
	}
short Mvia::getAlpha(void) {
	return(0);
	}
string Mvia::getNet2(void) {
	return("");
	}
string Mvia::getNet3(void) {
	return("");
	}
string Mvia::getNet4(void) {
	return("");
	}
int Mvia::getNpoint(void) {
	return(0);
	}
long double Mvia::getP(int _n, bool _xy, bool _r, bool _abs) {
	(void) _n;
	(void) _xy;
	(void) _r;
	(void) _abs;
	return(1);
	}
int Mvia::setW(long double _w) {
	(void) _w;
	return(1);
	}
int Mvia::setL(long double _l) {
	(void) _l;
	return(1);
	}
int Mvia::setNet2(string _net2) {
	(void) _net2;
	return(1);
	}
int Mvia::setNet3(string _net3) {
	(void) _net3;
	return(1);
	}
int Mvia::setNet4(string _net4) {
	(void) _net4;
	return(1);
	}
int Mvia::setP(void) {
	return(1);
	}
