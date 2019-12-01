/***************************************************************************
                               mrstub.cpp
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

#include "mrstub.h"
using namespace std;

Mrstub::Mrstub(string _label,
			string _type,
			bool _mirrorx,
			short _r,
			short _nport,
			long double _ri,
			long double _ro,
			short _alpha) :
	Element(_label, _type, _mirrorx, _r, _nport),
	m_ri(_ri),
	m_ro(_ro),
	m_alpha(_alpha){
	m_w=2*m_ri*sin((M_PI/180)*(m_alpha/2));
	m_l=sqrt((m_ri*m_ri)-((m_w/2)*(m_w/2)));
	}

Mrstub::~Mrstub() {
	}

string Mrstub::getDescriptor(void) {
	return(m_descriptor);
	}

long double Mrstub::getW(void) {
	return(m_w);
	}

long double Mrstub::getL(void) {
	return(m_l);
	}

long double Mrstub::getRi(void) {
	return(m_ri);
	}

long double Mrstub::getRo(void) {
	return(m_ro);
	}

short Mrstub::getAlpha(void) {
	return(m_alpha);
	}

string Mrstub::getNet1(void) {
	return(m_net1);
	}

int Mrstub::getNpoint(void) {
	return(m_npoint);
	}

long double Mrstub::getP(int _n, bool _xy, bool _r, bool _abs) {
	long double coord;
	if(_r) {
		coord= _xy ? rotateY(tab_p[_n][EL_X], tab_p[_n][EL_Y]) : rotateX(tab_p[_n][EL_X], tab_p[_n][EL_Y]);
	} else {
		coord=tab_p[_n][_xy];
		}
	return(_abs ? coord+(_xy ? m_y : m_x) : coord);
	}

int Mrstub::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

int Mrstub::setP(void) {
	int div=m_npoint-5;			//-4 fixed points, -1 number -> index
	long double n=m_alpha/div;
	long double u=-(m_npoint-2)/2*n+n;
	signed short s;
	if(m_mirrorx==0) s= 1;
	if(m_mirrorx==1) s=-1;
	tab_p[0][EL_X]= m_w/2;
	tab_p[0][EL_Y]=0;
	tab_p[1][EL_X]=-m_w/2;
	tab_p[1][EL_Y]=0;
	tab_p[2][EL_X]= m_ro*sin((M_PI/180)*(-m_alpha/2));
	tab_p[2][EL_Y]=s*((-m_ro*cos((M_PI/180)*(-m_alpha/2)))+m_l);
	for(int i=3;i<m_npoint-1;i++) {
		tab_p[i][EL_X]=m_ro*sin((M_PI/180)*(u));
		tab_p[i][EL_Y]=s*((-m_ro*cos((M_PI/180)*(u)))+m_l);
		u+=n;
		}
	tab_p[m_npoint-1][EL_X]=-m_ro*sin((M_PI/180)*(-m_alpha/2));
	tab_p[m_npoint-1][EL_Y]=s*((-m_ro*cos((M_PI/180)*(-m_alpha/2)))+m_l);
	return(0);
	}
