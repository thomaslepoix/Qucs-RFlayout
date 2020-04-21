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

#include <cmath>

#include "mrstub.hpp"
using namespace std;

Mrstub::Mrstub(string _label,
			string _type,
			bool _active,
			bool _mirrorx,
			short _r,
			string _subst,
			long double _ri,
			long double _ro,
			short _alpha) :
	Element(_label, _type, _active, _mirrorx, _r, 1, _subst),
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

long double Mrstub::getP(int _n, axis_t _xy, orientation_t _r, origin_t _abs) {
	long double coord;
	if(_r) {
		coord= _xy ? rotateY(tab_p[_n][X], tab_p[_n][Y])
		           : rotateX(tab_p[_n][X], tab_p[_n][Y]);
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
	signed short s= m_mirrorx ? -1 : 1;

	tab_p[0][X]= m_w/2;
	tab_p[0][Y]=0;
	tab_p[1][X]=-m_w/2;
	tab_p[1][Y]=0;
	tab_p[2][X]= m_ro*sin((M_PI/180)*(-m_alpha/2));
	tab_p[2][Y]=s*((-m_ro*cos((M_PI/180)*(-m_alpha/2)))+m_l);
	for(int i=3;i<m_npoint-1;i++) {
		tab_p[i][X]=m_ro*sin((M_PI/180)*(u));
		tab_p[i][Y]=s*((-m_ro*cos((M_PI/180)*(u)))+m_l);
		u+=n;
		}
	tab_p[m_npoint-1][X]=-m_ro*sin((M_PI/180)*(-m_alpha/2));
	tab_p[m_npoint-1][Y]=s*((-m_ro*cos((M_PI/180)*(-m_alpha/2)))+m_l);
	return(0);
	}

void Mrstub::getEdge(int const /*_net*/, long double& edge, short& dir) {
	edge=m_w;
	if(m_mirrorx==0) {
		switch(m_r) {
			case 0: dir=YMAX; break;
			case 90: dir=XMAX; break;
			case 180: dir=YMIN; break;
			case 270: dir=XMIN; break;
			}
	} else if(m_mirrorx==1) {
		switch(m_r) {
			case 0: dir=YMIN; break;
			case 90: dir=XMIN; break;
			case 180: dir=YMAX; break;
			case 270: dir=XMAX; break;
			}
		}
	}
