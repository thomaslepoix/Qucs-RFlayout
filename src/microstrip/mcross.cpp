/***************************************************************************
                               mcross.cpp
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

#include "mcross.h"
using namespace std;

Mcross::Mcross(string _label,
			string _type,
			bool _mirrorx,
			short _r,
			short _nport,
			long double _w1,
			long double _w2,
			long double _w3,
			long double _w4) :
	Element(_label, _type, _mirrorx, _r, _nport),
	m_w1(_w1),
	m_w2(_w2),
	m_w3(_w3),
	m_w4(_w4)
	{}

Mcross::~Mcross() {
	}

string Mcross::getDescriptor(void) {
	return(m_descriptor);
	}

long double Mcross::getW1(void) {
	return(m_w1);
	}

long double Mcross::getW2(void) {
	return(m_w2);
	}

long double Mcross::getW3(void) {
	return(m_w3);
	}

long double Mcross::getW4(void) {
	return(m_w4);
	}

string Mcross::getNet1(void) {
	return(m_net1);
	}

string Mcross::getNet2(void) {
	return(m_net2);
	}

string Mcross::getNet3(void) {
	return(m_net3);
	}

string Mcross::getNet4(void) {
	return(m_net4);
	}

int Mcross::getNpoint(void) {
	return(m_npoint);
	}

long double Mcross::getP(int _n, axis_t _xy, orientation_t _r, origin_t _abs) {
	long double coord;
	if(_r) {
		coord= _xy ? rotateY(tab_p[_n][X], tab_p[_n][Y])
		           : rotateX(tab_p[_n][X], tab_p[_n][Y]);
	} else {
		coord=tab_p[_n][_xy];
		}
	return(_abs ? coord+(_xy ? m_y : m_x) : coord);
	}

int Mcross::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

int Mcross::setNet2(string _net2) {
	m_net2=_net2;
	return(0);
	}

int Mcross::setNet3(string _net3) {
	m_net3=_net3;
	return(0);
	}

int Mcross::setNet4(string _net4) {
	m_net4=_net4;
	return(0);
	}

int Mcross::setP(void) {
//	signed short i=0;
	signed short s1;
	signed short s2;
	long double Wlong13= (m_w1>m_w3) ? m_w1 : m_w3;
	long double Wlong24= (m_w2>m_w4) ? m_w2 : m_w4;
//	unsigned short Wlong13= (m_w1>m_w3) ? m_w1 : m_w3;
	if(m_mirrorx) {
		s1= 1;
		s2=-1;
	} else {
		s1=-1;
		s2= 1;
		}
	if(m_w1==m_w3 || m_w2==m_w4) {
		//shape is a square
		//shape
		// ##
		// ##
		m_npoint=4;
		tab_p[0][X]=  -Wlong24/2;
		tab_p[0][Y]=s1*Wlong13/2;
		tab_p[1][X]=   Wlong24/2;
		tab_p[1][Y]=s1*Wlong13/2;
		tab_p[2][X]=   Wlong24/2;
		tab_p[2][Y]=s2*Wlong13/2;
		tab_p[3][X]=  -Wlong24/2;
		tab_p[3][Y]=s2*Wlong13/2;
	} else {
		if(Wlong13==m_w1 && Wlong24==m_w2) {
			//shape
			// ##
			// #
			tab_p[0][X]=  -Wlong24/2;
			tab_p[0][Y]=s1*Wlong13/2;
			tab_p[1][X]=   Wlong24/2;
			tab_p[1][Y]=s1*Wlong13/2;
			tab_p[2][X]=   m_w2/2;
			tab_p[2][Y]=s2*m_w3/2;
			tab_p[3][X]=   m_w4/2;
			tab_p[3][Y]=s2*m_w3/2;
			tab_p[4][X]=   m_w4/2;
			tab_p[4][Y]=s2*m_w1/2;
			tab_p[5][X]=  -Wlong24/2;
			tab_p[5][Y]=s2*Wlong13/2;
		} else if(Wlong13==m_w1 && Wlong24==m_w4) {
			//shape
			// #
			// ##
			tab_p[0][X]=  -Wlong24/2;
			tab_p[0][Y]=s1*Wlong13/2;
			tab_p[1][X]=   m_w2/2;
			tab_p[1][Y]=s1*m_w1/2;
			tab_p[2][X]=   m_w2/2;
			tab_p[2][Y]=s1*m_w3/2;
			tab_p[3][X]=   m_w4/2;
			tab_p[3][Y]=s1*m_w3/2;
			tab_p[4][X]=   Wlong24/2;
			tab_p[4][Y]=s2*Wlong13/2;
			tab_p[5][X]=  -Wlong24/2;
			tab_p[5][Y]=s2*Wlong13/2;
		} else if(Wlong13==m_w3 && Wlong24==m_w4) {
			//shape
			//  #
			// ##
			tab_p[0][X]=  -m_w4/2;
			tab_p[0][Y]=s1*m_w1/2;
			tab_p[1][X]=  -m_w2/2;
			tab_p[1][Y]=s1*m_w1/2;
			tab_p[2][X]=  -m_w2/2;
			tab_p[2][Y]=s1*m_w3/2;
			tab_p[3][X]=   Wlong24/2;
			tab_p[3][Y]=s1*Wlong13/2;
			tab_p[4][X]=   Wlong24/2;
			tab_p[4][Y]=s2*Wlong13/2;
			tab_p[5][X]=  -Wlong24/2;
			tab_p[5][Y]=s2*Wlong13/2;
		} else if(Wlong13==m_w3 && Wlong24==m_w2) {
			//shape
			// ##
			//  #
			tab_p[0][X]=  -Wlong24/2;
			tab_p[0][Y]=s1*Wlong13/2;
			tab_p[1][X]=   Wlong24/2;
			tab_p[1][Y]=s1*Wlong13/2;
			tab_p[2][X]=   Wlong24/2;
			tab_p[2][Y]=s2*Wlong13/2;
			tab_p[3][X]=  -m_w4/2;
			tab_p[3][Y]=s2*m_w3/2;
			tab_p[4][X]=  -m_w4/2;
			tab_p[4][Y]=s2*m_w1/2;
			tab_p[5][X]=  -m_w2/2;
			tab_p[5][Y]=s2*m_w1/2;
			}
		}
	return(0);
	}

void Mcross::getStep(int const _net, long double& xstep, long double& ystep) {
	long double Wlong=0;
	if(m_mirrorx==0 && m_r==0) {
		if(_net==1) {
			Wlong= (m_w2>m_w4) ? m_w2 : m_w4;
			xstep= - (Wlong)/2;
			ystep=0;
		} else if(_net==2) {
			Wlong= (m_w1>m_w3) ? m_w1 : m_w3;
			xstep=0;
			ystep= - (Wlong)/2;
		} else if(_net==3) {
			Wlong= (m_w2>m_w4) ? m_w2 : m_w4;
			xstep= + (Wlong)/2;
			ystep=0;
		} else if(_net==4) {
			Wlong= (m_w1>m_w3) ? m_w1 : m_w3;
			xstep=0;
			ystep= + (Wlong)/2;
			}
	} else if(m_mirrorx==0 && m_r==90) {
		if(_net==1) {
			Wlong= (m_w2>m_w4) ? m_w2 : m_w4;
			xstep=0;
			ystep= + (Wlong)/2;
		} else if(_net==2) {
			Wlong= (m_w1>m_w3) ? m_w1 : m_w3;
			xstep= - (Wlong)/2;
			ystep=0;
		} else if(_net==3) {
			Wlong= (m_w2>m_w4) ? m_w2 : m_w4;
			xstep=0;
			ystep= - (Wlong)/2;
		} else if(_net==4) {
			Wlong= (m_w1>m_w3) ? m_w1 : m_w3;
			ystep=0;
			xstep= + (Wlong)/2;
			}
	} else if(m_mirrorx==0 && m_r==180) {
		if(_net==1) {
			Wlong= (m_w2>m_w4) ? m_w2 : m_w4;
			xstep= + (Wlong)/2;
			ystep=0;
		} else if(_net==2) {
			Wlong= (m_w1>m_w3) ? m_w1 : m_w3;
			xstep=0;
			ystep= + (Wlong)/2;
		} else if(_net==3) {
			Wlong= (m_w2>m_w4) ? m_w2 : m_w4;
			xstep= - (Wlong)/2;
			ystep=0;
		} else if(_net==4) {
			Wlong= (m_w1>m_w3) ? m_w1 : m_w3;
			xstep=0;
			ystep= - (Wlong)/2;
			}
	} else if(m_mirrorx==0 && m_r==270) {
		if(_net==1) {
			Wlong= (m_w2>m_w4) ? m_w2 : m_w4;
			xstep=0;
			ystep= - (Wlong)/2;
		} else if(_net==2) {
			Wlong= (m_w1>m_w3) ? m_w1 : m_w3;
			xstep= + (Wlong)/2;
			ystep=0;
		} else if(_net==3) {
			Wlong= (m_w2>m_w4) ? m_w2 : m_w4;
			xstep=0;
			ystep= + (Wlong)/2;
		} else if(_net==4) {
			Wlong= (m_w1>m_w3) ? m_w1 : m_w3;
			ystep=0;
			xstep= - (Wlong)/2;
			}
	} else if(m_mirrorx==1 && m_r==0) {
		if(_net==1) {
			Wlong= (m_w2>m_w4) ? m_w2 : m_w4;
			xstep= - (Wlong)/2;
			ystep=0;
		} else if(_net==2) {
			Wlong= (m_w1>m_w3) ? m_w1 : m_w3;
			xstep=0;
			ystep= + (Wlong)/2;
		} else if(_net==3) {
			Wlong= (m_w2>m_w4) ? m_w2 : m_w4;
			xstep= + (Wlong)/2;
			ystep=0;
		} else if(_net==4) {
			Wlong= (m_w1>m_w3) ? m_w1 : m_w3;
			xstep=0;
			ystep= - (Wlong)/2;
			}
	} else if(m_mirrorx==1 && m_r==90) {
		if(_net==1) {
			Wlong= (m_w2>m_w4) ? m_w2 : m_w4;
			xstep=0;
			ystep= + (Wlong)/2;
		} else if(_net==2) {
			Wlong= (m_w1>m_w3) ? m_w1 : m_w3;
			xstep= + (Wlong)/2;
			ystep=0;
		} else if(_net==3) {
			Wlong= (m_w2>m_w4) ? m_w2 : m_w4;
			xstep=0;
			ystep= - (Wlong)/2;
		} else if(_net==4) {
			Wlong= (m_w1>m_w3) ? m_w1 : m_w3;
			ystep=0;
			xstep= - (Wlong)/2;
			}
	} else if(m_mirrorx==1 && m_r==180) {
		if(_net==1) {
			Wlong= (m_w2>m_w4) ? m_w2 : m_w4;
			xstep= + (Wlong)/2;
			ystep=0;
		} else if(_net==2) {
			Wlong= (m_w1>m_w3) ? m_w1 : m_w3;
			xstep=0;
			ystep= - (Wlong)/2;
		} else if(_net==3) {
			Wlong= (m_w2>m_w4) ? m_w2 : m_w4;
			xstep= - (Wlong)/2;
			ystep=0;
		} else if(_net==4) {
			Wlong= (m_w1>m_w3) ? m_w1 : m_w3;
			xstep=0;
			ystep= + (Wlong)/2;
			}
	} else if(m_mirrorx==1 && m_r==270) {
		if(_net==1) {
			Wlong= (m_w2>m_w4) ? m_w2 : m_w4;
			xstep=0;
			ystep= - (Wlong)/2;
		} else if(_net==2) {
			Wlong= (m_w1>m_w3) ? m_w1 : m_w3;
			xstep= - (Wlong)/2;
			ystep=0;
		} else if(_net==3) {
			Wlong= (m_w2>m_w4) ? m_w2 : m_w4;
			xstep=0;
			ystep= + (Wlong)/2;
		} else if(_net==4) {
			Wlong= (m_w1>m_w3) ? m_w1 : m_w3;
			ystep=0;
			xstep= + (Wlong)/2;
			}
		}
	}
