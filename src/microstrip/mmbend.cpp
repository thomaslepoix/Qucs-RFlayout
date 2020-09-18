/***************************************************************************
                               mmbend.cpp
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

#include "mmbend.hpp"
using namespace std;

//******************************************************************************
Mmbend::Mmbend(string _label,
			string _type,
			bool _active,
			bool _mirrorx,
			short _r,
			string _subst,
			long double _w) :
	Element(_label, _type, _active, _mirrorx, _r, 2, _subst),
	m_w(_w)
	{}

//******************************************************************************
string Mmbend::getDescriptor(void) {
	return(m_descriptor);
	}

//******************************************************************************
long double Mmbend::getW(void) {
	return(m_w);
	}

//******************************************************************************
string Mmbend::getNet1(void) {
	return(m_net1);
	}

//******************************************************************************
string Mmbend::getNet2(void) {
	return(m_net2);
	}

//******************************************************************************
int Mmbend::getNpoint(void) {
	return(m_npoint);
	}

//******************************************************************************
long double Mmbend::getP(int const _n, axis_t const _xy, orientation_t const _r, origin_t const _abs, bool const /*apply_shift*/) {
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
int Mmbend::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

//******************************************************************************
int Mmbend::setNet2(string _net2) {
	m_net2=_net2;
	return(0);
	}

//******************************************************************************
int Mmbend::setP(void) {
	signed short s1; //= m_mirror ? -1 :  1;
	signed short s2; //= m_mirror ?  1 : -1;
	if(m_mirrorx) {
		s1=-1;
		s2= 1;
	} else {
		s1= 1;
		s2=-1;
		}
	tab_p[0][X]=  -m_w/2;
	tab_p[0][Y]=s1*m_w/2;
	tab_p[1][X]=   m_w/2;
	tab_p[1][Y]=s1*m_w/2;
	tab_p[2][X]=  -m_w/2;
	tab_p[2][Y]=s2*m_w/2;
	return(0);
	}

//******************************************************************************
void Mmbend::getStep(int const _net, long double& xstep, long double& ystep) {
	if(m_mirrorx==0 && m_r==0) {
		if(_net==1) {
			xstep= - m_w/2;
			ystep=0;
		} else if(_net==2) {
			xstep=0;
			ystep= + m_w/2;
			}
	} else if(m_mirrorx==0 && m_r==90) {
		if(_net==1) {
			xstep=0;
			ystep= + m_w/2;
		} else if(_net==2) {
			xstep= + m_w/2;
			ystep=0;
			}
	} else if(m_mirrorx==0 && m_r==180) {
		if(_net==1) {
			xstep= + m_w/2;
			ystep=0;
		} else if(_net==2) {
			xstep=0;
			ystep= - m_w/2;
			}
	} else if(m_mirrorx==0 && m_r==270) {
		if(_net==1) {
			xstep=0;
			ystep= - m_w/2;
		} else if(_net==2) {
			xstep= - m_w/2;
			ystep=0;
			}
	} else if(m_mirrorx==1 && m_r==0) {
		if(_net==1) {
			xstep= - m_w/2;
			ystep=0;
		} else if(_net==2) {
			xstep=0;
			ystep= - m_w/2;
			}
	} else if(m_mirrorx==1 && m_r==90) {
		if(_net==1) {
			xstep=0;
			ystep= + m_w/2;
		} else if(_net==2) {
			xstep= - m_w/2;
			ystep=0;
			}
	} else if(m_mirrorx==1 && m_r==180) {
		if(_net==1) {
			xstep= + m_w/2;
			ystep=0;
		} else if(_net==2) {
			xstep=0;
			ystep= + m_w/2;
			}
	} else if(m_mirrorx==1 && m_r==270) {
		if(_net==1) {
			xstep=0;
			ystep= - m_w/2;
		} else if(_net==2) {
			xstep= + m_w/2;
			ystep=0;
			}
		}
	}

//******************************************************************************
void Mmbend::getEdge(int const _net, long double& edge, short& dir) {
	edge=m_w;
	if(_net==1) {
		switch(m_r) {
			case 0: dir=XMIN; break;
			case 90: dir=YMAX; break;
			case 180: dir=XMAX; break;
			case 270: dir=YMIN; break;
			}
	} else if(_net==2) {
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
	}

//******************************************************************************
int Mmbend::getOemsNcorelines(void) {
	return(4);
	}

//******************************************************************************
int Mmbend::getOemsMeshCore(int const _n, OemsLine& line) {
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
			case 0:   line.position=getP(1, X, R, ABS); line.direction=XMAX; break;
			case 90:  line.position=getP(1, Y, R, ABS); line.direction=YMIN; break;
			case 180: line.position=getP(1, X, R, ABS); line.direction=XMIN; break;
			case 270: line.position=getP(1, Y, R, ABS); line.direction=YMAX; break;
			}
	} else if(_n==2) {
		if(m_mirrorx==0) {
			switch(m_r) {
				case 0:   line.position=getP(2, Y, R, ABS); line.direction=YMIN; break;
				case 90:  line.position=getP(2, X, R, ABS); line.direction=XMIN; break;
				case 180: line.position=getP(2, Y, R, ABS); line.direction=YMAX; break;
				case 270: line.position=getP(2, X, R, ABS); line.direction=XMAX; break;
				}
		} else {
			switch(m_r) {
				case 0:   line.position=getP(2, Y, R, ABS); line.direction=YMAX; break;
				case 90:  line.position=getP(2, X, R, ABS); line.direction=XMAX; break;
				case 180: line.position=getP(2, Y, R, ABS); line.direction=YMIN; break;
				case 270: line.position=getP(2, X, R, ABS); line.direction=XMIN; break;
				}
			}
	} else if(_n==3) {
		switch(m_r) {
			case 0:   line.position=getP(0, X, R, ABS); line.direction=XMIN; break;
			case 90:  line.position=getP(0, Y, R, ABS); line.direction=YMAX; break;
			case 180: line.position=getP(0, X, R, ABS); line.direction=XMAX; break;
			case 270: line.position=getP(0, Y, R, ABS); line.direction=YMIN; break;
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
bool Mmbend::isOemsMeshInterface(int const _port, long double const _w) {
	if(_port==1 || _port==2) {
		return(_w>m_w ? true : false);
	} else {
		return(false);
		}
	}
