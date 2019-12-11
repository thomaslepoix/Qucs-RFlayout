/***************************************************************************
                               mcoupled.cpp
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

#include "mcoupled.h"
using namespace std;

Mcoupled::Mcoupled(string _label,
			string _type,
			bool _mirrorx,
			short _r,
			short _nport,
			long double _w,
			long double _l,
			long double _s) :
	Element(_label, _type, _mirrorx, _r, _nport),
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

long double Mcoupled::getP(int _n, axis_t _xy, orientation_t _r, origin_t _abs) {
	long double coord;
	if(_r) {
		coord= _xy ? rotateY(tab_p[_n][X], tab_p[_n][Y])
		           : rotateX(tab_p[_n][X], tab_p[_n][Y]);
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
	tab_p[0][X]=-m_l/2;
	tab_p[0][Y]= (m_s/2+m_w);
	tab_p[1][X]= m_l/2;
	tab_p[1][Y]= (m_s/2+m_w);
	tab_p[2][X]= m_l/2;
	tab_p[2][Y]= m_s/2;
	tab_p[3][X]=-m_l/2;
	tab_p[3][Y]= m_s/2;
	tab_p[4][X]=-m_l/2;
	tab_p[4][Y]=-m_s/2;
	tab_p[5][X]= m_l/2;
	tab_p[5][Y]=-m_s/2;
	tab_p[6][X]= m_l/2;
	tab_p[6][Y]=-(m_s/2+m_w);
	tab_p[7][X]=-m_l/2;
	tab_p[7][Y]=-(m_s/2+m_w);
	return(0);
	}
