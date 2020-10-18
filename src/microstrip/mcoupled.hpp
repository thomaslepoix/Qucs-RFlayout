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

//******************************************************************************
class Mcoupled final : public Element {
private :
	static std::string const m_descriptor;
	long double const m_w;
	long double const m_l;
	long double const m_s;
	std::string m_net1;
	std::string m_net2;
	std::string m_net3;
	std::string m_net4;
	static int constexpr m_npoint=8;
	long double tab_p[m_npoint][2]={};

	// first : element, second : element's port
	std::pair<std::shared_ptr<Element>, int> adjacent1;
	std::pair<std::shared_ptr<Element>, int> adjacent2;
	std::pair<std::shared_ptr<Element>, int> adjacent3;
	std::pair<std::shared_ptr<Element>, int> adjacent4;
public :
	Mcoupled(std::string const _label,
			std::string const _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			std::string const _subst,
			long double const _w,
			long double const _l,
			long double const _s);
	~Mcoupled()=default;
	std::string getDescriptor() const override;
	long double getW() const override;
	long double getL() const override;
	long double getS() const override;
	std::string getNet1() const override;
	std::string getNet2() const override;
	std::string getNet3() const override;
	std::string getNet4() const override;
	int getNpoint() const override;
	long double getP(int const _n, axis_t const _xy, orientation_t const _r=NOR, origin_t const _abs=REL, bool const apply_shift=true) const override;
	void getStep(int const _net, long double& xstep, long double& ystep) const override;
	void getEdge(int const _net, long double& edge, short& dir) const override;
	int getOemsNcorelines() const override;
	int getOemsMeshCore(int const _n, OemsLine& line) const override;
	int getOemsMeshInterface(int const _net, OemsLine& line) const override;
	bool isOemsMeshInterface(int const _port, long double const _w) const override;
	int setAdjacent(int const _port, std::shared_ptr<Element> const& element, int const adjacent_port) override;
	int setNet1(std::string const _net1) override;
	int setNet2(std::string const _net2) override;
	int setNet3(std::string const _net3) override;
	int setNet4(std::string const _net4) override;
	int setP() override;
};

#endif // MCOUPLED_HPP
