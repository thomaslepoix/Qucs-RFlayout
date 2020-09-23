/***************************************************************************
                               pac.hpp
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

#ifndef PAC_HPP
#define PAC_HPP

#include "element.hpp"

//******************************************************************************
class Pac final : public Element {
private :
	static std::string const m_descriptor;
	unsigned long m_n;
	long double m_z;
	long double m_p;
	long double m_f;
	long double m_w;
	long double m_l;
	std::string m_net1;
	std::string m_net2;
	static int constexpr m_npoint=4;
	long double tab_p[m_npoint][2]={};
public :
	bool is_size_set=false;

	Pac(std::string _label,
			std::string _type,
			bool _active,
			bool _mirrorx,
			short _r,
			unsigned long _n,
			long double _z,
			long double _p,
			long double _f);
	~Pac(void)=default;
	std::string getDescriptor(void) override;
	long double getW(void) override;
	long double getL(void) override;
	long double getZ(void) override;
	long double getDbm(void) override;	//m_p
	long double getF(void) override;
	unsigned long getN(void) override;
	std::string getNet1(void) override;
	std::string getNet2(void) override;
	int getNpoint(void) override;
	long double getP(int const _n, axis_t const _xy, orientation_t const _r=NOR, origin_t const _abs=REL, bool const apply_shift=true) override;
	void getEdge(int const _net, long double& edge, short& dir) override;
	int getOemsNcorelines(void) override;
	int getOemsMeshCore(int const _n, OemsLine& line) override;
	int setNet1(std::string const _net1) override;
	int setNet2(std::string const _net2) override;
	int setSubst(std::string const _subst) override;
	int setW(long double const _w) override;
	int setL(long double const _l) override;
	int setR(short const _r) override;
	int setP(void) override;
};

#endif // PAC_HPP
