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
	std::array<std::array<long double, 2>, m_npoint> tab_p={};
public :
	Mrstub(std::string _label,
			std::string _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			std::string _subst,
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
	int setNet1(std::string const& _net1) override;
	int setP() override;
};
