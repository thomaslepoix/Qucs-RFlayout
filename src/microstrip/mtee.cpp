///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#include "mtee.hpp"
using namespace std;

//******************************************************************************
string const Mtee::m_descriptor("microstrip_tee");

//******************************************************************************
Mtee::Mtee(string _label,
			string _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			string _subst,
			long double const _w1,
			long double const _w2,
			long double const _w3) :
	Element(std::move(_label), std::move(_type), _active, _mirrorx, _r, 3, std::move(_subst)),
	m_w1(_w1),
	m_w2(_w2),
	m_w3(_w3)
	{}

//******************************************************************************
string Mtee::getDescriptor() const {
	return(m_descriptor);
	}

//******************************************************************************
long double Mtee::getW1() const {
	return(m_w1);
	}

//******************************************************************************
long double Mtee::getW2() const {
	return(m_w2);
	}

//******************************************************************************
long double Mtee::getW3() const {
	return(m_w3);
	}

//******************************************************************************
string Mtee::getNet1() const {
	return(m_net1);
	}

//******************************************************************************
string Mtee::getNet2() const {
	return(m_net2);
	}

//******************************************************************************
string Mtee::getNet3() const {
	return(m_net3);
	}

//******************************************************************************
int Mtee::getNpoint() const {
	return(m_npoint);
	}

//******************************************************************************
long double Mtee::getP(int const _n, axis_t const _xy, orientation_t const _r, origin_t const _abs, bool const /*apply_shift*/) const {
	long double coord;
	if(_r) {
		coord= _xy ? rotateY(tab_p[_n][0], tab_p[_n][1])
		           : rotateX(tab_p[_n][0], tab_p[_n][1]);
	} else {
		coord=tab_p[_n][_xy];
		}
	return(_abs ? coord+(_xy ? m_y : m_x) : coord);
	}

//******************************************************************************
int Mtee::setNet1(string const& _net1) {
	m_net1=_net1;
	return(0);
	}

//******************************************************************************
int Mtee::setNet2(string const& _net2) {
	m_net2=_net2;
	return(0);
	}

//******************************************************************************
int Mtee::setNet3(string const& _net3) {
	m_net3=_net3;
	return(0);
	}

//******************************************************************************
int Mtee::setP() {
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

//******************************************************************************
void Mtee::getStep(int const _net, long double& xstep, long double& ystep) const {
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

//******************************************************************************
void Mtee::getEdge(int const _net, long double& edge, short& dir) const {
	if(_net==1) {
		edge=m_w1;
		switch(m_r) {
			case 0: dir=XMIN; break;
			case 90: dir=YMAX; break;
			case 180: dir=XMAX; break;
			case 270: dir=YMIN; break;
			}
	} else if(_net==2) {
		edge=m_w2;
		switch(m_r) {
			case 0: dir=XMAX; break;
			case 90: dir=YMIN; break;
			case 180: dir=XMIN; break;
			case 270: dir=YMAX; break;
			}
	} else if(_net==3) {
		edge=m_w3;
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
int Mtee::getOemsNcorelines() const {
	if(m_w1==m_w2){
		return(1);
	} else {
		return(3);
		}
	}

//******************************************************************************
int Mtee::getOemsMeshCore(int const _n, OemsLine& line) const {
	if(_n==0) {
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
	} else if(_n==1) {
		switch(m_r) {
			case 0:   line.position=getP(4, X, R, ABS); line.direction=(m_w1>m_w2 ? XMAX : XMIN); break;
			case 90:  line.position=getP(4, Y, R, ABS); line.direction=(m_w1>m_w2 ? YMIN : YMAX); break;
			case 180: line.position=getP(4, X, R, ABS); line.direction=(m_w1>m_w2 ? XMIN : XMAX); break;
			case 270: line.position=getP(4, Y, R, ABS); line.direction=(m_w1>m_w2 ? YMAX : YMIN); break;
			}
	} else if(_n==2) {
		if(m_mirrorx==0) {
			switch(m_r) {
				case 0:   line.position=getP(5, Y, R, ABS); line.direction=YMIN; break;
				case 90:  line.position=getP(5, X, R, ABS); line.direction=XMIN; break;
				case 180: line.position=getP(5, Y, R, ABS); line.direction=YMAX; break;
				case 270: line.position=getP(5, X, R, ABS); line.direction=XMAX; break;
				}
		} else if(m_mirrorx==1) {
			switch(m_r) {
				case 0:   line.position=getP(5, Y, R, ABS); line.direction=YMAX; break;
				case 90:  line.position=getP(5, X, R, ABS); line.direction=XMAX; break;
				case 180: line.position=getP(5, Y, R, ABS); line.direction=YMIN; break;
				case 270: line.position=getP(5, X, R, ABS); line.direction=XMIN; break;
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
int Mtee::getOemsMeshInterface(int const _net, OemsLine& line) const {
	if(_net==1
	&&(adjacent1.first==nullptr
	||(adjacent1.first!=nullptr && adjacent1.first->isOemsMeshInterface(adjacent1.second, m_w1)))) {
		switch(m_r) {
			case 0:   line.position=getP(0, X, R, ABS); line.direction=XMIN; break;
			case 90:  line.position=getP(0, Y, R, ABS); line.direction=YMAX; break;
			case 180: line.position=getP(0, X, R, ABS); line.direction=XMAX; break;
			case 270: line.position=getP(0, Y, R, ABS); line.direction=YMIN; break;
			}
	} else if(_net==2
	       &&(adjacent2.first==nullptr
	       ||(adjacent2.first!=nullptr && adjacent2.first->isOemsMeshInterface(adjacent2.second, m_w2)))) {
		switch(m_r) {
			case 0:   line.position=getP(2, X, R, ABS); line.direction=XMAX; break;
			case 90:  line.position=getP(2, Y, R, ABS); line.direction=YMIN; break;
			case 180: line.position=getP(2, X, R, ABS); line.direction=XMIN; break;
			case 270: line.position=getP(2, Y, R, ABS); line.direction=YMAX; break;
			}
	} else if(_net==3
	       &&(adjacent3.first==nullptr
	       ||(adjacent3.first!=nullptr && adjacent3.first->isOemsMeshInterface(adjacent3.second, m_w3)))) {
		if(m_mirrorx==0) {
			switch(m_r) {
				case 0:   line.position=getP(0, Y, R, ABS); line.direction=YMAX; break;
				case 90:  line.position=getP(0, X, R, ABS); line.direction=XMAX; break;
				case 180: line.position=getP(0, Y, R, ABS); line.direction=YMIN; break;
				case 270: line.position=getP(0, X, R, ABS); line.direction=XMIN; break;
				}
		} else if(m_mirrorx==1) {
			switch(m_r) {
				case 0:   line.position=getP(0, Y, R, ABS); line.direction=YMAX; break;
				case 90:  line.position=getP(0, X, R, ABS); line.direction=XMAX; break;
				case 180: line.position=getP(0, Y, R, ABS); line.direction=YMIN; break;
				case 270: line.position=getP(0, X, R, ABS); line.direction=XMIN; break;
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
bool Mtee::isOemsMeshInterface(int const _port, long double const _w) const {
	if(_port==1) {
		return(_w>m_w1 ? true : false);
	} else if(_port==2) {
		return(_w>m_w2 ? true : false);
	} else if(_port==3) {
		return(_w>m_w3 ? true : false);
	} else {
		return(false);
		}
	}

//******************************************************************************
int Mtee::setAdjacent(int const _port, shared_ptr<Element> const& adjacent, int const adjacent_port) {
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
		default:
			return(1);
		}
	return(0);
	}
