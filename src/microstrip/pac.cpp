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
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "pac.hpp"
using namespace std;

//******************************************************************************
string const Pac::m_descriptor("ac_port");

//******************************************************************************
Pac::Pac(string const _label,
			string const _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			unsigned long const _n,
			long double const _z,
			long double const _p,
			long double const _f) :
	Element(_label, _type, _active, _mirrorx, _r, 2, ""),
	m_n(_n),
	m_z(_z),
	m_p(_p),
	m_f(_f),
	m_w(0.0),
	m_l(0.0)
	{}

//******************************************************************************
string Pac::getDescriptor() const {
	return(m_descriptor);
	}

//******************************************************************************
long double Pac::getW() const {
	return(m_w);
	}

//******************************************************************************
long double Pac::getL() const {
	return(m_l);
	}

//******************************************************************************
long double Pac::getZ() const {
	return(m_z);
	}

//******************************************************************************
long double Pac::getDbm() const {
	return(m_p);
	}

//******************************************************************************
long double Pac::getF() const {
	return(m_f);
	}

//******************************************************************************
unsigned long Pac::getN() const {
	return(m_n);
	}

//******************************************************************************
string Pac::getNet1() const {
	return(m_net1);
	}

//******************************************************************************
string Pac::getNet2() const {
	return(m_net2);
	}

//******************************************************************************
int Pac::getNpoint() const {
	return(m_npoint);
	}

//******************************************************************************
long double Pac::getP(int const _n, axis_t const _xy, orientation_t const _r, origin_t const _abs, bool const apply_shift) const {
	long double coord;
	if(_r) {
		coord= _xy ? rotateY(tab_p[_n][X], tab_p[_n][Y])
		           : rotateX(tab_p[_n][X], tab_p[_n][Y]);
	} else {
		coord=tab_p[_n][_xy];
		}
	return(_abs ? coord+(_xy ? getY(apply_shift) : getX(apply_shift)) : coord);
	}

//******************************************************************************
void Pac::getEdge(int const _net, long double& edge, short& dir) const {
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

//******************************************************************************
int Pac::setNet1(string const _net1) {
	m_net1=_net1;
	return(0);
	}

//******************************************************************************
int Pac::setNet2(string const _net2) {
	m_net2=_net2;
	return(0);
	}

//******************************************************************************
int Pac::setSubst(string const _subst) {
	m_subst=_subst;
	return(0);
	}

//******************************************************************************
int Pac::setW(long double const _w) {
	m_w=_w;
	return(0);
	}

//******************************************************************************
int Pac::setL(long double const _l) {
	m_l=_l;
	return(0);
	}

//******************************************************************************
int Pac::setR(short const _r) {
	m_r=_r;
	return(0);
	}

//******************************************************************************
int Pac::setP() {
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

//******************************************************************************
int Pac::getOemsNcorelines() const {
	return(2);
	}

//******************************************************************************
int Pac::getOemsMeshCore(int const _n, OemsLine& line) const {
	if(_n==0) {
		line.position=getX();
		line.direction=XMIN;
	} else if(_n==1) {
		line.position=getY();
		line.direction=YMIN;
		}

	line.label=m_label;
	line.type=m_type;
	line.third_rule=false;
	return(0);
	}
