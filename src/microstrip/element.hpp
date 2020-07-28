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

#include <cmath>
#include <memory>
#include <string>

#include "oemsline.hpp"

enum axis_t {X, Y};            // x axis / y axis
enum orientation_t {NOR, R};   // no rotation / rotation
enum origin_t {REL, ABS};      // relative / absolute
enum {XMIN, XMAX, YMIN, YMAX}; // extrem_pos index

class Element {
protected:
	std::string m_label;
	std::string m_type;
	bool m_active;
	bool m_mirrorx;
	short m_r;
	short m_nport;
	std::string m_subst;
    long double m_x=NAN;
    long double m_y=NAN;
	long double m_shift_x=0.0;
	long double m_shift_y=0.0;
	long double rotateX(long double _x, long double _y);
	long double rotateY(long double _x, long double _y);
public:
	Element(std::string _label,
			std::string _type,
			bool _active,
			bool _mirrorx,
			short _r,
			short _nport,
			std::string _subst);
	virtual ~Element();
	std::shared_ptr<Element> prev=nullptr;
	std::string getLabel(void);
	std::string getType(void);
	bool getActive(void);
	bool getMirrorx(void);
	short getR(void);
	short getNport(void);
	std::string getSubst(void);
	long double getX(void);
	long double getY(void);
	int setX(long double _x);
	int setY(long double _y);
	int setShiftX(long double _shift_x);
	int setShiftY(long double _shift_y);

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
	virtual long double getZ(void);
	virtual long double getDbm(void);
	virtual long double getF(void);
	virtual long double getFstart(void);
	virtual long double getFstop(void);
	virtual long double getEr(void);
	virtual long double getH(void);
	virtual long double getT(void);
	virtual long double getTand(void);
	virtual long double getRho(void);
	virtual long double getMargin(void);
	virtual unsigned long getN(void);
	virtual short getAlpha(void);
	virtual std::string getSimtype(void);
	virtual std::string getNet1(void);
	virtual std::string getNet2(void);
	virtual std::string getNet3(void);
	virtual std::string getNet4(void);
	virtual int getNpoint(void);
	virtual long double getP(int _n, axis_t _xy, orientation_t _r, origin_t _abs);
	virtual void getStep(int const _net, long double& xstep, long double& ystep);
	virtual void getEdge(int const _net, long double& edge, short& dir);
	virtual int getOemsNcorelines(void);
	virtual int getOemsMeshCore(int const _n, OemsLine& line);
	virtual int getOemsMeshInterface(int const _net, OemsLine& line);
	virtual bool isOemsMeshInterface(int const _port, long double const _w);
	virtual int setAdjacent(int const _port, std::shared_ptr<Element> const& element, int const adjacent_port);

	virtual int setW(long double _w);
	virtual int setL(long double _l);
	virtual int setR(short _r);
	virtual int setSubst(std::string _subst);
	virtual int setNet1(std::string _net1);
	virtual int setNet2(std::string _net2);
	virtual int setNet3(std::string _net3);
	virtual int setNet4(std::string _net4);
	virtual int setP(void);
};

#endif // ELEMENT_HPP
