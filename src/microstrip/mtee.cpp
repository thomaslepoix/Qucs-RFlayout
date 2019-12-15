/***************************************************************************
                               mtee.cpp
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

#include "mtee.h"
using namespace std;

Mtee::Mtee(string _label,
			string _type,
			bool _mirrorx,
			short _r,
			short _nport,
			long double _w1,
			long double _w2,
			long double _w3) :
	Element(_label, _type, _mirrorx, _r, _nport),
	m_w1(_w1),
	m_w2(_w2),
	m_w3(_w3)
	{}

Mtee::~Mtee() {
	}

string Mtee::getDescriptor(void) {
	return(m_descriptor);
	}

long double Mtee::getW1(void) {
	return(m_w1);
	}

long double Mtee::getW2(void) {
	return(m_w2);
	}

long double Mtee::getW3(void) {
	return(m_w3);
	}

string Mtee::getNet1(void) {
	return(m_net1);
	}

string Mtee::getNet2(void) {
	return(m_net2);
	}

string Mtee::getNet3(void) {
	return(m_net3);
	}

int Mtee::getNpoint(void) {
	return(m_npoint);
	}

long double Mtee::getP(int _n, axis_t _xy, orientation_t _r, origin_t _abs) {
	long double coord;
	if(_r) {
		coord= _xy ? rotateY(tab_p[_n][0], tab_p[_n][1])
		           : rotateX(tab_p[_n][0], tab_p[_n][1]);
	} else {
		coord=tab_p[_n][_xy];
		}
	return(_abs ? coord+(_xy ? m_y : m_x) : coord);
	}

int Mtee::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

int Mtee::setNet2(string _net2) {
	m_net2=_net2;
	return(0);
	}

int Mtee::setNet3(string _net3) {
	m_net3=_net3;
	return(0);
	}

int Mtee::setP(void) {
	signed short s1; //= m_mirror ? -1 :  1;
	signed short s2; //= m_mirror ?  1 : -1;
	long double Wlong= (m_w1>m_w2) ? m_w1 : m_w2;
	if(m_mirrorx) {
		s1=-1;
		s2= 1;
	} else {
		s1= 1;
		s2=-1;
		}
	tab_p[0][X]=-m_w3/2;
	tab_p[0][Y]=s1*Wlong/2;
	tab_p[1][X]= m_w3/2;
	tab_p[1][Y]=s1*Wlong/2;
	tab_p[2][X]= m_w3/2;
	tab_p[2][Y]=s2*m_w2/2;
	tab_p[3][X]=0;
	tab_p[3][Y]=s2*m_w2/2;
	tab_p[4][X]=0;
	tab_p[4][Y]=s2*m_w1/2;
	tab_p[5][X]=-m_w3/2;
	tab_p[5][Y]=s2*m_w1/2;
	return(0);
	}

void Mtee::getStep(int const _net, long double& xstep, long double& ystep) {
	long double Wlong=0;
	if(m_mirrorx==0 && m_r==0) {
		if(_net==1) {
			xstep= - (m_w3)/2;
			ystep=0;
		} else if(_net==2) {
			xstep= + (m_w3)/2;
			ystep=0;
		} else if(_net==3) {
			Wlong= (m_w1>m_w2) ? m_w1 : m_w2;
			xstep=0;
			ystep= + (Wlong)/2;
			}
	} else if(m_mirrorx==0 && m_r==90) {
		if(_net==1) {
			xstep=0;
			ystep= + (m_w3)/2;
		} else if(_net==2) {
			xstep=0;
			ystep= - (m_w3)/2;
		} else if(_net==3) {
			Wlong= (m_w1>m_w2) ? m_w1 : m_w2;
			xstep= + (Wlong)/2;
			ystep=0;
			}
	} else if(m_mirrorx==0 && m_r==180) {
		if(_net==1) {
			xstep= + (m_w3)/2;
			ystep=0;
		} else if(_net==2) {
			xstep= - (m_w3)/2;
			ystep=0;
		} else if(_net==3) {
			Wlong= (m_w1>m_w2) ? m_w1 : m_w2;
			xstep=0;
			ystep= - (Wlong)/2;
			}
	} else if(m_mirrorx==0 && m_r==270) {
		if(_net==1) {
			xstep=0;
			ystep= - (m_w3)/2;
		} else if(_net==2) {
			xstep=0;
			ystep= + (m_w3)/2;
		} else if(_net==3) {
			Wlong= (m_w1>m_w2) ? m_w1 : m_w2;
			xstep= - (Wlong)/2;
			ystep=0;
			}
	} else if(m_mirrorx==1 && m_r==0) {
		if(_net==1) {
			xstep= - (m_w3)/2;
			ystep=0;
		} else if(_net==2) {
			xstep= + (m_w3)/2;
			ystep=0;
		} else if(_net==3) {
			Wlong= (m_w1>m_w2) ? m_w1 : m_w2;
			xstep=0;
			ystep= - (Wlong)/2;
			}
	} else if(m_mirrorx==1 && m_r==90) {
		if(_net==1) {
			xstep=0;
			ystep= + (m_w3)/2;
		} else if(_net==2) {
			xstep=0;
			ystep= - (m_w3)/2;
		} else if(_net==3) {
			Wlong= (m_w1>m_w2) ? m_w1 : m_w2;
			xstep= - (Wlong)/2;
			ystep=0;
			}
	} else if(m_mirrorx==1 && m_r==180) {
		if(_net==1) {
			xstep= + (m_w3)/2;
			ystep=0;
		} else if(_net==2) {
			xstep= - (m_w3)/2;
			ystep=0;
		} else if(_net==3) {
			Wlong= (m_w1>m_w2) ? m_w1 : m_w2;
			xstep=0;
			ystep= + (Wlong)/2;
			}
	} else if(m_mirrorx==1 && m_r==270) {
		if(_net==1) {
			xstep=0;
			ystep= - (m_w3)/2;
		} else if(_net==2) {
			xstep=0;
			ystep= + (m_w3)/2;
		} else if(_net==3) {
			Wlong= (m_w1>m_w2) ? m_w1 : m_w2;
			xstep= + (Wlong)/2;
			ystep=0;
			}
		}
	}
