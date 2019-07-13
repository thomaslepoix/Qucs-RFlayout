/***************************************************************************
                               eqn.cpp
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

#include "eqn.h"
using namespace std;

Eqn::Eqn(string _label,
			string _type,
			bool _mirrorx,
			short _r) :
	Element(_label, _type, _mirrorx, _r, 0, "")
	{}

Eqn::~Eqn() {
	}

string Eqn::getDescriptor(void) {
	return(m_descriptor);
	}

////////////////////////////////////////////////////////////////////////////////

long double Eqn::getW(void) {
	return(0);
	}
long double Eqn::getW1(void) {
	return(0);
	}
long double Eqn::getW2(void) {
	return(0);
	}
long double Eqn::getW3(void) {
	return(0);
	}
long double Eqn::getW4(void) {
	return(0);
	}
long double Eqn::getL(void) {
	return(0);
	}
long double Eqn::getD(void) {
	return(0);
	}
long double Eqn::getS(void) {
	return(0);
	}
long double Eqn::getRi(void) {
	return(0);
	}
long double Eqn::getRo(void) {
	return(0);
	}
long double Eqn::getZ(void) {
	return(0);
	}
long double Eqn::getDbm(void) {
	return(0);
	}
long double Eqn::getF(void) {
	return(0);
	}
long double Eqn::getEr(void) {
	return(0);
	}
long double Eqn::getH(void) {
	return(0);
	}
long double Eqn::getT(void) {
	return(0);
	}
long double Eqn::getTand(void) {
	return(0);
	}
long double Eqn::getRho(void) {
	return(0);
	}
short Eqn::getN(void) {
	return(0);
	}
short Eqn::getAlpha(void) {
	return(0);
	}
string Eqn::getNet1(void) {
	return("");
	}
string Eqn::getNet2(void) {
	return("");
	}
string Eqn::getNet3(void) {
	return("");
	}
string Eqn::getNet4(void) {
	return("");
	}
int Eqn::getNpoint(void) {
	return(0);
	}
long double Eqn::getP(int _n, bool _xy, bool _r, bool _abs) {
	(void) _n;
	(void) _xy;
	(void) _r;
	(void) _abs;
	return(1);
	}
int Eqn::setW(long double _w) {
	(void) _w;
	return(1);
	}
int Eqn::setL(long double _l) {
	(void) _l;
	return(1);
	}
int Eqn::setNet1(string _net1) {
	(void) _net1;
	return(1);
	}
int Eqn::setNet2(string _net2) {
	(void) _net2;
	return(1);
	}
int Eqn::setNet3(string _net3) {
	(void) _net3;
	return(1);
	}
int Eqn::setNet4(string _net4) {
	(void) _net4;
	return(1);
	}
int Eqn::setP(void) {
	return(1);
	}
