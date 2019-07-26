/***************************************************************************
                               mcross.h
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

#ifndef MCROSS_H
#define MCROSS_H

#include "element.h"

class Mcross : public Element {
private :
	const std::string m_descriptor="microstrip_cross";
	long double m_w1;
	long double m_w2;
	long double m_w3;
	long double m_w4;
	std::string m_net1;
	std::string m_net2;
	std::string m_net3;
	std::string m_net4;
	int m_npoint=6;
	long double tab_p[6][2]={};
public :
	Mcross(std::string _label,
			std::string _type,
			bool _mirrorx,
			short _r,
			short _nport,
			long double _w1,
			long double _w2,
			long double _w3,
			long double _w4);
	~Mcross();
	std::string getDescriptor(void);
	long double getW1(void);
	long double getW2(void);
	long double getW3(void);
	long double getW4(void);
	std::string getNet1(void);
	std::string getNet2(void);
	std::string getNet3(void);
	std::string getNet4(void);
	int getNpoint(void);
	long double getP(int _n, bool _xy, bool _r=_NOR, bool _abs=_REL);
	int setNet1(std::string _net1);
	int setNet2(std::string _net2);
	int setNet3(std::string _net3);
	int setNet4(std::string _net4);
	int setP(void);
////////////////////////////////////////////////////////////////////////////////
	long double getW(void);
	long double getL(void);
	long double getD(void);
	long double getS(void);
	long double getRi(void);
	long double getRo(void);
	short getAlpha(void);
};

#endif // MCROSS_H
