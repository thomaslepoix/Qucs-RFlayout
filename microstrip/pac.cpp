/***************************************************************************
                               pac.cpp
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

#include "pac.h"
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

short Pac::getN(void) {
	return(m_n);
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

////////////////////////////////////////////////////////////////////////////////

long double Pac::getW(void) {
	return(0);
	}
long double Pac::getW1(void) {
	return(0);
	}
long double Pac::getW2(void) {
	return(0);
	}
long double Pac::getW3(void) {
	return(0);
	}
long double Pac::getW4(void) {
	return(0);
	}
long double Pac::getL(void) {
	return(0);
	}
long double Pac::getD(void) {
	return(0);
	}
long double Pac::getS(void) {
	return(0);
	}
long double Pac::getRi(void) {
	return(0);
	}
long double Pac::getRo(void) {
	return(0);
	}
long double Pac::getEr(void) {
	return(0);
	}
long double Pac::getH(void) {
	return(0);
	}
long double Pac::getT(void) {
	return(0);
	}
long double Pac::getTand(void) {
	return(0);
	}
long double Pac::getRho(void) {
	return(0);
	}
short Pac::getAlpha(void) {
	return(0);
	}
string Pac::getNet3(void) {
	return("");
	}
string Pac::getNet4(void) {
	return("");
	}
int Pac::getNpoint(void) {
	return(0);
	}
long double Pac::getP(int _n, bool _xy, bool _r, bool _abs) {
	(void) _n;
	(void) _xy;
	(void) _r;
	(void) _abs;
	return(1);
	}
int Pac::setW(long double _w) {
	(void) _w;
	return(1);
	}
int Pac::setL(long double _l) {
	(void) _l;
	return(1);
	}
int Pac::setNet3(string _net3) {
	(void) _net3;
	return(1);
	}
int Pac::setNet4(string _net4) {
	(void) _net4;
	return(1);
	}
int Pac::setP(void) {
	return(1);
	}
