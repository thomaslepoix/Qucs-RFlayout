/***************************************************************************
                               mgap.hpp
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

#ifndef MGAP_HPP
#define MGAP_HPP

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
	Mgap(std::string _label,
			std::string _type,
			bool _active,
			bool _mirrorx,
			short _r,
			std::string _subst,
			long double _w1,
			long double _w2,
			long double _s);
	~Mgap(void)=default;
	std::string getDescriptor(void) const override;
	long double getW1(void) const override;
	long double getW2(void) const override;
	long double getS(void) const override;
	std::string getNet1(void) const override;
	std::string getNet2(void) const override;
	void getStep(int const _net, long double& xstep, long double& ystep) const override;
	void getEdge(int const _net, long double& edge, short& dir) const override;
	bool isOemsMeshInterface(int const _port, long double const _w) const override;
	int setNet1(std::string const _net1) override;
	int setNet2(std::string const _net2) override;
};

#endif // MGAP_HPP
