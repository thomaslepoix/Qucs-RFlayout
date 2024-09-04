///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#include "mlin.hpp"
using namespace std;

//******************************************************************************
string const Mlin::m_descriptor("microstrip_line");

//******************************************************************************
Mlin::Mlin(string const _label,
			string const _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			string const _subst,
			long double const _w,
			long double const _l) :
	Element(_label, _type, _active, _mirrorx, _r, 2, _subst),
	m_w(_w),
	m_l(_l)
	{}

//******************************************************************************
string Mlin::getDescriptor() const {
	return(m_descriptor);
	}

//******************************************************************************
long double Mlin::getW() const {
	return(m_w);
	}

//******************************************************************************
long double Mlin::getL() const {
	return(m_l);
	}

//******************************************************************************
string Mlin::getNet1() const {
	return(m_net1);
	}

//******************************************************************************
string Mlin::getNet2() const {
	return(m_net2);
	}

//******************************************************************************
int Mlin::getNpoint() const {
	return(m_npoint);
	}

//******************************************************************************
long double Mlin::getP(int const _n, axis_t const _xy, orientation_t const _r, origin_t const _abs, bool const /*apply_shift*/) const {
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
int Mlin::setNet1(string const _net1) {
	m_net1=_net1;
	return(0);
	}

//******************************************************************************
int Mlin::setNet2(string const _net2) {
	m_net2=_net2;
	return(0);
	}

//******************************************************************************
int Mlin::setP() {
	tab_p[0][X]=-m_l/2;
	tab_p[0][Y]= m_w/2;
	tab_p[1][X]= m_l/2;
	tab_p[1][Y]= m_w/2;
	tab_p[2][X]= m_l/2;
	tab_p[2][Y]=-m_w/2;
	tab_p[3][X]=-m_l/2;
	tab_p[3][Y]=-m_w/2;
	return(0);
	}

//******************************************************************************
void Mlin::getStep(int const _net, long double& xstep, long double& ystep) const {
	if(m_r==0) {
		if(_net==1) {
			xstep= - m_l/2;
			ystep=0;
		} else if(_net==2) {
			xstep= + m_l/2;
			ystep=0;
			}
	} else if(m_r==90) {
		if(_net==1) {
			xstep=0;
			ystep= + m_l/2;
		} else if(_net==2) {
			xstep=0;
			ystep= - m_l/2;
			}
	} else if(m_r==180) {
		if(_net==1) {
			xstep= + m_l/2;
			ystep=0;
		} else if(_net==2) {
			xstep= - m_l/2;
			ystep=0;
			}
	} else if(m_r==270) {
		if(_net==1) {
			xstep=0;
			ystep= - m_l/2;
		} else if(_net==2) {
			xstep=0;
			ystep= + m_l/2;
			}
		}
	}

//******************************************************************************
void Mlin::getEdge(int const _net, long double& edge, short& dir) const {
	edge=m_w;
	if(_net==1) {
		switch(m_r) {
			case 0: dir=XMIN; break;
			case 90: dir=YMAX; break;
			case 180: dir=XMAX; break;
			case 270: dir=YMIN; break;
			}
	} else if(_net==2) {
		switch(m_r) {
			case 0: dir=XMAX; break;
			case 90: dir=YMIN; break;
			case 180: dir=XMIN; break;
			case 270: dir=YMAX; break;
			}
		}
	}

//******************************************************************************
int Mlin::getOemsNcorelines() const {
	return(2);
	}

//******************************************************************************
int Mlin::getOemsMeshCore(int const _n, OemsLine& line) const {
/*	axis_t axis;
	switch(m_r) {
		case  0: case 180: axis=Y; break;
		case 90: case 270: axis=X; break;
		default: axis=X; break; // Never happens
		}*/

	if(_n==0) {
//		line.position=getP(0, axis, R, ABS);
		switch(m_r) {
			case 0:   line.position=getP(0, Y, R, ABS); line.direction=YMAX; break;
			case 90:  line.position=getP(0, X, R, ABS); line.direction=XMAX; break;
			case 180: line.position=getP(0, Y, R, ABS); line.direction=YMIN; break;
			case 270: line.position=getP(0, X, R, ABS); line.direction=XMIN; break;
			}
	} else if(_n==1) {
//		line.position=getP(2, axis, R, ABS);
		switch(m_r) {
			case 0:   line.position=getP(2, Y, R, ABS); line.direction=YMIN; break;
			case 90:  line.position=getP(2, X, R, ABS); line.direction=XMIN; break;
			case 180: line.position=getP(2, Y, R, ABS); line.direction=YMAX; break;
			case 270: line.position=getP(2, X, R, ABS); line.direction=XMAX; break;
			}
	} else {
		return(1);
		}

	line.label=m_label;
	line.type=m_type;
	line.third_rule=true;
	return(0);
	}

//******************************************************************************
int Mlin::getOemsMeshInterface(int const _net, OemsLine& line) const {
/*	axis_t axis;
	switch(m_r) {
		case  0: case 180: axis=X; break;
		case 90: case 270: axis=Y; break;
		default: axis=X; break; // Never happens
		}*/

	if(_net==1
	&&(adjacent1.first==nullptr
	||(adjacent1.first!=nullptr && adjacent1.first->isOemsMeshInterface(adjacent1.second, m_w)))) {
//		line.position=getP(0, axis, R, ABS);
		switch(m_r) {
			case 0:   line.position=getP(0, X, R, ABS); line.direction=XMIN; break;
			case 90:  line.position=getP(0, Y, R, ABS); line.direction=YMAX; break;
			case 180: line.position=getP(0, X, R, ABS); line.direction=XMAX; break;
			case 270: line.position=getP(0, Y, R, ABS); line.direction=YMIN; break;
			}
	} else if(_net==2
	       &&(adjacent2.first==nullptr
	       ||(adjacent2.first!=nullptr && adjacent2.first->isOemsMeshInterface(adjacent2.second, m_w)))) {
//		line.position=getP(2, axis, R, ABS);
		switch(m_r) {
			case 0:   line.position=getP(2, X, R, ABS); line.direction=XMAX; break;
			case 90:  line.position=getP(2, Y, R, ABS); line.direction=YMIN; break;
			case 180: line.position=getP(2, X, R, ABS); line.direction=XMIN; break;
			case 270: line.position=getP(2, Y, R, ABS); line.direction=YMAX; break;
			}
	} else {
		return(1);
		}

	line.label=m_label;
	line.type=m_type;
	line.third_rule=true;
	return(0);
	}

//******************************************************************************
bool Mlin::isOemsMeshInterface(int const _port, long double const _w) const {
	if(_port==1 || _port==2) {
		return(_w>m_w ? true : false);
	} else {
		return(false);
		}
	}

//******************************************************************************
int Mlin::setAdjacent(int const _port, shared_ptr<Element> const& adjacent, int const adjacent_port) {
	switch(_port) {
		case 1:
			adjacent1.first=adjacent;
			adjacent1.second=adjacent_port;
			break;
		case 2:
			adjacent2.first=adjacent;
			adjacent2.second=adjacent_port;
			break;
		default:
			return(1);
		}
	return(0);
	}
