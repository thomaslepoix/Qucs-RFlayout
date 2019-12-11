/***************************************************************************
                               pac.h
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

#ifndef PAC_H
#define PAC_H

#include "element.h"

class Pac : public Element {
private :
	const std::string m_descriptor="ac_port";
//	long double m_z;
//	long double m_p;
//	long double m_f;
	std::string m_net1;
	std::string m_net2;
public :
	Pac(std::string _label,
			std::string _type,
			bool _mirrorx,
			short _r,
			short _nport);
//			long double _z,
//			long double _p,
//			long double _f);
	~Pac();
	std::string getDescriptor(void);
	std::string getNet1(void);
	std::string getNet2(void);
	int setNet1(std::string _net1);
	int setNet2(std::string _net2);
//	long double getZ(void);
//	long double getDbm(void);	//m_p
//	long double getF(void);
};

#endif // PAC_H
