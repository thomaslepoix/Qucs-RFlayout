/***************************************************************************
                               mvia.h
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

#ifndef MVIA_H
#define MVIA_H

#include "element.h"

class Mvia final : public Element {
private :
	std::string const m_descriptor="microstrip_via";
	long double m_d;
	std::string m_net1;
public :
	Mvia(std::string _label,
			std::string _type,
			bool _mirrorx,
			short _r,
			short _nport,
			long double _d);
	~Mvia();
	std::string getDescriptor(void) override;
	long double getD(void) override;
	std::string getNet1(void) override;
	int setNet1(std::string _net1) override;
};

#endif // MVIA_H
