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

//******************************************************************************
class Subst final : public Element {
private :
	static std::string const m_descriptor;
	long double m_w;
	long double m_l;
	long double const m_er;
	long double const m_h;
	long double const m_t;
	long double const m_tand;
	long double const m_rho;
	long double const m_d;
	long double const m_margin;
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
	std::string getDescriptor(void) const override;
	long double getL(void) const override;
	long double getW(void) const override;
	long double getEr(void) const override;
	long double getH(void) const override;
	long double getT(void) const override;
	long double getTand(void) const override;
	long double getRho(void) const override;
	long double getD(void) const override;
	long double getMargin(void) const override;
	int getNpoint(void) const override;
	long double getP(int const _n, axis_t const _xy, orientation_t const _r=NOR, origin_t const _abs=REL, bool const apply_shift=true) const override;
	int setW(long double const _w) override;
	int setL(long double const _l) override;
	int setP(void) override;
};

#endif // SUBST_HPP
