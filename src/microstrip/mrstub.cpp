///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#define _USE_MATH_DEFINES

#include <cmath>

#include "mrstub.hpp"
using namespace std;

//******************************************************************************
string const Mrstub::m_descriptor("microstrip_radial_stub");

//******************************************************************************
Mrstub::Mrstub(string _label,
			string _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			string _subst,
			long double const _ri,
			long double const _ro,
			long double const _alpha) :
	Element(std::move(_label), std::move(_type), _active, _mirrorx, _r, 1, std::move(_subst)),
	m_w(2*_ri*sin((M_PI/180)*(_alpha/2))),
	m_l(sqrt((_ri*_ri)-((m_w/2)*(m_w/2)))),
	m_ri(_ri),
	m_ro(_ro),
	m_alpha(_alpha)
	{}

//******************************************************************************
string Mrstub::getDescriptor() const {
	return(m_descriptor);
	}

//******************************************************************************
long double Mrstub::getW() const {
	return(m_w);
	}

//******************************************************************************
long double Mrstub::getL() const {
	return(m_l);
	}

//******************************************************************************
long double Mrstub::getRi() const {
	return(m_ri);
	}

//******************************************************************************
long double Mrstub::getRo() const {
	return(m_ro);
	}

//******************************************************************************
long double Mrstub::getAlpha() const {
	return(m_alpha);
	}

//******************************************************************************
string Mrstub::getNet1() const {
	return(m_net1);
	}

//******************************************************************************
int Mrstub::getNpoint() const {
	return(m_npoint);
	}

//******************************************************************************
long double Mrstub::getP(int const _n, axis_t const _xy, orientation_t const _r, origin_t const _abs, bool const /*apply_shift*/) const {
	long double coord;
	if(_r) {
		coord= _xy ? rotateY(tab_p[_n][X], tab_p[_n][Y])
		           : rotateX(tab_p[_n][X], tab_p[_n][Y]);
	} else {
		coord=tab_p[_n][_xy];
		}
	return(_abs ? coord+(_xy ? m_y : m_x) : coord);
	}

//******************************************************************************
int Mrstub::setNet1(string const& _net1) {
	m_net1=_net1;
	return(0);
	}

//******************************************************************************
int Mrstub::setP() {
// TODO 0 at bottom left, counter clockwise
// instead of 0 at bottom right, clockwise
	int const div=m_npoint-5; // -4 fixed points, -1 number -> index
	long double const n=m_alpha/div;
	long double u=-(m_npoint-2)/2*n+n;
	signed short const s= m_mirrorx ? -1 : 1;

	tab_p[0][X]= m_w/2;
	tab_p[0][Y]=0;
	tab_p[1][X]=-m_w/2;
	tab_p[1][Y]=0;
	tab_p[2][X]= m_ro*sin((M_PI/180)*(-m_alpha/2));
	tab_p[2][Y]=s*((-m_ro*cos((M_PI/180)*(-m_alpha/2)))+m_l);
	for(int i=3;i<m_npoint-1;i++) {
		tab_p[i][X]=m_ro*sin((M_PI/180)*(u));
		tab_p[i][Y]=s*((-m_ro*cos((M_PI/180)*(u)))+m_l);
		u+=n;
		}
	tab_p[m_npoint-1][X]=-m_ro*sin((M_PI/180)*(-m_alpha/2));
	tab_p[m_npoint-1][Y]=s*((-m_ro*cos((M_PI/180)*(-m_alpha/2)))+m_l);
	return(0);
	}

//******************************************************************************
void Mrstub::getEdge(int const /*_net*/, long double& edge, short& dir) const {
	edge=m_w;
	if(m_mirrorx==0) {
		switch(m_r) {
			case 0: dir=YMAX; break;
			case 90: dir=XMAX; break;
			case 180: dir=YMIN; break;
			case 270: dir=XMIN; break;
			}
	} else if(m_mirrorx==1) {
		switch(m_r) {
			case 0: dir=YMIN; break;
			case 90: dir=XMIN; break;
			case 180: dir=YMAX; break;
			case 270: dir=XMAX; break;
			}
		}
	}

//******************************************************************************
int Mrstub::getOemsNcorelines() const {
	return(4);
	}

//******************************************************************************
int Mrstub::getOemsMeshCore(int const _n, OemsLine& line) const {
	if(_n==0) {
		if(m_mirrorx==0) {
			switch(m_r) {
				case 0:   line.position=getP(0, Y, R, ABS); line.direction=YMAX; break;
				case 90:  line.position=getP(0, X, R, ABS); line.direction=XMAX; break;
				case 180: line.position=getP(0, Y, R, ABS); line.direction=YMIN; break;
				case 270: line.position=getP(0, X, R, ABS); line.direction=XMIN; break;
				}
		} else if(m_mirrorx==1) {
			switch(m_r) {
				case 0:   line.position=getP(0, Y, R, ABS); line.direction=YMIN; break;
				case 90:  line.position=getP(0, X, R, ABS); line.direction=XMIN; break;
				case 180: line.position=getP(0, Y, R, ABS); line.direction=YMAX; break;
				case 270: line.position=getP(0, X, R, ABS); line.direction=XMAX; break;
				}
			}
	} else if(_n==1) {
		switch(m_r) {
			case 0:   line.position=getP(2, X, R, ABS); line.direction=XMIN; break;
			case 90:  line.position=getP(2, Y, R, ABS); line.direction=YMAX; break;
			case 180: line.position=getP(2, X, R, ABS); line.direction=XMAX; break;
			case 270: line.position=getP(2, Y, R, ABS); line.direction=YMIN; break;
			}
	} else if(_n==2) {
		int p=(m_npoint-5)/2+3;
		if(m_mirrorx==0) {
			switch(m_r) {
				case 0:   line.position=getP(p, Y, R, ABS); line.direction=YMIN; break;
				case 90:  line.position=getP(p, X, R, ABS); line.direction=XMIN; break;
				case 180: line.position=getP(p, Y, R, ABS); line.direction=YMAX; break;
				case 270: line.position=getP(p, X, R, ABS); line.direction=XMAX; break;
				}
		} else {
			switch(m_r) {
				case 0:   line.position=getP(p, Y, R, ABS); line.direction=YMAX; break;
				case 90:  line.position=getP(p, X, R, ABS); line.direction=XMAX; break;
				case 180: line.position=getP(p, Y, R, ABS); line.direction=YMIN; break;
				case 270: line.position=getP(p, X, R, ABS); line.direction=XMIN; break;
				}
			}
	} else if(_n==3) {
		int p=m_npoint-1;
		switch(m_r) {
			case 0:   line.position=getP(p, X, R, ABS); line.direction=XMAX; break;
			case 90:  line.position=getP(p, Y, R, ABS); line.direction=YMIN; break;
			case 180: line.position=getP(p, X, R, ABS); line.direction=XMIN; break;
			case 270: line.position=getP(p, Y, R, ABS); line.direction=YMAX; break;
			}
	} else {
		return(1);
		}

	line.label=m_label;
	line.type=m_type;
	line.third_rule=true;
	line.high_res=true;
	return(0);
	}

//******************************************************************************
bool Mrstub::isOemsMeshInterface(int const _port, long double const _w) const {
	if(_port==1) {
		return(_w>m_w ? true : false);
	} else {
		return(false);
		}
	}
