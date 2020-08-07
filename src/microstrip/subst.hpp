/***************************************************************************
                               subst.hpp
                             ------------------
    begin                : Thu Oct 25 2018
    copyright            : (C) 2018 by Thomas Lepoix
    email                : thomas.lepoix@protonmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef SUBST_HPP
#define SUBST_HPP

#include <array>

#include "element.hpp"

class Subst final : public Element {
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
	long double m_margin;
	static const int m_npoint=4;
	long double tab_p[m_npoint][2]={};
public :
	std::array<long double, 4> extrem_pos;

	Subst(std::string _label,
			std::string _type,
			bool _mirrorx,
			short _r,
			long double _er,
			long double _h,
			long double _t,
			long double _tand,
			long double _rho,
			long double _d,
			unsigned int _margin_factor);
	Subst(Subst const* _subst);
	~Subst(void)=default;
	std::string getDescriptor(void) override;
	long double getL(void) override;
	long double getW(void) override;
	long double getEr(void) override;
	long double getH(void) override;
	long double getT(void) override;
	long double getTand(void) override;
	long double getRho(void) override;
	long double getD(void) override;
	long double getMargin(void) override;
	int getNpoint(void) override;
	long double getP(int _n, axis_t _xy, orientation_t _r=NOR, origin_t _abs=REL) override;
	int setW(long double _w) override;
	int setL(long double _l) override;
	int setP(void) override;
};

#endif // SUBST_HPP
