/***************************************************************************
                               mcross.cpp
                             ------------------
    begin                : Thu Oct 25 2018
    copyright            : (C) 2018 by Thomas Lepoix
    email                : thomas.lepoix@gmail.com
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

long double Mcross::getP(int _n, bool _xy, bool _r, bool _abs) {
	long double coord;
	if(_r) {
		coord= _xy ? rotateY(tab_p[_n][0], tab_p[_n][1]) : rotateX(tab_p[_n][0], tab_p[_n][1]);
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
		tab_p[0][_X]=  -Wlong24/2;
		tab_p[0][_Y]=s1*Wlong13/2;
		tab_p[1][_X]=   Wlong24/2;
		tab_p[1][_Y]=s1*Wlong13/2;
		tab_p[2][_X]=   Wlong24/2;
		tab_p[2][_Y]=s2*Wlong13/2;
		tab_p[3][_X]=  -Wlong24/2;
		tab_p[3][_Y]=s2*Wlong13/2;
	} else {
		if(Wlong13==m_w1 && Wlong24==m_w2) {
			//shape
			// ##
			// #
			tab_p[0][_X]=  -Wlong24/2;
			tab_p[0][_Y]=s1*Wlong13/2;
			tab_p[1][_X]=   Wlong24/2;
			tab_p[1][_Y]=s1*Wlong13/2;
			tab_p[2][_X]=   m_w2/2;
			tab_p[2][_Y]=s2*m_w3/2;
			tab_p[3][_X]=   m_w4/2;
			tab_p[3][_Y]=s2*m_w3/2;
			tab_p[4][_X]=   m_w4/2;
			tab_p[4][_Y]=s2*m_w1/2;
			tab_p[5][_X]=  -Wlong24/2;
			tab_p[5][_Y]=s2*Wlong13/2;
		} else if(Wlong13==m_w1 && Wlong24==m_w4) {
			//shape
			// #
			// ##
			tab_p[0][_X]=  -Wlong24/2;
			tab_p[0][_Y]=s1*Wlong13/2;
			tab_p[1][_X]=   m_w2/2;
			tab_p[1][_Y]=s1*m_w1/2;
			tab_p[2][_X]=   m_w2/2;
			tab_p[2][_Y]=s1*m_w3/2;
			tab_p[3][_X]=   m_w4/2;
			tab_p[3][_Y]=s1*m_w3/2;
			tab_p[4][_X]=   Wlong24/2;
			tab_p[4][_Y]=s2*Wlong13/2;
			tab_p[5][_X]=  -Wlong24/2;
			tab_p[5][_Y]=s2*Wlong13/2;
		} else if(Wlong13==m_w3 && Wlong24==m_w4) {
			//shape
			//  #
			// ##
			tab_p[0][_X]=  -m_w4/2;
			tab_p[0][_Y]=s1*m_w1/2;
			tab_p[1][_X]=  -m_w2/2;
			tab_p[1][_Y]=s1*m_w1/2;
			tab_p[2][_X]=  -m_w2/2;
			tab_p[2][_Y]=s1*m_w3/2;
			tab_p[3][_X]=   Wlong24/2;
			tab_p[3][_Y]=s1*Wlong13/2;
			tab_p[4][_X]=   Wlong24/2;
			tab_p[4][_Y]=s2*Wlong13/2;
			tab_p[5][_X]=  -Wlong24/2;
			tab_p[5][_Y]=s2*Wlong13/2;
		} else if(Wlong13==m_w3 && Wlong24==m_w2) {
			//shape
			// ##
			//  #
			tab_p[0][_X]=  -Wlong24/2;
			tab_p[0][_Y]=s1*Wlong13/2;
			tab_p[1][_X]=   Wlong24/2;
			tab_p[1][_Y]=s1*Wlong13/2;
			tab_p[2][_X]=   Wlong24/2;
			tab_p[2][_Y]=s2*Wlong13/2;
			tab_p[3][_X]=  -m_w4/2;
			tab_p[3][_Y]=s2*m_w3/2;
			tab_p[4][_X]=  -m_w4/2;
			tab_p[4][_Y]=s2*m_w1/2;
			tab_p[5][_X]=  -m_w2/2;
			tab_p[5][_Y]=s2*m_w1/2;
			}
		}
	return(0);
	}

////////////////////////////////////////////////////////////////////////////////

long double Mcross::getW(void) {
	return(0);
	}
long double Mcross::getL(void) {
	return(0);
	}
long double Mcross::getD(void) {
	return(0);
	}
long double Mcross::getS(void) {
	return(0);
	}
long double Mcross::getRi(void) {
	return(0);
	}
long double Mcross::getRo(void) {
	return(0);
	}
short Mcross::getAlpha(void) {
	return(0);
	}
