/***************************************************************************
                               mlin.h
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

#ifndef MLIN_H
#define MLIN_H

#include "element.h"

class Mlin : public Element {
private :
	const std::string m_descriptor="microstrip_line";
	long double m_w;
	long double m_l;
	std::string m_net1;
	std::string m_net2;
	static const int m_npoint=4;
	long double tab_p[m_npoint][2]={};
public :
	Mlin(std::string _label,
			std::string _type,
			bool _mirrorx,
			short _r,
			std::string _subst,
			long double _w,
			long double _l);
	~Mlin();
	std::string getDescriptor(void);
	long double getW(void);
	long double getL(void);
	std::string getNet1(void);
	std::string getNet2(void);
	int getNpoint(void);
	long double getP(int _n, bool _xy, bool _r=_NOR, bool _abs=_REL);
	int setNet1(std::string _net1);
	int setNet2(std::string _net2);
	int setP(void);
////////////////////////////////////////////////////////////////////////////////
	long double getW1(void);
	long double getW2(void);
	long double getW3(void);
	long double getW4(void);
	long double getD(void);
	long double getS(void);
	long double getRi(void);
	long double getRo(void);
	long double getZ(void);
	long double getDbm(void);
	long double getF(void);
	long double getEr(void);
	long double getH(void);
	long double getT(void);
	long double getTand(void);
	long double getRho(void);
	short getN(void);
	short getAlpha(void);
	std::string getNet3(void);
	std::string getNet4(void);
	int setW(long double _w);
	int setL(long double _l);
	int setNet3(std::string _net3);
	int setNet4(std::string _net4);
};

#endif // MLIN_H
