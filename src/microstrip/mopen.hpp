/***************************************************************************
                               mopen.hpp
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

#ifndef MOPEN_HPP
#define MOPEN_HPP

#include "element.hpp"

//******************************************************************************
class Mopen final : public Element {
private :
	static std::string const m_descriptor;
	long double m_w;
	std::string m_net1;

	// first : element, second : element's port
	std::pair<std::shared_ptr<Element>, int> adjacent1;
public :
	Mopen(std::string _label,
			std::string _type,
			bool _active,
			bool _mirrorx,
			short _r,
			std::string _subst,
			long double _w);
	~Mopen(void)=default;
	std::string getDescriptor(void) override;
	long double getW(void) override;
	std::string getNet1(void) override;
	void getEdge(int const _net, long double& edge, short& dir) override;
	bool isOemsMeshInterface(int const _port, long double const _w) override;
	int setAdjacent(int const _port, std::shared_ptr<Element> const& element, int const adjacent_port) override;
	int setNet1(std::string const _net1) override;
};

#endif // MOPEN_HPP
