/***************************************************************************
                               subst.cpp
                             ------------------
    begin                : Thu Oct 25 2018
    copyright            : (C) 2018 by Thomas Lepoix
    email                : thomas.lepoix@protonmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "subst.hpp"
using namespace std;

//******************************************************************************
string const Subst::m_descriptor("substrat");

//******************************************************************************
Subst::Subst(string _label,
			string _type,
			bool _mirrorx,
			short _r,
			long double _er,
			long double _h,
			long double _t,
			long double _tand,
			long double _rho,
			long double _d,
			unsigned int _margin_factor) :
	Element(_label, _type, true, _mirrorx, _r, 0, ""),
	m_w(0.0),
	m_l(0.0),
	m_er(_er),
	m_h(_h),
	m_t(_t),
	m_tand(_tand),
	m_rho(_rho),
	m_d(_d),
	m_margin(_margin_factor*_h)
	{}

//******************************************************************************
Subst::Subst(Subst const* _subst) :
	Element(_subst->m_label,
		_subst->m_type,
		true,
		_subst->m_mirrorx,
		_subst->m_r,
		0,
		""),
	m_w(0.0),
	m_l(0.0),
	m_er(_subst->m_er),
	m_h(_subst->m_h),
	m_t(_subst->m_t),
	m_tand(_subst->m_tand),
	m_rho(_subst->m_rho),
	m_d(_subst->m_d),
	m_margin(_subst->m_margin)
	{}

//******************************************************************************
string Subst::getDescriptor(void) const {
	return(m_descriptor);
	}

//******************************************************************************
long double Subst::getL(void) const {
	return(m_l);
	}

//******************************************************************************
long double Subst::getW(void) const {
	return(m_w);
	}

//******************************************************************************
long double Subst::getEr(void) const {
	return(m_er);
	}

//******************************************************************************
long double Subst::getH(void) const {
	return(m_h);
	}

//******************************************************************************
long double Subst::getT(void) const {
	return(m_t);
	}

//******************************************************************************
long double Subst::getTand(void) const {
	return(m_tand);
	}

//******************************************************************************
long double Subst::getRho(void) const {
	return(m_rho);
	}

//******************************************************************************
long double Subst::getD(void) const {
	return(m_d);
	}

//******************************************************************************
long double Subst::getMargin(void) const {
	return(m_margin);
	}

//******************************************************************************
int Subst::getNpoint(void) const {
	return(m_npoint);
	}

//******************************************************************************
long double Subst::getP(int const _n, axis_t const _xy, orientation_t const _r, origin_t const _abs, bool const /*apply_shift*/) const {
	long double coord;
	if(_r) {
		coord= _xy ? rotateY(tab_p[_n][X], tab_p[_n][Y]) : rotateX(tab_p[_n][X], tab_p[_n][Y]);
	} else {
		coord=tab_p[_n][_xy];
		}
	return(_abs ? coord+(_xy ? m_y : m_x) : coord);
	}

//******************************************************************************
int Subst::setW(long double const _w) {
	m_w=_w;
	return(0);
	}

//******************************************************************************
int Subst::setL(long double const _l) {
	m_l=_l;
	return(0);
	}

//******************************************************************************
int Subst::setP(void) {
	tab_p[0][X]=-m_l/2;
	tab_p[0][Y]= m_w/2;
	tab_p[1][X]= m_l/2;
	tab_p[1][Y]= m_w/2;
	tab_p[2][X]= m_l/2;
	tab_p[2][Y]=-m_w/2;
	tab_p[3][X]=-m_l/2;
	tab_p[3][Y]=-m_w/2;
	extrem_pos[XMIN]=getP(0, X, R, ABS);
	extrem_pos[XMAX]=getP(1, X, R, ABS);
	extrem_pos[YMIN]=getP(2, Y, R, ABS);
	extrem_pos[YMAX]=getP(0, Y, R, ABS);
	return(0);
	}
