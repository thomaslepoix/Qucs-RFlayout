///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#pragma once

#include <memory>
#include <string>

#include "oemsline.hpp"

//******************************************************************************
enum axis_t { X, Y };            // x axis / y axis
enum orientation_t { NOR, R };   // no rotation / rotation
enum origin_t { REL, ABS };      // relative / absolute
enum { XMIN, XMAX, YMIN, YMAX }; // boundary index

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
			bool const _active,
			bool const _mirrorx,
			short const _r,
			short const _nport,
			std::string _subst);
	virtual ~Element()=default;
	std::shared_ptr<Element> prev;
	std::string getLabel() const;
	std::string getType() const;
	bool getActive() const;
	bool getMirrorx() const;
	short getR() const;
	short getNport() const;
	std::string getSubst() const;
	long double getX(bool const apply_shift=true) const;
	long double getY(bool const apply_shift=true) const;
	int setX(long double const _x);
	int setY(long double const _y);
	int setShiftX(long double const _shift_x);
	int setShiftY(long double const _shift_y);

	//default functions, to override
	virtual std::string getDescriptor() const;
	virtual long double getW() const;
	virtual long double getW1() const;
	virtual long double getW2() const;
	virtual long double getW3() const;
	virtual long double getW4() const;
	virtual long double getL() const;
	virtual long double getD() const;
	virtual long double getS() const;
	virtual long double getRi() const;
	virtual long double getRo() const;
	virtual long double getZ() const;
	virtual long double getDbm() const;
	virtual long double getF() const;
	virtual long double getFstart() const;
	virtual long double getFstop() const;
	virtual long double getEr() const;
	virtual long double getH() const;
	virtual long double getT() const;
	virtual long double getTand() const;
	virtual long double getRho() const;
	virtual long double getMargin() const;
	virtual long double getAlpha() const;
	virtual unsigned long getN() const;
	virtual std::string getSimtype() const;
	virtual std::string getNet1() const;
	virtual std::string getNet2() const;
	virtual std::string getNet3() const;
	virtual std::string getNet4() const;
	virtual int getNpoint() const;
	virtual long double getP(int const _n, axis_t const _xy, orientation_t const _r, origin_t const _abs, bool const apply_shift=true) const;
	virtual void getStep(int const _net, long double& xstep, long double& ystep) const;
	virtual void getEdge(int const _net, long double& edge, short& dir) const;
	virtual int getOemsNcorelines() const;
	virtual int getOemsMeshCore(int const _n, OemsLine& line) const;
	virtual int getOemsMeshInterface(int const _net, OemsLine& line) const;
	virtual bool isOemsMeshInterface(int const _port, long double const _w) const;
	virtual int setAdjacent(int const _port, std::shared_ptr<Element> const& element, int const adjacent_port);

	virtual int setW(long double const _w);
	virtual int setL(long double const _l);
	virtual int setR(short const _r);
	virtual int setSubst(std::string const& _subst);
	virtual int setNet1(std::string const& _net1);
	virtual int setNet2(std::string const& _net2);
	virtual int setNet3(std::string const& _net3);
	virtual int setNet4(std::string const& _net4);
	virtual int setP();
};
