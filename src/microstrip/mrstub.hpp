/***************************************************************************
                               mrstub.hpp
                             ------------------
    begin                : Thu Oct 25 2018
    copyright            : (C) 2018 by Thomas Lepoix
    email                : thomas.lepoix@protonmail.ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#pragma once

#define _USE_MATH_DEFINES

#include "element.hpp"

//******************************************************************************
class Mrstub final : public Element {
private :
	static std::string const m_descriptor;
	long double const m_w;
	long double const m_l;
	long double const m_ri;
	long double const m_ro;
	long double const m_alpha;
	std::string m_net1;
	static int constexpr m_npoint=53;
	long double tab_p[m_npoint][2]={};
public :
	Mrstub(std::string const _label,
			std::string const _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			std::string const _subst,
			long double const _ri,
			long double const _ro,
			long double const _alpha);
	~Mrstub()=default;
	std::string getDescriptor() const override;
	long double getW() const override;
	long double getL() const override;
	long double getRi() const override;
	long double getRo() const override;
	long double getAlpha() const override;
	std::string getNet1() const override;
	int getNpoint() const override;
	long double getP(int const _n, axis_t const _xy, orientation_t const _r=NOR, origin_t const _abs=REL, bool const apply_shift=true) const override;
	void getEdge(int const _net, long double& edge, short& dir) const override;
	int getOemsNcorelines() const override;
	int getOemsMeshCore(int const _n, OemsLine& line) const override;
	bool isOemsMeshInterface(int const _port, long double const _w) const override;
	int setNet1(std::string const _net1) override;
	int setP() override;
};
