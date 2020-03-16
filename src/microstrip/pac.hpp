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

class Pac final : public Element {
private :
	std::string const m_descriptor="ac_port";
	short m_n;
	long double m_z;
	long double m_p;
	long double m_f;
	std::string m_net1;
	std::string m_net2;
public :
	Pac(std::string _label,
			std::string _type,
			bool _mirrorx,
			short _r,
			short _n,
			long double _z,
			long double _p,
			long double _f);
	~Pac();
	std::string getDescriptor(void) override;
	std::string getNet1(void) override;
	std::string getNet2(void) override;
	int setNet1(std::string _net1) override;
	int setNet2(std::string _net2) override;
	long double getZ(void) override;
	long double getDbm(void) override;	//m_p
	long double getF(void) override;
	short getN(void) override;
};

#endif // PAC_HPP
