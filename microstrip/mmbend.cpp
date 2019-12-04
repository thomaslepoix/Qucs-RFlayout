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

long double Mmbend::getP(int _n, axis_t _xy, orientation_t _r, origin_t _abs) {
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
	signed short s1; //= m_mirror ? -1 :  1;
	signed short s2; //= m_mirror ?  1 : -1;
	if(m_mirrorx) {
		s1=-1;
		s2= 1;
	} else {
		s1= 1;
		s2=-1;
		}
	tab_p[0][EL_X]=  -m_w/2;
	tab_p[0][EL_Y]=s1*m_w/2;
	tab_p[1][EL_X]=   m_w/2;
	tab_p[1][EL_Y]=s1*m_w/2;
	tab_p[2][EL_X]=  -m_w/2;
	tab_p[2][EL_Y]=s2*m_w/2;
	return(0);
	}
