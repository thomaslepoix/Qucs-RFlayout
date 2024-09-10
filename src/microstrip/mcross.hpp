///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#pragma once

#include <array>
#include <utility>

#include "element.hpp"

//******************************************************************************
class Mcross final : public Element {
private :
	static std::string const m_descriptor;
	long double const m_w1;
	long double const m_w2;
	long double const m_w3;
	long double const m_w4;
	std::string m_net1;
	std::string m_net2;
	std::string m_net3;
	std::string m_net4;
	int m_npoint=6;
	std::array<std::array<long double, 2>, 6> tab_p={};

	// first : element, second : element's port
	std::pair<Element*, int> adjacent1;
	std::pair<Element*, int> adjacent2;
	std::pair<Element*, int> adjacent3;
	std::pair<Element*, int> adjacent4;
public :
	Mcross(std::string _label,
			std::string _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			std::string _subst,
			long double const _w1,
			long double const _w2,
			long double const _w3,
			long double const _w4);
	~Mcross()=default;
	std::string getDescriptor() const override;
	long double getW1() const override;
	long double getW2() const override;
	long double getW3() const override;
	long double getW4() const override;
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
	int setAdjacent(int const _port, Element* adjacent, int const adjacent_port) override;
	int setNet1(std::string const& _net1) override;
	int setNet2(std::string const& _net2) override;
	int setNet3(std::string const& _net3) override;
	int setNet4(std::string const& _net4) override;
	int setP() override;
};
