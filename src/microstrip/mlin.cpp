/***************************************************************************
                               mlin.cpp
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

#include "mlin.hpp"
using namespace std;

Mlin::Mlin(string _label,
			string _type,
			bool _mirrorx,
			short _r,
			string _subst,
			long double _w,
			long double _l) :
	Element(_label, _type, _mirrorx, _r, 2, _subst),
	m_w(_w),
	m_l(_l)
	{}

Mlin::~Mlin() {
	}

string Mlin::getDescriptor(void) {
	return(m_descriptor);
	}

long double Mlin::getW(void) {
	return(m_w);
	}

long double Mlin::getL(void) {
	return(m_l);
	}

string Mlin::getNet1(void) {
	return(m_net1);
	}

string Mlin::getNet2(void) {
	return(m_net2);
	}

int Mlin::getNpoint(void) {
	return(m_npoint);
	}

long double Mlin::getP(int _n, axis_t _xy, orientation_t _r, origin_t _abs) {
	long double coord;
	if(_r) {
		coord= _xy ? rotateY(tab_p[_n][X], tab_p[_n][Y])
		           : rotateX(tab_p[_n][X], tab_p[_n][Y]);
	} else {
		coord=tab_p[_n][_xy];
		}
	return(_abs ? coord+(_xy ? m_y : m_x) : coord);
	}

int Mlin::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

int Mlin::setNet2(string _net2) {
	m_net2=_net2;
	return(0);
	}

int Mlin::setP(void) {
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

void Mlin::getStep(int const _net, long double& xstep, long double& ystep) {
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

void Mlin::getEdge(int const _net, long double& edge, short& dir) {
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
