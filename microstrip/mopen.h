/***************************************************************************
                               mopen.h
                             ------------------
    begin                : Thu Oct 25 2018
    copyright            : (C) 2018 by Thomas Lepoix
    email                : thomas.lepoix@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MOPEN_H
#define MOPEN_H

#include "element.h"

class Mopen : public Element {
private :
	const std::string m_descriptor="microstrip_open";
	long double m_w;
	std::string m_net1;
public :
	Mopen(std::string _label,
			std::string _type,
			bool _mirrorx,
			short _r,
			short _nport,
			long double _w);
	~Mopen();
	std::string getDescriptor(void);
	long double getW(void);
	std::string getNet1(void);
	int setNet1(std::string _net1);
////////////////////////////////////////////////////////////////////////////////
	long double getW1(void);
	long double getW2(void);
	long double getW3(void);
	long double getW4(void);
	long double getL(void);
	long double getD(void);
	long double getS(void);
	long double getRi(void);
	long double getRo(void);
	short getAlpha(void);
	std::string getNet2(void);
	std::string getNet3(void);
	std::string getNet4(void);
	int getNpoint(void);
	long double getP(int _n, bool _xy, bool _r=_NOR, bool _abs=_REL);
	int setNet2(std::string _net2);
	int setNet3(std::string _net3);
	int setNet4(std::string _net4);
	int setP(void);
};

#endif // MOPEN_H
