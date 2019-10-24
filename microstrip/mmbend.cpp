/***************************************************************************
                               mmbend.cpp
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

#include "mmbend.h"
using namespace std;

Mmbend::Mmbend(string _label,
			string _type,
			bool _mirrorx,
			short _r,
			short _nport,
			long double _w) :
	Element(_label, _type, _mirrorx, _r, _nport),
	m_w(_w)
	{}

Mmbend::~Mmbend() {
	}

string Mmbend::getDescriptor(void) {
	return(m_descriptor);
	}

long double Mmbend::getW(void) {
	return(m_w);
	}

string Mmbend::getNet1(void) {
	return(m_net1);
	}

string Mmbend::getNet2(void) {
	return(m_net2);
	}

int Mmbend::getNpoint(void) {
	return(m_npoint);
	}

long double Mmbend::getP(int _n, bool _xy, bool _r, bool _abs) {
	long double coord;
	if(_r) {
		coord= _xy ? rotateY(tab_p[_n][EL_X], tab_p[_n][EL_Y]) : rotateX(tab_p[_n][EL_X], tab_p[_n][EL_Y]);
	} else {
		coord=tab_p[_n][_xy];
		}
	return(_abs ? coord+(_xy ? m_y : m_x) : coord);
	}

int Mmbend::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

int Mmbend::setNet2(string _net2) {
	m_net2=_net2;
	return(0);
	}

int Mmbend::setP(void) {
	signed short s1;
	signed short s2;
	if(m_mirrorx==0) {
		s1= 1;
		s2=-1;
	} else if(m_mirrorx==1) {
		s1=-1;
		s2= 1;
		}
	tab_p[0][EL_X]=-m_w/2;
	tab_p[0][EL_Y]=s1*m_w/2;
	tab_p[1][EL_X]= m_w/2;
	tab_p[1][EL_Y]=s1*m_w/2;
	tab_p[2][EL_X]=-m_w/2;
	tab_p[2][EL_Y]=s2*m_w/2;
	return(0);
	}

////////////////////////////////////////////////////////////////////////////////

long double Mmbend::getW1(void) {
	return(0);
	}
long double Mmbend::getW2(void) {
	return(0);
	}
long double Mmbend::getW3(void) {
	return(0);
	}
long double Mmbend::getW4(void) {
	return(0);
	}
long double Mmbend::getL(void) {
	return(0);
	}
long double Mmbend::getD(void) {
	return(0);
	}
long double Mmbend::getS(void) {
	return(0);
	}
long double Mmbend::getRi(void) {
	return(0);
	}
long double Mmbend::getRo(void) {
	return(0);
	}
short Mmbend::getAlpha(void) {
	return(0);
	}
string Mmbend::getNet3(void) {
	return("");
	}
string Mmbend::getNet4(void) {
	return("");
	}
int Mmbend::setNet3(string _net3) {
	(void) _net3;
	return(1);
	}
int Mmbend::setNet4(string _net4) {
	(void) _net4;
	return(1);
	}
