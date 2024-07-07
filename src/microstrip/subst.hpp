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
 *   the Free Software Foundation; either version 3 of the License, or     *
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
	std::array<long double, 4> substrate_boundary;

	Subst(std::string const _label,
			std::string const _type,
			bool const _mirrorx,
			short const _r,
			long double const _er,
			long double const _h,
			long double const _t,
			long double const _tand,
			long double const _rho,
			long double const _d,
			unsigned int const _margin_factor);
	Subst(Subst const& _subst);
	~Subst()=default;
	std::string getDescriptor() const override;
	long double getL() const override;
	long double getW() const override;
	long double getEr() const override;
	long double getH() const override;
	long double getT() const override;
	long double getTand() const override;
	long double getRho() const override;
	long double getD() const override;
	long double getMargin() const override;
	int getNpoint() const override;
	long double getP(int const _n, axis_t const _xy, orientation_t const _r=NOR, origin_t const _abs=REL, bool const apply_shift=true) const override;
	int setW(long double const _w) override;
	int setL(long double const _l) override;
	int setP() override;
};

#endif // SUBST_HPP
