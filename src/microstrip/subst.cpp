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
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "subst.hpp"
using namespace std;

//******************************************************************************
string const Subst::m_descriptor("substrat");

//******************************************************************************
Subst::Subst(string const _label,
			string const _type,
			bool const _mirrorx,
			short const _r,
			long double const _er,
			long double const _h,
			long double const _t,
			long double const _tand,
			long double const _rho,
			long double const _d,
			unsigned int const _margin_factor) :
	Element(_label, _type, true, _mirrorx, _r, 0, ""),
	m_w(0.0),
	m_l(0.0),
	m_er(_er),
	m_h(_h),
	m_t(_t),
	m_tand(_tand),
	m_rho(_rho),
	m_d(_d),
	m_margin(_margin_factor*_h),
	substrate_boundary({ 0.0, 0.0, 0.0, 0.0 })
	{}

//******************************************************************************
Subst::Subst(Subst const& _subst) :
	Element(_subst.m_label,
		_subst.m_type,
		true,
		_subst.m_mirrorx,
		_subst.m_r,
		0,
		""),
	m_w(0.0),
	m_l(0.0),
	m_er(_subst.m_er),
	m_h(_subst.m_h),
	m_t(_subst.m_t),
	m_tand(_subst.m_tand),
	m_rho(_subst.m_rho),
	m_d(_subst.m_d),
	m_margin(_subst.m_margin),
	substrate_boundary({ 0.0, 0.0, 0.0, 0.0 })
	{}

//******************************************************************************
string Subst::getDescriptor() const {
	return(m_descriptor);
	}

//******************************************************************************
long double Subst::getL() const {
	return(m_l);
	}

//******************************************************************************
long double Subst::getW() const {
	return(m_w);
	}

//******************************************************************************
long double Subst::getEr() const {
	return(m_er);
	}

//******************************************************************************
long double Subst::getH() const {
	return(m_h);
	}

//******************************************************************************
long double Subst::getT() const {
	return(m_t);
	}

//******************************************************************************
long double Subst::getTand() const {
	return(m_tand);
	}

//******************************************************************************
long double Subst::getRho() const {
	return(m_rho);
	}

//******************************************************************************
long double Subst::getD() const {
	return(m_d);
	}

//******************************************************************************
long double Subst::getMargin() const {
	return(m_margin);
	}

//******************************************************************************
int Subst::getNpoint() const {
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
int Subst::setP() {
	tab_p[0][X]=-m_l/2;
	tab_p[0][Y]= m_w/2;
	tab_p[1][X]= m_l/2;
	tab_p[1][Y]= m_w/2;
	tab_p[2][X]= m_l/2;
	tab_p[2][Y]=-m_w/2;
	tab_p[3][X]=-m_l/2;
	tab_p[3][Y]=-m_w/2;
	substrate_boundary[XMIN]=getP(0, X, R, ABS);
	substrate_boundary[XMAX]=getP(1, X, R, ABS);
	substrate_boundary[YMIN]=getP(2, Y, R, ABS);
	substrate_boundary[YMAX]=getP(0, Y, R, ABS);
	return(0);
	}
