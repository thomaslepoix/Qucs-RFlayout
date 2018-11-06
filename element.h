/***************************************************************************
                               element.h
                             ------------------
    begin                : Thu Oct 25 2018
    copyright            : (C) 2018 by Thomas Lepoix
    email                : thomas.lepoix@gmail.com
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
#include <string>

class Element {
private:
	std::string m_label;
	std::string m_type;
	short m_mirrorx;
	short m_r;
	short m_nport;
	long double m_x=0.0/0.0;
	long double m_y=0.0/0.0;
public:
	Element(std::string _label,
			std::string _type,
			short _mirrorx,
			short _r,
			short _nport);
	~Element();
	Element* prev=NULL;
	std::string getLabel(void);
	std::string getType(void);
	short getMirrorx(void);
	short getR(void);
	short getNport(void);
	long double getX(void);
	long double getY(void);
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
	int setX(long double _x);
	int setY(long double _y);
	virtual int setNet1(std::string _net1)=0;
	virtual int setNet2(std::string _net2)=0;
	virtual int setNet3(std::string _net3)=0;
	virtual int setNet4(std::string _net4)=0;
};

#endif
