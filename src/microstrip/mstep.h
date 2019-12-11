/***************************************************************************
                               mstep.h
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

#ifndef MSTEP_H
#define MSTEP_H

#include "element.h"

class Mstep : public Element {
private :
	const std::string m_descriptor="microstrip_step";
	long double m_w1;
	long double m_w2;
	std::string m_net1;
	std::string m_net2;
public :
	Mstep(std::string _label,
			std::string _type,
			bool _mirrorx,
			short _r,
			short _nport,
			long double _w1,
			long double _w2);
	~Mstep();
	std::string getDescriptor(void);
	long double getW1(void);
	long double getW2(void);
	std::string getNet1(void);
	std::string getNet2(void);
	int setNet1(std::string _net1);
	int setNet2(std::string _net2);
};

#endif // MSTEP_H
