/***************************************************************************
                               subst.h
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

#ifndef SUBST_H
#define SUBST_H

#include "element.h"

class Subst : public Element {
private :
	const std::string m_descriptor="substrat";
	long double m_w;
	long double m_l;
	long double m_er;
	long double m_h;
	long double m_t;
	long double m_tand;
	long double m_rho;
	long double m_d;
	static const int m_npoint=4;
	long double tab_p[m_npoint][2]={};
public :
	Subst(std::string _label,
			std::string _type,
			bool _mirrorx,
			short _r,
			long double _er,
			long double _h,
			long double _t,
			long double _tand,
			long double _rho,
			long double _d);
	~Subst();
	std::string getDescriptor(void);
	long double getL(void);
	long double getW(void);
	long double getEr(void);
	long double getH(void);
	long double getT(void);
	long double getTand(void);
	long double getRho(void);
	long double getD(void);
	int getNpoint(void);
	long double getP(int _n, bool _xy, bool _r=_NOR, bool _abs=_REL);
	int setW(long double _w);
	int setL(long double _l);
	int setP(void);
////////////////////////////////////////////////////////////////////////////////
	long double getW1(void);
	long double getW2(void);
	long double getW3(void);
	long double getW4(void);
	long double getS(void);
	long double getRi(void);
	long double getRo(void);
	long double getZ(void);
	long double getDbm(void);
	long double getF(void);
	short getN(void);
	short getAlpha(void);
	std::string getNet1(void);
	std::string getNet2(void);
	std::string getNet3(void);
	std::string getNet4(void);
	int setNet1(std::string _net1);
	int setNet2(std::string _net2);
	int setNet3(std::string _net3);
	int setNet4(std::string _net4);
};

#endif // SUBST_H
