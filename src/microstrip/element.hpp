/***************************************************************************
                               element.hpp
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

#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#define _USE_MATH_DEFINES

enum axis_t {X, Y};				// x axis / y axis
enum orientation_t {NOR, R};			// no rotation / rotation
enum origin_t {REL, ABS};				// relative / absolute
enum {XMIN, XMAX, YMIN, YMAX};		// extrem_pos index

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
	virtual ~Element();
	std::shared_ptr<Element> prev=nullptr;
	std::string getLabel(void);
	std::string getType(void);
	bool getMirrorx(void);
	short getR(void);
	short getNport(void);
	long double getX(void);
	long double getY(void);
	int setX(long double _x);
	int setY(long double _y);

	//default functions, to override
	virtual std::string getDescriptor(void);
	virtual long double getW(void);
	virtual long double getW1(void);
	virtual long double getW2(void);
	virtual long double getW3(void);
	virtual long double getW4(void);
	virtual long double getL(void);
	virtual long double getD(void);
	virtual long double getS(void);
	virtual long double getRi(void);
	virtual long double getRo(void);
	virtual short getAlpha(void);
	virtual std::string getNet1(void);
	virtual std::string getNet2(void);
	virtual std::string getNet3(void);
	virtual std::string getNet4(void);
	virtual int getNpoint(void);
	virtual long double getP(int _n, axis_t _xy, orientation_t _r, origin_t _abs);
	virtual void getStep(int const _net, long double& xstep, long double& ystep);
	virtual int setNet1(std::string _net1);
	virtual int setNet2(std::string _net2);
	virtual int setNet3(std::string _net3);
	virtual int setNet4(std::string _net4);
	virtual int setP(void);
};

#endif // ELEMENT_HPP
