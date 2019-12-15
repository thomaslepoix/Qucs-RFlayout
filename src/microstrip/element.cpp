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

#include "element.h"
using namespace std;

Element::Element(string _label,
			string _type,
			bool _mirrorx,
			short _r,
			short _nport) :
	m_label(_label),
	m_type(_type),
	m_mirrorx(_mirrorx),
	m_r(_r),
	m_nport(_nport)
	{}

Element::~Element() {
	}

string Element::getLabel(void) {
	return(m_label);
	}

string Element::getType(void) {
	return(m_type);
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

long double Element::getX(void) {
	return(m_x);
	}

long double Element::getY(void) {
	return(m_y);
	}

int Element::setX(long double _x) {
	m_x=_x;
	return(0);
	}

int Element::setY(long double _y) {
	m_y=_y;
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

short Element::getAlpha(void) {
	return(0);
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
