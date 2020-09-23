/***************************************************************************
                               element.cpp
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

#define _USE_MATH_DEFINES

#include <cmath>

#include "element.hpp"
using namespace std;

//******************************************************************************
Element::Element(string const _label,
			string const _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			short const _nport,
			string const _subst) :
	m_label(_label),
	m_type(_type),
	m_active(_active),
	m_mirrorx(_mirrorx),
	m_r(_r),
	m_nport(_nport),
	m_subst(_subst),
	m_x(NAN),
	m_y(NAN),
	m_shift_x(0.0),
	m_shift_y(0.0),
	prev(nullptr)
	{}

//******************************************************************************
string Element::getLabel(void) const {
	return(m_label);
	}

//******************************************************************************
string Element::getType(void) const {
	return(m_type);
	}

//******************************************************************************
bool Element::getActive(void) const {
	return(m_active);
	}

//******************************************************************************
bool Element::getMirrorx(void) const {
	return(m_mirrorx);
	}

//******************************************************************************
short Element::getR(void) const {
	return(m_r);
	}

//******************************************************************************
short Element::getNport(void) const {
	return(m_nport);
	}

//******************************************************************************
string Element::getSubst(void) const {
	return(m_subst);
	}

//******************************************************************************
long double Element::getX(bool const apply_shift) const {
	return(m_shift_x && apply_shift ? m_x+m_shift_x : m_x); // Avoid useless float calcul.
	}

//******************************************************************************
long double Element::getY(bool const apply_shift) const {
	return(m_shift_y && apply_shift ? m_y+m_shift_y : m_y); // Avoid useless float calcul.
	}

//******************************************************************************
int Element::setX(long double const _x) {
	m_x=_x;
	return(0);
	}

//******************************************************************************
int Element::setY(long double const _y) {
	m_y=_y;
	return(0);
	}

//******************************************************************************
int Element::setShiftX(long double const _shift_x) {
	m_shift_x=_shift_x;
	return(0);
	}

//******************************************************************************
int Element::setShiftY(long double const _shift_y) {
	m_shift_y=_shift_y;
	return(0);
	}

//******************************************************************************
long double Element::rotateX(long double const _x, long double const _y) const {
	return(_x*cos((M_PI/180)*m_r)+_y*sin((M_PI/180)*m_r));
	}

//******************************************************************************
long double Element::rotateY(long double const _x, long double const _y) const {
	return(-_x*sin((M_PI/180)*m_r)+_y*cos((M_PI/180)*m_r));
	}

////////////////////////////////////////////////////////////////////////////////

//******************************************************************************
string Element::getDescriptor(void) const {
	return("");
	}

//******************************************************************************
long double Element::getW(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getW1(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getW2(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getW3(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getW4(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getL(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getD(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getS(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getRi(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getRo(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getZ(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getDbm(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getF(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getFstart(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getFstop(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getEr(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getH(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getT(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getTand(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getRho(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getMargin(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getAlpha(void) const {
	return(0);
	}

//******************************************************************************
unsigned long Element::getN(void) const {
	return(0);
	}

//******************************************************************************
string Element::getSimtype(void) const {
	return("");
	}

//******************************************************************************
string Element::getNet1(void) const {
	return("");
	}

//******************************************************************************
string Element::getNet2(void) const {
	return("");
	}

//******************************************************************************
string Element::getNet3(void) const {
	return("");
	}

//******************************************************************************
string Element::getNet4(void) const {
	return("");
	}

//******************************************************************************
int Element::getNpoint(void) const {
	return(0);
	}

//******************************************************************************
long double Element::getP(int const /*_n*/, axis_t const /*_xy*/, orientation_t const /*_r*/, origin_t const /*_abs*/, bool const /*apply_shift*/) const {
	return(0);
	}

//******************************************************************************
void Element::getStep(int const /*_net*/, long double& xstep, long double& ystep) const {
	xstep=0;
	ystep=0;
	}

//******************************************************************************
void Element::getEdge(int const /*_net*/, long double& edge, short& dir) const {
	edge=0;
	dir=0;
	}

//******************************************************************************
int Element::getOemsNcorelines(void) const {
	return(0);
	}

//******************************************************************************
int Element::getOemsMeshCore(int const /*_n*/, OemsLine& /*line*/) const {
	return(1);
	}

//******************************************************************************
int Element::getOemsMeshInterface(int const /*_net*/, OemsLine& /*line*/) const {
	return(1);
	}

//******************************************************************************
bool Element::isOemsMeshInterface(int const /*_port*/, long double const /*_w*/) const {
	return(false);
	}

//******************************************************************************
int Element::setAdjacent(int const /*_port*/, shared_ptr<Element> const& /*element*/, int const /*adjacent_port*/) {
	return(1);
	}

//******************************************************************************
int Element::setW(long double const /*_w*/) {
	return(1);
	}

//******************************************************************************
int Element::setL(long double const /*_l*/) {
	return(1);
	}

//******************************************************************************
int Element::setR(short const /*_r*/) {
	return(1);
	}

//******************************************************************************
int Element::setSubst(string const /*_subst*/) {
	return(1);
	}

//******************************************************************************
int Element::setNet1(string const /*_net1*/) {
	return(1);
	}

//******************************************************************************
int Element::setNet2(string const /*_net2*/) {
	return(1);
	}

//******************************************************************************
int Element::setNet3(string const /*_net3*/) {
	return(1);
	}

//******************************************************************************
int Element::setNet4(string const /*_net4*/) {
	return(1);
	}

//******************************************************************************
int Element::setP(void) {
	return(1);
	}
