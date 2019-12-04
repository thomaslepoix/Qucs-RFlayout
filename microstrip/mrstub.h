/***************************************************************************
                               mrstub.h
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

#ifndef MRSTUB_H
#define MRSTUB_H

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include "element.h"

class Mrstub : public Element {
private :
	const std::string m_descriptor="microstrip_radial_stub";
	long double m_w;
	long double m_l;
	long double m_ri;
	long double m_ro;
	long double m_alpha;
	std::string m_net1;
	static const int m_npoint=53;
	long double tab_p[m_npoint][2]={};
public :
	Mrstub(std::string _label,
			std::string _type,
			bool _mirrorx,
			short _r,
			short _nport,
			long double _ri,
			long double _ro,
			short _alpha);
	~Mrstub();
	std::string getDescriptor(void);
	long double getW(void);
	long double getL(void);
	long double getRi(void);
	long double getRo(void);
	short getAlpha(void);
	std::string getNet1(void);
	int getNpoint(void);
	long double getP(int _n, axis_t _xy, orientation_t _r=NOR, origin_t _abs=REL);
	int setNet1(std::string _net1);
	int setP(void);
};

#endif // MRSTUB_H
