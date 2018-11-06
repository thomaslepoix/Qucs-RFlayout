/***************************************************************************
                               mtee.cpp
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

#include "mtee.h"
using namespace std;

Mtee::Mtee(string _label,
			string _type,
			short _mirrorx,
			short _r,
			short _nport,
			long double _w1,
			long double _w2,
			long double _w3) :
	Element(_label, _type, _mirrorx, _r, _nport),
	m_w1(_w1),
	m_w2(_w2),
	m_w3(_w3)
	{}

Mtee::~Mtee() {
	}

long double Mtee::getW1(void) {
	return(m_w1);
	}

long double Mtee::getW2(void) {
	return(m_w2);
	}

long double Mtee::getW3(void) {
	return(m_w3);
	}

string Mtee::getNet1(void) {
	return(m_net1);
	}

string Mtee::getNet2(void) {
	return(m_net2);
	}

string Mtee::getNet3(void) {
	return(m_net3);
	}

int Mtee::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

int Mtee::setNet2(string _net2) {
	m_net2=_net2;
	return(0);
	}

int Mtee::setNet3(string _net3) {
	m_net3=_net3;
	return(0);
	}

////////////////////////////////////////////////////////////////////////////////

long double Mtee::getW(void) {
	return(0);
	}
long double Mtee::getW4(void) {
	return(0);
	}
long double Mtee::getL(void) {
	return(0);
	}
long double Mtee::getD(void) {
	return(0);
	}
long double Mtee::getS(void) {
	return(0);
	}
long double Mtee::getRi(void) {
	return(0);
	}
long double Mtee::getRo(void) {
	return(0);
	}
short Mtee::getAlpha(void) {
	return(0);
	}
string Mtee::getNet4(void) {
	return("");
	}
int Mtee::setNet4(string _net4) {
	return(1);
	}
