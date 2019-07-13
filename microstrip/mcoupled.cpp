/***************************************************************************
                               mcoupled.cpp
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

#include "mcoupled.h"
using namespace std;

Mcoupled::Mcoupled(string _label,
			string _type,
			bool _mirrorx,
			short _r,
			string _subst,
			long double _w,
			long double _l,
			long double _s) :
	Element(_label, _type, _mirrorx, _r, 4, _subst),
	m_w(_w),
	m_l(_l),
	m_s(_s)
	{}

Mcoupled::~Mcoupled() {
	}

string Mcoupled::getDescriptor(void) {
	return(m_descriptor);
	}

long double Mcoupled::getW(void) {
	return(m_w);
	}

long double Mcoupled::getL(void) {
	return(m_l);
	}

long double Mcoupled::getS(void) {
	return(m_s);
	}

string Mcoupled::getNet1(void) {
	return(m_net1);
	}

string Mcoupled::getNet2(void) {
	return(m_net2);
	}

string Mcoupled::getNet3(void) {
	return(m_net3);
	}

string Mcoupled::getNet4(void) {
	return(m_net4);
	}

int Mcoupled::getNpoint(void) {
	return(m_npoint);
	}

long double Mcoupled::getP(int _n, bool _xy, bool _r, bool _abs) {
	long double coord;
	if(_r) {
		coord= _xy ? rotateY(tab_p[_n][_X], tab_p[_n][_Y]) : rotateX(tab_p[_n][_X], tab_p[_n][_Y]);
	} else {
		coord=tab_p[_n][_xy];
		}
	return(_abs ? coord+(_xy ? m_y : m_x) : coord);
	}

int Mcoupled::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

int Mcoupled::setNet2(string _net2) {
	m_net2=_net2;
	return(0);
	}

int Mcoupled::setNet3(string _net3) {
	m_net3=_net3;
	return(0);
	}

int Mcoupled::setNet4(string _net4) {
	m_net4=_net4;
	return(0);
	}

int Mcoupled::setP(void) {
	tab_p[0][_X]=-m_l/2;
	tab_p[0][_Y]= (m_s/2+m_w);
	tab_p[1][_X]= m_l/2;
	tab_p[1][_Y]= (m_s/2+m_w);
	tab_p[2][_X]= m_l/2;
	tab_p[2][_Y]= m_s/2;
	tab_p[3][_X]=-m_l/2;
	tab_p[3][_Y]= m_s/2;
	tab_p[4][_X]=-m_l/2;
	tab_p[4][_Y]=-m_s/2;
	tab_p[5][_X]= m_l/2;
	tab_p[5][_Y]=-m_s/2;
	tab_p[6][_X]= m_l/2;
	tab_p[6][_Y]=-(m_s/2+m_w);
	tab_p[7][_X]=-m_l/2;
	tab_p[7][_Y]=-(m_s/2+m_w);
	return(0);
	}

////////////////////////////////////////////////////////////////////////////////

long double Mcoupled::getW1(void) {
	return(0);
	}
long double Mcoupled::getW2(void) {
	return(0);
	}
long double Mcoupled::getW3(void) {
	return(0);
	}
long double Mcoupled::getW4(void) {
	return(0);
	}
long double Mcoupled::getD(void) {
	return(0);
	}
long double Mcoupled::getRi(void) {
	return(0);
	}
long double Mcoupled::getRo(void) {
	return(0);
	}
long double Mcoupled::getZ(void) {
	return(0);
	}
long double Mcoupled::getDbm(void) {
	return(0);
	}
long double Mcoupled::getF(void) {
	return(0);
	}
long double Mcoupled::getEr(void) {
	return(0);
	}
long double Mcoupled::getH(void) {
	return(0);
	}
long double Mcoupled::getT(void) {
	return(0);
	}
long double Mcoupled::getTand(void) {
	return(0);
	}
long double Mcoupled::getRho(void) {
	return(0);
	}
short Mcoupled::getN(void) {
	return(0);
	}
short Mcoupled::getAlpha(void) {
	return(0);
	}
int Mcoupled::setW(long double _w) {
	(void) _w;
	return(1);
	}
int Mcoupled::setL(long double _l) {
	(void) _l;
	return(1);
	}
