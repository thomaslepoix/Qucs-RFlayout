/***************************************************************************
                               mopen.h
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

#ifndef MOPEN_H
#define MOPEN_H

#include "element.h"

class Mopen : public Element {
private :
	const std::string m_descriptor="microstrip_open";
	long double m_w;
	std::string m_net1;
public :
	Mopen(std::string _label,
			std::string _type,
			bool _mirrorx,
			short _r,
			short _nport,
			long double _w);
	~Mopen();
	std::string getDescriptor(void);
	long double getW(void);
	std::string getNet1(void);
	int setNet1(std::string _net1);
};

#endif // MOPEN_H
