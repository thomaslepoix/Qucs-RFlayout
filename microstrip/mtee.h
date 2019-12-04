/***************************************************************************
                               mtee.h
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

#ifndef MTEE_H
#define MTEE_H

#include "element.h"

class Mtee : public Element {
private :
	const std::string m_descriptor="microstrip_tee";
	long double m_w1;
	long double m_w2;
	long double m_w3;
	std::string m_net1;
	std::string m_net2;
	std::string m_net3;
	static const int m_npoint=6;
	long double tab_p[m_npoint][2]={};
public :
	Mtee(std::string _label,
			std::string _type,
			bool _mirrorx,
			short _r,
			short _nport,
			long double _w1,
			long double _w2,
			long double _w3);
	~Mtee();
	std::string getDescriptor(void);
	long double getW1(void);
	long double getW2(void);
	long double getW3(void);
	std::string getNet1(void);
	std::string getNet2(void);
	std::string getNet3(void);
	int getNpoint(void);
	long double getP(int _n, axis_t _xy, orientation_t _r=NOR, origin_t _abs=REL);
	int setNet1(std::string _net1);
	int setNet2(std::string _net2);
	int setNet3(std::string _net3);
	int setP(void);
};

#endif // MTEE_H
