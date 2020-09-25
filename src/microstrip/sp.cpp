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

//******************************************************************************
string const Sp::m_descriptor("s_parameter_simulation");

//******************************************************************************
Sp::Sp(string const _label,
			string const _type,
			bool const _mirrorx,
			short const _r,
			std::string const _simtype,
			long double const _fstart,
			long double const _fstop,
			unsigned long const _n) :
	Element(_label, _type, true, _mirrorx, _r, 0, ""),
	m_simtype(_simtype),
	m_fstart(_fstart),
	m_fstop(_fstop),
	m_n(_n)
	{}

//******************************************************************************
string Sp::getDescriptor() const {
	return(m_descriptor);
	}

//******************************************************************************
long double Sp::getFstart() const {
	return(m_fstart);
	}

//******************************************************************************
long double Sp::getFstop() const {
	return(m_fstop);
	}

//******************************************************************************
string Sp::getSimtype() const {
	return(m_simtype);
	}

//******************************************************************************
unsigned long Sp::getN() const {
	return(m_n);
	}
