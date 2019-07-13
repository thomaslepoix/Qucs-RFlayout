/***************************************************************************
                               subst.cpp
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

#include "subst.h"
using namespace std;

Subst::Subst(string _label,
			string _type,
			bool _mirrorx,
			short _r,
			long double _er,
			long double _h,
			long double _t,
			long double _tand,
			long double _rho,
			long double _d) :
	Element(_label, _type, _mirrorx, _r, 0, ""),
	m_er(_er),
	m_h(_h),
	m_t(_t),
	m_tand(_tand),
	m_rho(_rho),
	m_d(_d)
	{}

Subst::~Subst() {
	}

string Subst::getDescriptor(void) {
	return(m_descriptor);
	}

long double Subst::getL(void) {
	return(m_l);
	}

long double Subst::getW(void) {
	return(m_w);
	}

long double Subst::getEr(void){
	return(m_er);
	}

long double Subst::getH(void){
	return(m_h);
	}

long double Subst::getT(void){
	return(m_t);
	}

long double Subst::getTand(void){
	return(m_tand);
	}

long double Subst::getRho(void){
	return(m_rho);
	}

long double Subst::getD(void) {
	return(m_d);
	}

int Subst::getNpoint(void) {
	return(m_npoint);
	}

long double Subst::getP(int _n, bool _xy, bool _r, bool _abs) {
	long double coord;
	if(_r) {
		coord= _xy ? rotateY(tab_p[_n][_X], tab_p[_n][_Y]) : rotateX(tab_p[_n][_X], tab_p[_n][_Y]);
	} else {
		coord=tab_p[_n][_xy];
		}
	return(_abs ? coord+(_xy ? m_y : m_x) : coord);
	}

int Subst::setW(long double _w) {
	m_w=_w;
	return(0);
	}

int Subst::setL(long double _l) {
	m_l=_l;
	return(0);
	}

int Subst::setP(void) {
	tab_p[0][_X]=-m_l/2;
	tab_p[0][_Y]= m_w/2;
	tab_p[1][_X]= m_l/2;
	tab_p[1][_Y]= m_w/2;
	tab_p[2][_X]= m_l/2;
	tab_p[2][_Y]=-m_w/2;
	tab_p[3][_X]=-m_l/2;
	tab_p[3][_Y]=-m_w/2;
	return(0);
	}

////////////////////////////////////////////////////////////////////////////////

long double Subst::getW1(void) {
	return(0);
	}
long double Subst::getW2(void) {
	return(0);
	}
long double Subst::getW3(void) {
	return(0);
	}
long double Subst::getW4(void) {
	return(0);
	}
long double Subst::getS(void) {
	return(0);
	}
long double Subst::getRi(void) {
	return(0);
	}
long double Subst::getRo(void) {
	return(0);
	}
long double Subst::getZ(void) {
	return(0);
	}
long double Subst::getDbm(void) {
	return(0);
	}
long double Subst::getF(void) {
	return(0);
	}
short Subst::getN(void) {
	return(0);
	}
short Subst::getAlpha(void) {
	return(0);
	}
string Subst::getNet1(void) {
	return("");
	}
string Subst::getNet2(void) {
	return("");
	}
string Subst::getNet3(void) {
	return("");
	}
string Subst::getNet4(void) {
	return("");
	}
int Subst::setNet1(string _net1) {
	(void) _net1;
	return(1);
	}
int Subst::setNet2(string _net2) {
	(void) _net2;
	return(1);
	}
int Subst::setNet3(string _net3) {
	(void) _net3;
	return(1);
	}
int Subst::setNet4(string _net4) {
	(void) _net4;
	return(1);
	}
