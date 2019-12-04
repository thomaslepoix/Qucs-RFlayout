/***************************************************************************
                               mcoupled.h
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

#ifndef MCOUPLED_H
#define MCOUPLED_H

#include "element.h"

class Mcoupled : public Element {
private :
	const std::string m_descriptor="microstrip_coupled_lines";
	long double m_w;
	long double m_l;
	long double m_s;
	std::string m_net1;
	std::string m_net2;
	std::string m_net3;
	std::string m_net4;
	static const int m_npoint=8;
	long double tab_p[m_npoint][2]={};
public :
	Mcoupled(std::string _label,
			std::string _type,
			bool _mirrorx,
			short _r,
			short _nport,
			long double _w,
			long double _l,
			long double _s);
	~Mcoupled();
	std::string getDescriptor(void);
	long double getW(void);
	long double getL(void);
	long double getS(void);
	std::string getNet1(void);
	std::string getNet2(void);
	std::string getNet3(void);
	std::string getNet4(void);
	int getNpoint(void);
	long double getP(int _n, axis_t _xy, orientation_t _r=_NOR, origin_t _abs=_REL);
	int setNet1(std::string _net1);
	int setNet2(std::string _net2);
	int setNet3(std::string _net3);
	int setNet4(std::string _net4);
	int setP(void);
};

#endif // MCOUPLED_H
