/***************************************************************************
                               mlin.cpp
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

#include "mlin.h"
using namespace std;

Mlin::Mlin(string _label,
			string _type,
			bool _mirrorx,
			short _r,
			short _nport,
			long double _w,
			long double _l) :
	Element(_label, _type, _mirrorx, _r, _nport),
	m_w(_w),
	m_l(_l)
	{}

Mlin::~Mlin() {
	}

string Mlin::getDescriptor(void) {
	return(m_descriptor);
	}

long double Mlin::getW(void) {
	return(m_w);
	}

long double Mlin::getL(void) {
	return(m_l);
	}

string Mlin::getNet1(void) {
	return(m_net1);
	}

string Mlin::getNet2(void) {
	return(m_net2);
	}

int Mlin::getNpoint(void) {
	return(m_npoint);
	}

long double Mlin::getP(int _n, bool _xy, bool _r, bool _abs) {
	long double coord;
	if(_r) {
		coord= _xy ? rotateY(tab_p[_n][EL_X], tab_p[_n][EL_Y]) : rotateX(tab_p[_n][EL_X], tab_p[_n][EL_Y]);
	} else {
		coord=tab_p[_n][_xy];
		}
	return(_abs ? coord+(_xy ? m_y : m_x) : coord);
	}

int Mlin::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

int Mlin::setNet2(string _net2) {
	m_net2=_net2;
	return(0);
	}

int Mlin::setP(void) {
	tab_p[0][EL_X]=-m_l/2;
	tab_p[0][EL_Y]= m_w/2;
	tab_p[1][EL_X]= m_l/2;
	tab_p[1][EL_Y]= m_w/2;
	tab_p[2][EL_X]= m_l/2;
	tab_p[2][EL_Y]=-m_w/2;
	tab_p[3][EL_X]=-m_l/2;
	tab_p[3][EL_Y]=-m_w/2;
	return(0);
	}
