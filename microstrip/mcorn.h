/***************************************************************************
                               mcorn.h
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

#ifndef MCORN_H
#define MCORN_H

#include "element.h"

class Mcorn : public Element {
private :
	const std::string m_descriptor="microstrip_corner";
	long double m_w;
	std::string m_net1;
	std::string m_net2;
	static const int m_npoint=4;
	long double tab_p[m_npoint][2]={};
public :
	Mcorn(std::string _label,
			std::string _type,
			bool _mirrorx,
			short _r,
			short _nport,
			long double _w);
	~Mcorn();
	std::string getDescriptor(void);
	long double getW(void);
	std::string getNet1(void);
	std::string getNet2(void);
	int getNpoint(void);
	long double getP(int _n, axis_t _xy, orientation_t _r=_NOR, origin_t _abs=_REL);
	int setNet1(std::string _net1);
	int setNet2(std::string _net2);
	int setP(void);
};

#endif // MCORN_H
