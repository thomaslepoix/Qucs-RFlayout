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
	long double m_w;
	std::string m_net1;
	std::string m_net2;
	static int constexpr m_npoint=3;
	long double tab_p[m_npoint][2]={};
public :
	Mmbend(std::string _label,
			std::string _type,
			bool _active,
			bool _mirrorx,
			short _r,
			std::string _subst,
			long double _w);
	~Mmbend(void)=default;
	std::string getDescriptor(void) override;
	long double getW(void) override;
	std::string getNet1(void) override;
	std::string getNet2(void) override;
	int getNpoint(void) override;
	long double getP(int const _n, axis_t const _xy, orientation_t const _r=NOR, origin_t const _abs=REL, bool const apply_shift=true) override;
	void getStep(int const _net, long double& xstep, long double& ystep) override;
	void getEdge(int const _net, long double& edge, short& dir) override;
	int getOemsNcorelines(void) override;
	int getOemsMeshCore(int const _n, OemsLine& line) override;
	bool isOemsMeshInterface(int const _port, long double const _w) override;
	int setNet1(std::string const _net1) override;
	int setNet2(std::string const _net2) override;
	int setP(void) override;
};

#endif // MMBEND_HPP
