/***************************************************************************
                               mcorn.cpp
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

#include "mcorn.h"
using namespace std;

Mcorn::Mcorn(string _label,
			string _type,
			bool _mirrorx,
			short _r,
			short _nport,
			long double _w) :
	Element(_label, _type, _mirrorx, _r, _nport),
	m_w(_w)
	{}

Mcorn::~Mcorn() {
	}

string Mcorn::getDescriptor(void) {
	return(m_descriptor);
	}

long double Mcorn::getW(void) {
	return(m_w);
	}

string Mcorn::getNet1(void) {
	return(m_net1);
	}

string Mcorn::getNet2(void) {
	return(m_net2);
	}

int Mcorn::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

int Mcorn::setNet2(string _net2) {
	m_net2=_net2;
	return(0);
	}

//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int Mcorn::getNpoint(void) {
	return(m_npoint);
	}

long double Mcorn::getP(int _n, bool _xy, bool _r, bool _abs) {
	(void) _r;
	return(_abs ? tab_p[_n][_xy]+(_xy ? m_y : m_x) : tab_p[_n][_xy]);
	}

int Mcorn::setP(void) {
	tab_p[0][_X]=-m_w/2;
	tab_p[0][_Y]= m_w/2;
	tab_p[1][_X]= m_w/2;
	tab_p[1][_Y]= m_w/2;
	tab_p[2][_X]= m_w/2;
	tab_p[2][_Y]=-m_w/2;
	tab_p[3][_X]=-m_w/2;
	tab_p[3][_Y]=-m_w/2;
	return(0);
	}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
////////////////////////////////////////////////////////////////////////////////

long double Mcorn::getW1(void) {
	return(0);
	}
long double Mcorn::getW2(void) {
	return(0);
	}
long double Mcorn::getW3(void) {
	return(0);
	}
long double Mcorn::getW4(void) {
	return(0);
	}
long double Mcorn::getL(void) {
	return(0);
	}
long double Mcorn::getD(void) {
	return(0);
	}
long double Mcorn::getS(void) {
	return(0);
	}
long double Mcorn::getRi(void) {
	return(0);
	}
long double Mcorn::getRo(void) {
	return(0);
	}
short Mcorn::getAlpha(void) {
	return(0);
	}
string Mcorn::getNet3(void) {
	return("");
	}
string Mcorn::getNet4(void) {
	return("");
	}
int Mcorn::setNet3(string _net3) {
	(void) _net3;
	return(1);
	}
int Mcorn::setNet4(string _net4) {
	(void) _net4;
	return(1);
	}
