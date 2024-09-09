///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#define _USE_MATH_DEFINES

#include <cmath>

#include "element.hpp"
using namespace std;

//******************************************************************************
Element::Element(string _label,
			string _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			short const _nport,
			string _subst) :
	m_label(std::move(_label)),
	m_type(std::move(_type)),
	m_active(_active),
	m_mirrorx(_mirrorx),
	m_r(_r),
	m_nport(_nport),
	m_subst(std::move(_subst)),
	m_x(NAN),
	m_y(NAN),
	m_shift_x(0.0),
	m_shift_y(0.0),
	prev(nullptr)
	{}

//******************************************************************************
string Element::getLabel() const {
	return(m_label);
	}

//******************************************************************************
string Element::getType() const {
	return(m_type);
	}

//******************************************************************************
bool Element::getActive() const {
	return(m_active);
	}

//******************************************************************************
bool Element::getMirrorx() const {
	return(m_mirrorx);
	}

//******************************************************************************
short Element::getR() const {
	return(m_r);
	}

//******************************************************************************
short Element::getNport() const {
	return(m_nport);
	}

//******************************************************************************
string Element::getSubst() const {
	return(m_subst);
	}

//******************************************************************************
long double Element::getX(bool const apply_shift) const {
	return(m_shift_x && apply_shift ? m_x+m_shift_x : m_x); // Avoid useless float calcul.
	}

//******************************************************************************
long double Element::getY(bool const apply_shift) const {
	return(m_shift_y && apply_shift ? m_y+m_shift_y : m_y); // Avoid useless float calcul.
	}

//******************************************************************************
int Element::setX(long double const _x) {
	m_x=_x;
	return(0);
	}

//******************************************************************************
int Element::setY(long double const _y) {
	m_y=_y;
	return(0);
	}

//******************************************************************************
int Element::setShiftX(long double const _shift_x) {
	m_shift_x=_shift_x;
	return(0);
	}

//******************************************************************************
int Element::setShiftY(long double const _shift_y) {
	m_shift_y=_shift_y;
	return(0);
	}

//******************************************************************************
long double Element::rotateX(long double const _x, long double const _y) const {
	return(_x*cos((M_PI/180)*m_r)+_y*sin((M_PI/180)*m_r));
	}

//******************************************************************************
long double Element::rotateY(long double const _x, long double const _y) const {
	return(-_x*sin((M_PI/180)*m_r)+_y*cos((M_PI/180)*m_r));
	}

////////////////////////////////////////////////////////////////////////////////

//******************************************************************************
string Element::getDescriptor() const {
	return("");
	}

//******************************************************************************
long double Element::getW() const {
	return(0);
	}

//******************************************************************************
long double Element::getW1() const {
	return(0);
	}

//******************************************************************************
long double Element::getW2() const {
	return(0);
	}

//******************************************************************************
long double Element::getW3() const {
	return(0);
	}

//******************************************************************************
long double Element::getW4() const {
	return(0);
	}

//******************************************************************************
long double Element::getL() const {
	return(0);
	}

//******************************************************************************
long double Element::getD() const {
	return(0);
	}

//******************************************************************************
long double Element::getS() const {
	return(0);
	}

//******************************************************************************
long double Element::getRi() const {
	return(0);
	}

//******************************************************************************
long double Element::getRo() const {
	return(0);
	}

//******************************************************************************
long double Element::getZ() const {
	return(0);
	}

//******************************************************************************
long double Element::getDbm() const {
	return(0);
	}

//******************************************************************************
long double Element::getF() const {
	return(0);
	}

//******************************************************************************
long double Element::getFstart() const {
	return(0);
	}

//******************************************************************************
long double Element::getFstop() const {
	return(0);
	}

//******************************************************************************
long double Element::getEr() const {
	return(0);
	}

//******************************************************************************
long double Element::getH() const {
	return(0);
	}

//******************************************************************************
long double Element::getT() const {
	return(0);
	}

//******************************************************************************
long double Element::getTand() const {
	return(0);
	}

//******************************************************************************
long double Element::getRho() const {
	return(0);
	}

//******************************************************************************
long double Element::getMargin() const {
	return(0);
	}

//******************************************************************************
long double Element::getAlpha() const {
	return(0);
	}

//******************************************************************************
unsigned long Element::getN() const {
	return(0);
	}

//******************************************************************************
string Element::getSimtype() const {
	return("");
	}

//******************************************************************************
string Element::getNet1() const {
	return("");
	}

//******************************************************************************
string Element::getNet2() const {
	return("");
	}

//******************************************************************************
string Element::getNet3() const {
	return("");
	}

//******************************************************************************
string Element::getNet4() const {
	return("");
	}

//******************************************************************************
int Element::getNpoint() const {
	return(0);
	}

//******************************************************************************
long double Element::getP(int const /*_n*/, axis_t const /*_xy*/, orientation_t const /*_r*/, origin_t const /*_abs*/, bool const /*apply_shift*/) const {
	return(0);
	}

//******************************************************************************
void Element::getStep(int const /*_net*/, long double& xstep, long double& ystep) const {
	xstep=0;
	ystep=0;
	}

//******************************************************************************
void Element::getEdge(int const /*_net*/, long double& edge, short& dir) const {
	edge=0;
	dir=0;
	}

//******************************************************************************
int Element::getOemsNcorelines() const {
	return(0);
	}

//******************************************************************************
int Element::getOemsMeshCore(int const /*_n*/, OemsLine& /*line*/) const {
	return(1);
	}

//******************************************************************************
int Element::getOemsMeshInterface(int const /*_net*/, OemsLine& /*line*/) const {
	return(1);
	}

//******************************************************************************
bool Element::isOemsMeshInterface(int const /*_port*/, long double const /*_w*/) const {
	return(false);
	}

//******************************************************************************
int Element::setAdjacent(int const /*_port*/, Element* /*element*/, int const /*adjacent_port*/) {
	return(1);
	}

//******************************************************************************
int Element::setW(long double const /*_w*/) {
	return(1);
	}

//******************************************************************************
int Element::setL(long double const /*_l*/) {
	return(1);
	}

//******************************************************************************
int Element::setR(short const /*_r*/) {
	return(1);
	}

//******************************************************************************
int Element::setSubst(string const& /*_subst*/) {
	return(1);
	}

//******************************************************************************
int Element::setNet1(string const& /*_net1*/) {
	return(1);
	}

//******************************************************************************
int Element::setNet2(string const& /*_net2*/) {
	return(1);
	}

//******************************************************************************
int Element::setNet3(string const& /*_net3*/) {
	return(1);
	}

//******************************************************************************
int Element::setNet4(string const& /*_net4*/) {
	return(1);
	}

//******************************************************************************
int Element::setP() {
	return(1);
	}
