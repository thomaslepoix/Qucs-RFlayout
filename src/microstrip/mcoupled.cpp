/***************************************************************************
                               mcoupled.cpp
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

#include "mcoupled.hpp"
using namespace std;

//******************************************************************************
string const Mcoupled::m_descriptor("microstrip_coupled_lines");

//******************************************************************************
Mcoupled::Mcoupled(string _label,
			string _type,
			bool _active,
			bool _mirrorx,
			short _r,
			string _subst,
			long double _w,
			long double _l,
			long double _s) :
	Element(_label, _type, _active, _mirrorx, _r, 4, _subst),
	m_w(_w),
	m_l(_l),
	m_s(_s)
	{}

//******************************************************************************
string Mcoupled::getDescriptor(void) const {
	return(m_descriptor);
	}

//******************************************************************************
long double Mcoupled::getW(void) const {
	return(m_w);
	}

//******************************************************************************
long double Mcoupled::getL(void) const {
	return(m_l);
	}

//******************************************************************************
long double Mcoupled::getS(void) const {
	return(m_s);
	}

//******************************************************************************
string Mcoupled::getNet1(void) const {
	return(m_net1);
	}

//******************************************************************************
string Mcoupled::getNet2(void) const {
	return(m_net2);
	}

//******************************************************************************
string Mcoupled::getNet3(void) const {
	return(m_net3);
	}

//******************************************************************************
string Mcoupled::getNet4(void) const {
	return(m_net4);
	}

//******************************************************************************
int Mcoupled::getNpoint(void) const {
	return(m_npoint);
	}

//******************************************************************************
long double Mcoupled::getP(int const _n, axis_t const _xy, orientation_t const _r, origin_t const _abs, bool const /*apply_shift*/) const {
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
int Mcoupled::setNet1(string const _net1) {
	m_net1=_net1;
	return(0);
	}

//******************************************************************************
int Mcoupled::setNet2(string const _net2) {
	m_net2=_net2;
	return(0);
	}

//******************************************************************************
int Mcoupled::setNet3(string const _net3) {
	m_net3=_net3;
	return(0);
	}

//******************************************************************************
int Mcoupled::setNet4(string const _net4) {
	m_net4=_net4;
	return(0);
	}

//******************************************************************************
int Mcoupled::setP(void) {
	tab_p[0][X]=-m_l/2;
	tab_p[0][Y]= (m_s/2+m_w);
	tab_p[1][X]= m_l/2;
	tab_p[1][Y]= (m_s/2+m_w);
	tab_p[2][X]= m_l/2;
	tab_p[2][Y]= m_s/2;
	tab_p[3][X]=-m_l/2;
	tab_p[3][Y]= m_s/2;
	tab_p[4][X]=-m_l/2;
	tab_p[4][Y]=-m_s/2;
	tab_p[5][X]= m_l/2;
	tab_p[5][Y]=-m_s/2;
	tab_p[6][X]= m_l/2;
	tab_p[6][Y]=-(m_s/2+m_w);
	tab_p[7][X]=-m_l/2;
	tab_p[7][Y]=-(m_s/2+m_w);
	return(0);
	}

//******************************************************************************
void Mcoupled::getStep(int const _net, long double& xstep, long double& ystep) const {
	if(m_mirrorx==0 && m_r==0) {
		if(_net==1) {
			xstep= - m_l/2;
			ystep= - (m_w+m_s)/2;
		} else if(_net==2) {
			xstep= + m_l/2;
			ystep= - (m_w+m_s)/2;
		} else if(_net==3) {
			xstep= + m_l/2;
			ystep= + (m_w+m_s)/2;
		} else if(_net==4) {
			xstep= - m_l/2;
			ystep= + (m_w+m_s)/2;
			}
	} else if(m_mirrorx==0 && m_r==90) {
		if(_net==1) {
			xstep= - (m_w+m_s)/2;
			ystep= + m_l/2;
		} else if(_net==2) {
			xstep= - (m_w+m_s)/2;
			ystep= - m_l/2;
		} else if(_net==3) {
			xstep= + (m_w+m_s)/2;
			ystep= - m_l/2;
		} else if(_net==4) {
			xstep= + (m_w+m_s)/2;
			ystep= + m_l/2;
			}
	} else if(m_mirrorx==0 && m_r==180) {
		if(_net==1) {
			xstep= + m_l/2;
			ystep= + (m_w+m_s)/2;
		} else if(_net==2) {
			xstep= - m_l/2;
			ystep= + (m_w+m_s)/2;
		} else if(_net==3) {
			xstep= - m_l/2;
			ystep= - (m_w+m_s)/2;
		} else if(_net==4) {
			xstep= + m_l/2;
			ystep= - (m_w+m_s)/2;
			}
	} else if(m_mirrorx==0 && m_r==270) {
		if(_net==1) {
			xstep= + (m_w+m_s)/2;
			ystep= - m_l/2;
		} else if(_net==2) {
			xstep= + (m_w+m_s)/2;
			ystep= + m_l/2;
		} else if(_net==3) {
			xstep= - (m_w+m_s)/2;
			ystep= + m_l/2;
		} else if(_net==4) {
			xstep= - (m_w+m_s)/2;
			ystep= - m_l/2;
			}
	} else if(m_mirrorx==1 && m_r==0) {
		if(_net==1) {
			xstep= - m_l/2;
			ystep= + (m_w+m_s)/2;
		} else if(_net==2) {
			xstep= + m_l/2;
			ystep= + (m_w+m_s)/2;
		} else if(_net==3) {
			xstep= + m_l/2;
			ystep= - (m_w+m_s)/2;
		} else if(_net==4) {
			xstep= - m_l/2;
			ystep= - (m_w+m_s)/2;
			}
	} else if(m_mirrorx==1 && m_r==90) {
		if(_net==1) {
			xstep= + (m_w+m_s)/2;
			ystep= + m_l/2;
		} else if(_net==2) {
			xstep= + (m_w+m_s)/2;
			ystep= - m_l/2;
		} else if(_net==3) {
			xstep= - (m_w+m_s)/2;
			ystep= - m_l/2;
		} else if(_net==4) {
			xstep= - (m_w+m_s)/2;
			ystep= + m_l/2;
			}
	} else if(m_mirrorx==1 && m_r==180) {
		if(_net==1) {
			xstep= + m_l/2;
			ystep= - (m_w+m_s)/2;
		} else if(_net==2) {
			xstep= - m_l/2;
			ystep= - (m_w+m_s)/2;
		} else if(_net==3) {
			xstep= - m_l/2;
			ystep= + (m_w+m_s)/2;
		} else if(_net==4) {
			xstep= + m_l/2;
			ystep= + (m_w+m_s)/2;
			}
	} else if(m_mirrorx==1 && m_r==270) {
		if(_net==1) {
			xstep= - (m_w+m_s)/2;
			ystep= - m_l/2;
		} else if(_net==2) {
			xstep= - (m_w+m_s)/2;
			ystep= + m_l/2;
		} else if(_net==3) {
			xstep= + (m_w+m_s)/2;
			ystep= + m_l/2;
		} else if(_net==4) {
			xstep= + (m_w+m_s)/2;
			ystep= - m_l/2;
			}
		}
	}

//******************************************************************************
void Mcoupled::getEdge(int const _net, long double& edge, short& dir) const {
	edge=m_w;
	if(_net==1 || _net==4) {
		switch(m_r) {
			case 0: dir=XMIN; break;
			case 90: dir=YMAX; break;
			case 180: dir=XMAX; break;
			case 270: dir=YMIN; break;
			}
	} else if(_net==2 || _net==3) {
		switch(m_r) {
			case 0: dir=XMAX; break;
			case 90: dir=YMIN; break;
			case 180: dir=XMIN; break;
			case 270: dir=YMAX; break;
			}
		}
	}

//******************************************************************************
int Mcoupled::getOemsNcorelines(void) const {
	return(3);
	}

//******************************************************************************
int Mcoupled::getOemsMeshCore(int const _n, OemsLine& line) const {
	if(_n==0) {
		switch(m_r) {
			case 0:   line.position=getP(0, Y, R, ABS); line.direction=YMAX; break;
			case 90:  line.position=getP(0, X, R, ABS); line.direction=XMAX; break;
			case 180: line.position=getP(0, Y, R, ABS); line.direction=YMIN; break;
			case 270: line.position=getP(0, X, R, ABS); line.direction=XMIN; break;
			}
	} else if(_n==1) {
		switch(m_r) {
			case 0:   line.position=getP(2, Y, R, ABS); line.direction=YMIN; break;
			case 90:  line.position=getP(2, X, R, ABS); line.direction=XMIN; break;
			case 180: line.position=getP(2, Y, R, ABS); line.direction=YMAX; break;
			case 270: line.position=getP(2, X, R, ABS); line.direction=XMAX; break;
			}
	} else if(_n==2) {
		switch(m_r) {
			case 0:   line.position=getP(4, Y, R, ABS); line.direction=YMAX; break;
			case 90:  line.position=getP(4, X, R, ABS); line.direction=XMAX; break;
			case 180: line.position=getP(4, Y, R, ABS); line.direction=YMIN; break;
			case 270: line.position=getP(4, X, R, ABS); line.direction=XMIN; break;
			}
	} else if(_n==3) {
		switch(m_r) {
			case 0:   line.position=getP(6, Y, R, ABS); line.direction=YMIN; break;
			case 90:  line.position=getP(6, X, R, ABS); line.direction=XMIN; break;
			case 180: line.position=getP(6, Y, R, ABS); line.direction=YMAX; break;
			case 270: line.position=getP(6, X, R, ABS); line.direction=XMAX; break;
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
int Mcoupled::getOemsMeshInterface(int const _net, OemsLine& line) const {
	if((_net==1
	&&(adjacent1.first==nullptr
	||(adjacent1.first!=nullptr && adjacent1.first->isOemsMeshInterface(adjacent1.second, m_w))))
	|| (_net==4
	&&(adjacent4.first==nullptr
	||(adjacent4.first!=nullptr && adjacent4.first->isOemsMeshInterface(adjacent4.second, m_w))))) {
		switch(m_r) {
			case 0:   line.position=getP(0, X, R, ABS); line.direction=XMIN; break;
			case 90:  line.position=getP(0, Y, R, ABS); line.direction=YMAX; break;
			case 180: line.position=getP(0, X, R, ABS); line.direction=XMAX; break;
			case 270: line.position=getP(0, Y, R, ABS); line.direction=YMIN; break;
			}
	} else if((_net==2
	       &&(adjacent2.first==nullptr
	       ||(adjacent2.first!=nullptr && adjacent2.first->isOemsMeshInterface(adjacent2.second, m_w))))
	       || (_net==3
	       &&(adjacent3.first==nullptr
	       ||(adjacent3.first!=nullptr && adjacent3.first->isOemsMeshInterface(adjacent3.second, m_w))))) {
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
bool Mcoupled::isOemsMeshInterface(int const _port, long double const _w) const {
	if(_port==1 || _port==2 || _port==3 || _port==4) {
		return(_w>m_w ? true : false);
	} else {
		return(false);
		}
	}

//******************************************************************************
int Mcoupled::setAdjacent(int const _port, shared_ptr<Element> const& adjacent, int const adjacent_port) {
	switch(_port) {
		case 1:
			adjacent1.first=adjacent;
			adjacent1.second=adjacent_port;
			break;
		case 2:
			adjacent2.first=adjacent;
			adjacent2.second=adjacent_port;
			break;
		case 3:
			adjacent3.first=adjacent;
			adjacent3.second=adjacent_port;
			break;
		case 4:
			adjacent4.first=adjacent;
			adjacent4.second=adjacent_port;
			break;
		default:
			return(1);
		}
	return(0);
	}
