/***************************************************************************
                               pac.cpp
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

#include "pac.hpp"
using namespace std;

Pac::Pac(string _label,
			string _type,
			bool _active,
			bool _mirrorx,
			short _r,
			unsigned long _n,
			long double _z,
			long double _p,
			long double _f) :
	Element(_label, _type, _active, _mirrorx, _r, 2, ""),
	m_n(_n),
	m_z(_z),
	m_p(_p),
	m_f(_f),
	m_w(0.0),
	m_l(0.0)
	{}

Pac::~Pac() {
	}

string Pac::getDescriptor(void) {
	return(m_descriptor);
	}

long double Pac::getW(void) {
	return(m_w);
	}

long double Pac::getL(void) {
	return(m_l);
	}

long double Pac::getZ(void) {
	return(m_z);
	}

long double Pac::getDbm(void) {
	return(m_p);
	}

long double Pac::getF(void) {
	return(m_f);
	}

unsigned long Pac::getN(void) {
	return(m_n);
	}

string Pac::getNet1(void) {
	return(m_net1);
	}

string Pac::getNet2(void) {
	return(m_net2);
	}

int Pac::getNpoint(void) {
	return(m_npoint);
	}

long double Pac::getP(int _n, axis_t _xy, orientation_t _r, origin_t _abs) {
	long double coord;
	if(_r) {
		coord= _xy ? rotateY(tab_p[_n][X], tab_p[_n][Y])
		           : rotateX(tab_p[_n][X], tab_p[_n][Y]);
	} else {
		coord=tab_p[_n][_xy];
		}
	return(_abs ? coord+(_xy ? m_y : m_x) : coord);
	}

void Pac::getEdge(int const _net, long double& edge, short& dir) {
	edge=m_w;
	if(_net==1) {
		switch(m_r) {
			case 0: dir=XMIN; break;
			case 90: dir=YMAX; break;
			case 180: dir=XMAX; break;
			case 270: dir=YMIN; break;
			}
	} else if(_net==2) {
		switch(m_r) {
			case 0: dir=XMAX; break;
			case 90: dir=YMIN; break;
			case 180: dir=XMIN; break;
			case 270: dir=YMAX; break;
			}
		}
	}

int Pac::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

int Pac::setNet2(string _net2) {
	m_net2=_net2;
	return(0);
	}

int Pac::setSubst(string _subst) {
	m_subst=_subst;
	return(0);
	}

int Pac::setW(long double _w) {
	m_w=_w;
	return(0);
	}

int Pac::setL(long double _l) {
	m_l=_l;
	return(0);
	}

int Pac::setR(short _r) {
	m_r=_r;
	return(0);
	}

int Pac::setP(void) {
	tab_p[0][X]=-m_l/2;
	tab_p[0][Y]= m_w/2;
	tab_p[1][X]= m_l/2;
	tab_p[1][Y]= m_w/2;
	tab_p[2][X]= m_l/2;
	tab_p[2][Y]=-m_w/2;
	tab_p[3][X]=-m_l/2;
	tab_p[3][Y]=-m_w/2;
	return(0);
	}

int Pac::getOemsNcorelines(void) {
	return(2);
	}

int Pac::getOemsMeshCore(int const _n, OemsLine& line) {
	if(_n==0) {
		line.position=m_x;
		line.direction=XMIN;
	} else if(_n==1) {
		line.position=m_y;
		line.direction=YMIN;
		}

	line.label=m_label;
	line.type=m_type;
	line.third_rule=false;
	return(0);
	}

int Pac::getOemsMeshInterface(int const _net, OemsLine& line) {
	return(0);
	}
