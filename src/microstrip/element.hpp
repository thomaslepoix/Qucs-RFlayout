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

#include <memory>
#include <string>

#include "oemsline.hpp"

//******************************************************************************
enum axis_t { X, Y };            // x axis / y axis
enum orientation_t { NOR, R };   // no rotation / rotation
enum origin_t { REL, ABS };      // relative / absolute
enum { XMIN, XMAX, YMIN, YMAX }; // extrem_pos index

//******************************************************************************
class Element {
protected:
	std::string const m_label;
	std::string const m_type;
	bool const m_active;
	bool const m_mirrorx;
	short m_r;
	short const m_nport;
	std::string m_subst;
	long double m_x;
	long double m_y;
	long double m_shift_x;
	long double m_shift_y;
	long double rotateX(long double const _x, long double const _y) const;
	long double rotateY(long double const _x, long double const _y) const;
public:
	Element(std::string _label,
			std::string _type,
			bool _active,
			bool _mirrorx,
			short _r,
			short _nport,
			std::string _subst);
	virtual ~Element(void)=default;
	std::shared_ptr<Element> prev;
	std::string getLabel(void) const;
	std::string getType(void) const;
	bool getActive(void) const;
	bool getMirrorx(void) const;
	short getR(void) const;
	short getNport(void) const;
	std::string getSubst(void) const;
	long double getX(bool const apply_shift=true) const;
	long double getY(bool const apply_shift=true) const;
	int setX(long double const _x);
	int setY(long double const _y);
	int setShiftX(long double const _shift_x);
	int setShiftY(long double const _shift_y);

	//default functions, to override
	virtual std::string getDescriptor(void) const;
	virtual long double getW(void) const;
	virtual long double getW1(void) const;
	virtual long double getW2(void) const;
	virtual long double getW3(void) const;
	virtual long double getW4(void) const;
	virtual long double getL(void) const;
	virtual long double getD(void) const;
	virtual long double getS(void) const;
	virtual long double getRi(void) const;
	virtual long double getRo(void) const;
	virtual long double getZ(void) const;
	virtual long double getDbm(void) const;
	virtual long double getF(void) const;
	virtual long double getFstart(void) const;
	virtual long double getFstop(void) const;
	virtual long double getEr(void) const;
	virtual long double getH(void) const;
	virtual long double getT(void) const;
	virtual long double getTand(void) const;
	virtual long double getRho(void) const;
	virtual long double getMargin(void) const;
	virtual long double getAlpha(void) const;
	virtual unsigned long getN(void) const;
	virtual std::string getSimtype(void) const;
	virtual std::string getNet1(void) const;
	virtual std::string getNet2(void) const;
	virtual std::string getNet3(void) const;
	virtual std::string getNet4(void) const;
	virtual int getNpoint(void) const;
	virtual long double getP(int const _n, axis_t const _xy, orientation_t const _r, origin_t const _abs, bool const apply_shift=true) const;
	virtual void getStep(int const _net, long double& xstep, long double& ystep) const;
	virtual void getEdge(int const _net, long double& edge, short& dir) const;
	virtual int getOemsNcorelines(void) const;
	virtual int getOemsMeshCore(int const _n, OemsLine& line) const;
	virtual int getOemsMeshInterface(int const _net, OemsLine& line) const;
	virtual bool isOemsMeshInterface(int const _port, long double const _w) const;
	virtual int setAdjacent(int const _port, std::shared_ptr<Element> const& element, int const adjacent_port);

	virtual int setW(long double const _w);
	virtual int setL(long double const _l);
	virtual int setR(short const _r);
	virtual int setSubst(std::string const _subst);
	virtual int setNet1(std::string const _net1);
	virtual int setNet2(std::string const _net2);
	virtual int setNet3(std::string const _net3);
	virtual int setNet4(std::string const _net4);
	virtual int setP(void);
};

#endif // ELEMENT_HPP
