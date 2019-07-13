/***************************************************************************
                               pac.h
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

#ifndef PAC_H
#define PAC_H

#include "element.h"

class Pac : public Element {
private :
	const std::string m_descriptor="ac_port";
	short m_n;
	long double m_z;
	long double m_p;
	long double m_f;
	std::string m_net1;
	std::string m_net2;
public :
	Pac(std::string _label,
			std::string _type,
			bool _mirrorx,
			short _r,
			short _n,
			long double _z,
			long double _p,
			long double _f);
	~Pac();
	std::string getDescriptor(void);
	short getN(void);
	long double getZ(void);
	long double getDbm(void);
	long double getF(void);
	std::string getNet1(void);
	std::string getNet2(void);
	int setNet1(std::string _net1);
	int setNet2(std::string _net2);
////////////////////////////////////////////////////////////////////////////////
	long double getW(void);
	long double getW1(void);
	long double getW2(void);
	long double getW3(void);
	long double getW4(void);
	long double getL(void);
	long double getD(void);
	long double getS(void);
	long double getRi(void);
	long double getRo(void);
	long double getEr(void);
	long double getH(void);
	long double getT(void);
	long double getTand(void);
	long double getRho(void);
	short getAlpha(void);
	std::string getNet3(void);
	std::string getNet4(void);
	int getNpoint(void);
	long double getP(int _n, bool _xy, bool _r=_NOR, bool _abs=_REL);
	int setW(long double _w);
	int setL(long double _l);
	int setNet3(std::string _net3);
	int setNet4(std::string _net4);
	int setP(void);
};

#endif // PAC_H
