/***************************************************************************
                               mstep.hpp
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

#ifndef MSTEP_HPP
#define MSTEP_HPP

#include "element.hpp"

//******************************************************************************
class Mstep final : public Element {
private :
	static std::string const m_descriptor;
	long double const m_w1;
	long double const m_w2;
	std::string m_net1;
	std::string m_net2;

	// first : element, second : element's port
	std::pair<std::shared_ptr<Element>, int> adjacent1;
	std::pair<std::shared_ptr<Element>, int> adjacent2;
public :
	Mstep(std::string _label,
			std::string _type,
			bool _active,
			bool _mirrorx,
			short _r,
			std::string _subst,
			long double _w1,
			long double _w2);
	~Mstep(void)=default;
	std::string getDescriptor(void) const override;
	long double getW1(void) const override;
	long double getW2(void) const override;
	std::string getNet1(void) const override;
	std::string getNet2(void) const override;
	void getEdge(int const _net, long double& edge, short& dir) const override;
	int getOemsNcorelines(void) const override;
	int getOemsMeshCore(int const _n, OemsLine& line) const override;
	int setAdjacent(int const _port, std::shared_ptr<Element> const& element, int const adjacent_port) override;
	int setNet1(std::string const _net1) override;
	int setNet2(std::string const _net2) override;
};

#endif // MSTEP_HPP
