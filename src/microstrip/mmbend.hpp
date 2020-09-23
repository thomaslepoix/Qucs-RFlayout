/***************************************************************************
                               mmbend.hpp
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

#ifndef MMBEND_HPP
#define MMBEND_HPP

#include "element.hpp"

//******************************************************************************
class Mmbend final : public Element {
private :
	static std::string const m_descriptor;
	long double const m_w;
	std::string m_net1;
	std::string m_net2;
	static int constexpr m_npoint=3;
	long double tab_p[m_npoint][2]={};
public :
	Mmbend(std::string const _label,
			std::string const _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			std::string const _subst,
			long double const _w);
	~Mmbend(void)=default;
	std::string getDescriptor(void) const override;
	long double getW(void) const override;
	std::string getNet1(void) const override;
	std::string getNet2(void) const override;
	int getNpoint(void) const override;
	long double getP(int const _n, axis_t const _xy, orientation_t const _r=NOR, origin_t const _abs=REL, bool const apply_shift=true) const override;
	void getStep(int const _net, long double& xstep, long double& ystep) const override;
	void getEdge(int const _net, long double& edge, short& dir) const override;
	int getOemsNcorelines(void) const override;
	int getOemsMeshCore(int const _n, OemsLine& line) const override;
	bool isOemsMeshInterface(int const _port, long double const _w) const override;
	int setNet1(std::string const _net1) override;
	int setNet2(std::string const _net2) override;
	int setP(void) override;
};

#endif // MMBEND_HPP
