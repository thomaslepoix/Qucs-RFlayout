/***************************************************************************
                               sp.cpp
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

#include "sp.hpp"
using namespace std;

Sp::Sp(string _label,
			string _type,
			bool _mirrorx,
			short _r,
			std::string _simtype,
			long double _fstart,
			long double _fstop,
			unsigned long _n) :
	Element(_label, _type, true, _mirrorx, _r, 0, ""),
	m_simtype(_simtype),
	m_fstart(_fstart),
	m_fstop(_fstop),
	m_n(_n)
	{}

Sp::~Sp() {
	}

string Sp::getDescriptor(void) {
	return(m_descriptor);
	}

long double Sp::getFstart(void) {
	return(m_fstart);
	}

long double Sp::getFstop(void) {
	return(m_fstop);
	}

string Sp::getSimtype(void) {
	return(m_simtype);
	}

unsigned long Sp::getN(void) {
	return(m_n);
	}

