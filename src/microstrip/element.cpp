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

#include "element.hpp"
using namespace std;

Element::Element(string _label,
			string _type,
			bool _active,
			bool _mirrorx,
			short _r,
			short _nport,
			string _subst) :
	m_label(_label),
	m_type(_type),
	m_active(_active),
	m_mirrorx(_mirrorx),
	m_r(_r),
	m_nport(_nport),
	m_subst(_subst)
	{}

Element::~Element() {
	}

string Element::getLabel(void) {
	return(m_label);
	}

string Element::getType(void) {
	return(m_type);
	}

bool Element::getActive(void) {
	return(m_active);
	}

bool Element::getMirrorx(void) {
	return(m_mirrorx);
	}

short Element::getR(void) {
	return(m_r);
	}

short Element::getNport(void) {
	return(m_nport);
	}

string Element::getSubst(void) {
	return(m_subst);
	}

long double Element::getX(void) {
	return(m_shift_x ? m_x+m_shift_x : m_x);
	}

long double Element::getY(void) {
	return(m_shift_y ? m_y+m_shift_y : m_y);
	}

int Element::setX(long double _x) {
	m_x=_x;
	return(0);
	}

int Element::setY(long double _y) {
	m_y=_y;
	return(0);
	}

int Element::setShiftX(long double _shift_x) {
	m_shift_x=_shift_x;
	return(0);
	}

int Element::setShiftY(long double _shift_y) {
	m_shift_y=_shift_y;
	return(0);
	}

long double Element::rotateX(long double _x, long double _y) {
	return(_x*cos((M_PI/180)*m_r)+_y*sin((M_PI/180)*m_r));
	}

long double Element::rotateY(long double _x, long double _y) {
	return(-_x*sin((M_PI/180)*m_r)+_y*cos((M_PI/180)*m_r));
	}

////////////////////////////////////////////////////////////////////////////////

string Element::getDescriptor(void) {
	return("");
	}

long double Element::getW(void) {
	return(0);
	}

long double Element::getW1(void) {
	return(0);
	}

long double Element::getW2(void) {
	return(0);
	}

long double Element::getW3(void) {
	return(0);
	}

long double Element::getW4(void) {
	return(0);
	}

long double Element::getL(void) {
	return(0);
	}

long double Element::getD(void) {
	return(0);
	}

long double Element::getS(void) {
	return(0);
	}

long double Element::getRi(void) {
	return(0);
	}

long double Element::getRo(void) {
	return(0);
	}

long double Element::getZ(void) {
	return(0);
	}

long double Element::getDbm(void) {
	return(0);
	}

long double Element::getF(void) {
	return(0);
	}

long double Element::getFstart(void) {
	return(0);
	}

long double Element::getFstop(void) {
	return(0);
	}

long double Element::getEr(void) {
	return(0);
	}

long double Element::getH(void) {
	return(0);
	}

long double Element::getT(void) {
	return(0);
	}

long double Element::getTand(void) {
	return(0);
	}

long double Element::getRho(void) {
	return(0);
	}

long double Element::getMargin(void) {
	return(0);
	}

unsigned long Element::getN(void) {
	return(0);
	}

short Element::getAlpha(void) {
	return(0);
	}

string Element::getSimtype(void) {
	return("");
	}

string Element::getNet1(void) {
	return("");
	}

string Element::getNet2(void) {
	return("");
	}

string Element::getNet3(void) {
	return("");
	}

string Element::getNet4(void) {
	return("");
	}

int Element::getNpoint(void) {
	return(0);
	}

long double Element::getP(int /*_n*/, axis_t /*_xy*/, orientation_t /*_r*/, origin_t /*_abs*/) {
	return(0);
	}

void Element::getStep(int const /*_net*/, long double& xstep, long double& ystep) {
	xstep=0;
	ystep=0;
	}

void Element::getEdge(int const /*_net*/, long double& edge, short& dir) {
	edge=0;
	dir=0;
	}

int Element::getOemsNcorelines(void) {
	return(0);
	}

int Element::getOemsMeshCore(int const /*_n*/, OemsLine& /*line*/) {
	return(1);
	}

int Element::getOemsMeshInterface(int const /*_net*/, OemsLine& /*line*/) {
	return(1);
	}

bool Element::isOemsMeshInterface(int const /*_port*/, long double const /*_w*/) {
	return(false);
	}

int Element::setAdjacent(int const /*_port*/, shared_ptr<Element> const& /*element*/, int const /*adjacent_port*/) {
	return(1);
	}

int Element::setW(long double /*_w*/) {
	return(1);
	}

int Element::setL(long double /*_l*/) {
	return(1);
	}

int Element::setR(short /*_r*/) {
	return(1);
	}

int Element::setSubst(string /*_subst*/) {
	return(1);
	}

int Element::setNet1(string /*_net1*/) {
	return(1);
	}

int Element::setNet2(string /*_net2*/) {
	return(1);
	}

int Element::setNet3(string /*_net3*/) {
	return(1);
	}

int Element::setNet4(string /*_net4*/) {
	return(1);
	}

int Element::setP(void) {
	return(1);
	}
