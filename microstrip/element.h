/***************************************************************************
                               element.h
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

#ifndef ELEMENT_H
#define ELEMENT_H

#define _USE_MATH_DEFINES

//getP() defines
#define EL_X    0
#define EL_Y	1
#define _NOR	0
#define _R		1
#define _REL	0
#define _ABS	1
//extrem_pos defines
#define _XMIN	0
#define _XMAX	1
#define _YMIN	2
#define _YMAX	3

#include <string>
#include <cmath>
#include <memory>

class Element {
protected:
	std::string m_label;
	std::string m_type;
	bool m_mirrorx;
	short m_r;
	short m_nport;
    long double m_x=NAN;
    long double m_y=NAN;
	long double rotateX(long double _x, long double _y);
	long double rotateY(long double _x, long double _y);
public:
	Element(std::string _label,
			std::string _type,
			bool _mirrorx,
			short _r,
			short _nport);
	~Element();
    std::shared_ptr<Element> prev=nullptr;
	std::string getLabel(void);
	std::string getType(void);
	bool getMirrorx(void);
	short getR(void);
	short getNport(void);
	long double getX(void);
	long double getY(void);
	virtual std::string getDescriptor(void)=0;
	virtual long double getW(void)=0;
	virtual long double getW1(void)=0;
	virtual long double getW2(void)=0;
	virtual long double getW3(void)=0;
	virtual long double getW4(void)=0;
	virtual long double getL(void)=0;
	virtual long double getD(void)=0;
	virtual long double getS(void)=0;
	virtual long double getRi(void)=0;
	virtual long double getRo(void)=0;
	virtual short getAlpha(void)=0;
	virtual std::string getNet1(void)=0;
	virtual std::string getNet2(void)=0;
	virtual std::string getNet3(void)=0;
	virtual std::string getNet4(void)=0;
	virtual int getNpoint(void)=0;
	virtual long double getP(int _n, bool _xy, bool _r, bool _abs)=0;
	int setX(long double _x);
	int setY(long double _y);
	virtual int setNet1(std::string _net1)=0;
	virtual int setNet2(std::string _net2)=0;
	virtual int setNet3(std::string _net3)=0;
	virtual int setNet4(std::string _net4)=0;
	virtual int setP(void)=0;
};

#endif // ELEMENT_H
