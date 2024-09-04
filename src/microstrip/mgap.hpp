///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#pragma once

#include "element.hpp"

//******************************************************************************
class Mgap final : public Element {
private :
	static std::string const m_descriptor;
	long double const m_w1;
	long double const m_w2;
	long double const m_s;
	std::string m_net1;
	std::string m_net2;
public :
	Mgap(std::string const _label,
			std::string const _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			std::string const _subst,
			long double const _w1,
			long double const _w2,
			long double const _s);
	~Mgap()=default;
	std::string getDescriptor() const override;
	long double getW1() const override;
	long double getW2() const override;
	long double getS() const override;
	std::string getNet1() const override;
	std::string getNet2() const override;
	void getStep(int const _net, long double& xstep, long double& ystep) const override;
	void getEdge(int const _net, long double& edge, short& dir) const override;
	bool isOemsMeshInterface(int const _port, long double const _w) const override;
	int setNet1(std::string const _net1) override;
	int setNet2(std::string const _net2) override;
};
