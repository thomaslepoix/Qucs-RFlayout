///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#include "mcorn.hpp"
using namespace std;

//******************************************************************************
string const Mcorn::m_descriptor("microstrip_corner");

//******************************************************************************
Mcorn::Mcorn(string _label,
			string _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			string _subst,
			long double const _w) :
	Element(std::move(_label), std::move(_type), _active, _mirrorx, _r, 2, std::move(_subst)),
	m_w(_w)
	{}

//******************************************************************************
string Mcorn::getDescriptor() const {
	return(m_descriptor);
	}

//******************************************************************************
long double Mcorn::getW() const {
	return(m_w);
	}

//******************************************************************************
string Mcorn::getNet1() const {
	return(m_net1);
	}

//******************************************************************************
string Mcorn::getNet2() const {
	return(m_net2);
	}

//******************************************************************************
int Mcorn::getNpoint() const {
	return(m_npoint);
	}

//******************************************************************************
long double Mcorn::getP(int const _n, axis_t const _xy, orientation_t const /*_r*/, origin_t const _abs, bool const /*apply_shift*/) const {
	return(_abs ? tab_p[_n][_xy]+(_xy ? m_y : m_x) : tab_p[_n][_xy]);
	}

//******************************************************************************
int Mcorn::setNet1(string const& _net1) {
	m_net1=_net1;
	return(0);
	}

//******************************************************************************
int Mcorn::setNet2(string const& _net2) {
	m_net2=_net2;
	return(0);
	}

//******************************************************************************
int Mcorn::setP() {
	tab_p[0][X]=-m_w/2;
	tab_p[0][Y]= m_w/2;
	tab_p[1][X]= m_w/2;
	tab_p[1][Y]= m_w/2;
	tab_p[2][X]= m_w/2;
	tab_p[2][Y]=-m_w/2;
	tab_p[3][X]=-m_w/2;
	tab_p[3][Y]=-m_w/2;
	return(0);
	}

//******************************************************************************
void Mcorn::getStep(int const _net, long double& xstep, long double& ystep) const {
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
void Mcorn::getEdge(int const _net, long double& edge, short& dir) const {
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
int Mcorn::getOemsNcorelines() const {
	return(2);
	}

//******************************************************************************
int Mcorn::getOemsMeshCore(int const _n, OemsLine& line) const {
	if(_n==0) {
		switch(m_r) {
			case 0:   line.position=getP(2, X, R, ABS); line.direction=XMAX; break;
			case 90:  line.position=getP(2, Y, R, ABS); line.direction=YMIN; break;
			case 180: line.position=getP(2, X, R, ABS); line.direction=XMIN; break;
			case 270: line.position=getP(2, Y, R, ABS); line.direction=YMAX; break;
			}
	} else if(_n==1) {
		if(m_mirrorx==0) {
			switch(m_r) {
				case 0:   line.position=getP(2, Y, R, ABS); line.direction=YMIN; break;
				case 90:  line.position=getP(2, X, R, ABS); line.direction=XMIN; break;
				case 180: line.position=getP(2, Y, R, ABS); line.direction=YMAX; break;
				case 270: line.position=getP(2, X, R, ABS); line.direction=XMAX; break;
				}
		} else if(m_mirrorx==1) {
			switch(m_r) {
				case 0:   line.position=getP(2, Y, R, ABS); line.direction=YMAX; break;
				case 90:  line.position=getP(2, X, R, ABS); line.direction=XMAX; break;
				case 180: line.position=getP(2, Y, R, ABS); line.direction=YMIN; break;
				case 270: line.position=getP(2, X, R, ABS); line.direction=XMIN; break;
				}
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
int Mcorn::getOemsMeshInterface(int const _net, OemsLine& line) const {
	if(_net==1
	&&(adjacent1.first==nullptr
	||(adjacent1.first!=nullptr && adjacent1.first->isOemsMeshInterface(adjacent1.second, m_w)))) {
		switch(m_r) {
			case 0:   line.position=getP(0, X, R, ABS); line.direction=XMIN; break;
			case 90:  line.position=getP(0, Y, R, ABS); line.direction=YMAX; break;
			case 180: line.position=getP(0, X, R, ABS); line.direction=XMAX; break;
			case 270: line.position=getP(0, Y, R, ABS); line.direction=YMIN; break;
			}
	} else if(_net==2
	       &&(adjacent2.first==nullptr
	       ||(adjacent2.first!=nullptr && adjacent2.first->isOemsMeshInterface(adjacent2.second, m_w)))) {
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
	} else {
		return(1);
		}

	line.label=m_label;
	line.type=m_type;
	line.third_rule=true;
	return(0);
	}

//******************************************************************************
bool Mcorn::isOemsMeshInterface(int const _port, long double const _w) const {
	if(_port==1 || _port==2) {
		return(_w>m_w ? true : false);
	} else {
		return(false);
		}
	}

//******************************************************************************
int Mcorn::setAdjacent(int const _port, shared_ptr<Element> const& adjacent, int const adjacent_port) {
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
