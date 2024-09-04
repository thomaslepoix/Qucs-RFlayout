///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#pragma once

#include "element.hpp"

//******************************************************************************
class Mopen final : public Element {
private :
	static std::string const m_descriptor;
	long double const m_w;
	std::string m_net1;

	// first : element, second : element's port
	std::pair<std::shared_ptr<Element>, int> adjacent1;
public :
	Mopen(std::string const _label,
			std::string const _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			std::string const _subst,
			long double const _w);
	~Mopen()=default;
	std::string getDescriptor() const override;
	long double getW() const override;
	std::string getNet1() const override;
	void getEdge(int const _net, long double& edge, short& dir) const override;
	bool isOemsMeshInterface(int const _port, long double const _w) const override;
	int setAdjacent(int const _port, std::shared_ptr<Element> const& element, int const adjacent_port) override;
	int setNet1(std::string const _net1) override;
};
