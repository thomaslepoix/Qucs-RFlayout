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
class Pac final : public Element {
private :
	static std::string const m_descriptor;
	unsigned long const m_n;
	long double const m_z;
	long double const m_p;
	long double const m_f;
	long double m_w;
	long double m_l;
	std::string m_net1;
	std::string m_net2;
	static int constexpr m_npoint=4;
	std::array<std::array<long double, 2>, m_npoint> tab_p={};
public :
	bool is_size_set=false;

	Pac(std::string _label,
			std::string _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			unsigned long const _n,
			long double const _z,
			long double const _p,
			long double const _f);
	~Pac()=default;
	std::string getDescriptor() const override;
	long double getW() const override;
	long double getL() const override;
	long double getZ() const override;
	long double getDbm() const override;	//m_p
	long double getF() const override;
	unsigned long getN() const override;
	std::string getNet1() const override;
	std::string getNet2() const override;
	int getNpoint() const override;
	long double getP(int const _n, axis_t const _xy, orientation_t const _r=NOR, origin_t const _abs=REL, bool const apply_shift=true) const override;
	void getEdge(int const _net, long double& edge, short& dir) const override;
	int getOemsNcorelines() const override;
	int getOemsMeshCore(int const _n, OemsLine& line) const override;
	int setNet1(std::string const& _net1) override;
	int setNet2(std::string const& _net2) override;
	int setSubst(std::string const& _subst) override;
	int setW(long double const _w) override;
	int setL(long double const _l) override;
	int setR(short const _r) override;
	int setP() override;
};
