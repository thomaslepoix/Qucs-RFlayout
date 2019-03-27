/***************************************************************************
                               mrstub.cpp
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

int Mrstub::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int Mrstub::getNpoint(void) {
	return(m_npoint);
	}

long double Mrstub::getP(int _n, bool _xy, bool _r, bool _abs) {
	long double coord;
	if(_r) {
		coord= _xy ? rotateY(tab_p[_n][_X], tab_p[_n][_Y]) : rotateX(tab_p[_n][_X], tab_p[_n][_Y]);
	} else {
		coord=tab_p[_n][_xy];
		}
	return(_abs ? coord+(_xy ? m_y : m_x) : coord);
	}

int Mrstub::setP(void) {
	int n=int(m_alpha)/5;
	int i=3;
	signed short s;
	if(m_mirrorx==0) s= 1;
	if(m_mirrorx==1) s=-1;
	tab_p[0][_X]= m_w/2;
	tab_p[0][_Y]=0;
	tab_p[1][_X]=-m_w/2;
	tab_p[1][_Y]=0;
	tab_p[2][_X]= m_ro*sin((M_PI/180)*(-m_alpha/2));
	tab_p[2][_Y]=s*((-m_ro*cos((M_PI/180)*(-m_alpha/2)))-m_l);
	for(int u=-5*n/2;u<=5*n/2;u+=5) {
		tab_p[i][_X]=m_ro*sin((M_PI/180)*(u));
		tab_p[i][_Y]=s*((-m_ro*cos((M_PI/180)*(u)))-m_l);
		i++;
		}
	tab_p[22][_X]=-m_ro*sin((M_PI/180)*(-m_alpha/2));
	tab_p[22][_Y]=s*((-m_ro*cos((M_PI/180)*(-m_alpha/2)))-m_l);
	return(0);
	}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
////////////////////////////////////////////////////////////////////////////////

long double Mrstub::getW1(void) {
	return(0);
	}
long double Mrstub::getW2(void) {
	return(0);
	}
long double Mrstub::getW3(void) {
	return(0);
	}
long double Mrstub::getW4(void) {
	return(0);
	}
long double Mrstub::getD(void) {
	return(0);
	}
long double Mrstub::getS(void) {
	return(0);
	}
string Mrstub::getNet2(void) {
	return("");
	}
string Mrstub::getNet3(void) {
	return("");
	}
string Mrstub::getNet4(void) {
	return("");
	}
int Mrstub::setNet2(string _net2) {
	(void) _net2;
	return(1);
	}
int Mrstub::setNet3(string _net3) {
	(void) _net3;
	return(1);
	}
int Mrstub::setNet4(string _net4) {
	(void) _net4;
	return(1);
	}
