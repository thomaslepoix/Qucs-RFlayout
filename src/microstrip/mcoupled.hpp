/***************************************************************************
                               mcoupled.hpp
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

#ifndef MCOUPLED_HPP
#define MCOUPLED_HPP

#include "element.hpp"

class Mcoupled final : public Element {
private :
	std::string const m_descriptor="microstrip_coupled_lines";
	long double m_w;
	long double m_l;
	long double m_s;
	std::string m_net1;
	std::string m_net2;
	std::string m_net3;
	std::string m_net4;
	static int const m_npoint=8;
	long double tab_p[m_npoint][2]={};
public :
	Mcoupled(std::string _label,
			std::string _type,
			bool _active,
			bool _mirrorx,
			short _r,
			std::string _subst,
			long double _w,
			long double _l,
			long double _s);
	~Mcoupled();
	std::string getDescriptor(void) override;
	long double getW(void) override;
	long double getL(void) override;
	long double getS(void) override;
	std::string getNet1(void) override;
	std::string getNet2(void) override;
	std::string getNet3(void) override;
	std::string getNet4(void) override;
	int getNpoint(void) override;
	long double getP(int _n, axis_t _xy, orientation_t _r=NOR, origin_t _abs=REL) override;
	void getStep(int const _net, long double& xstep, long double& ystep) override;
	void getEdge(int const _net, long double& edge, short& dir) override;
	int setNet1(std::string _net1) override;
	int setNet2(std::string _net2) override;
	int setNet3(std::string _net3) override;
	int setNet4(std::string _net4) override;
	int setP(void) override;
};

#endif // MCOUPLED_HPP
