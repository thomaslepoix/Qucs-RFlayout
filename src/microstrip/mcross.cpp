///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#include "mcross.hpp"
using namespace std;

//******************************************************************************
string const Mcross::m_descriptor("microstrip_cross");

//******************************************************************************
Mcross::Mcross(string _label,
			string _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			string _subst,
			long double const _w1,
			long double const _w2,
			long double const _w3,
			long double const _w4) :
	Element(std::move(_label), std::move(_type), _active, _mirrorx, _r, 4, std::move(_subst)),
	m_w1(_w1),
	m_w2(_w2),
	m_w3(_w3),
	m_w4(_w4)
	{}

//******************************************************************************
string Mcross::getDescriptor() const {
	return(m_descriptor);
	}

//******************************************************************************
long double Mcross::getW1() const {
	return(m_w1);
	}

//******************************************************************************
long double Mcross::getW2() const {
	return(m_w2);
	}

//******************************************************************************
long double Mcross::getW3() const {
	return(m_w3);
	}

//******************************************************************************
long double Mcross::getW4() const {
	return(m_w4);
	}

//******************************************************************************
string Mcross::getNet1() const {
	return(m_net1);
	}

//******************************************************************************
string Mcross::getNet2() const {
	return(m_net2);
	}

//******************************************************************************
string Mcross::getNet3() const {
	return(m_net3);
	}

//******************************************************************************
string Mcross::getNet4() const {
	return(m_net4);
	}

//******************************************************************************
int Mcross::getNpoint() const {
	return(m_npoint);
	}

//******************************************************************************
long double Mcross::getP(int const _n, axis_t const _xy, orientation_t const _r, origin_t const _abs, bool const /*apply_shift*/) const {
	long double coord;
	if(_r) {
		coord= _xy ? rotateY(tab_p[_n][X], tab_p[_n][Y])
		           : rotateX(tab_p[_n][X], tab_p[_n][Y]);
	} else {
		coord=tab_p[_n][_xy];
		}
	return(_abs ? coord+(_xy ? m_y : m_x) : coord);
	}

int Mcross::setNet1(string const& _net1) {
	m_net1=_net1;
	return(0);
	}

int Mcross::setNet2(string const& _net2) {
	m_net2=_net2;
	return(0);
	}

int Mcross::setNet3(string const& _net3) {
	m_net3=_net3;
	return(0);
	}

int Mcross::setNet4(string const& _net4) {
	m_net4=_net4;
	return(0);
	}

//******************************************************************************
int Mcross::setP() {
// TODO 0 at bottom left, counter clockwise
// instead of 0 at top left, clockwise
	signed short s1;
	signed short s2;
	long double Wlong13= (m_w1>m_w3) ? m_w1 : m_w3;
	long double Wlong24= (m_w2>m_w4) ? m_w2 : m_w4;
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

//******************************************************************************
void Mcross::getStep(int const _net, long double& xstep, long double& ystep) const {
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

//******************************************************************************
void Mcross::getEdge(int const _net, long double& edge, short& dir) const {
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
		if(m_mirrorx==0) {
			switch(m_r) {
				case 0: dir=YMIN; break;
				case 90: dir=XMIN; break;
				case 180: dir=YMAX; break;
				case 270: dir=XMAX; break;
				}
		} else if(m_mirrorx==1) {
			switch(m_r) {
				case 0: dir=YMAX; break;
				case 90: dir=XMAX; break;
				case 180: dir=YMIN; break;
				case 270: dir=XMIN; break;
				}
			}
	} else if(_net==3) {
		edge=m_w3;
		switch(m_r) {
			case 0: dir=XMAX; break;
			case 90: dir=YMIN; break;
			case 180: dir=XMIN; break;
			case 270: dir=YMAX; break;
			}
	} else if(_net==4) {
		edge=m_w4;
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
int Mcross::getOemsNcorelines() const {
	if(m_w1==m_w3 || m_w2==m_w4){
		return(0);
	} else {
		return(2);
		}
	}

//******************************************************************************
int Mcross::getOemsMeshCore(int const _n, OemsLine& line) const {
	if(_n==0) {
		if(m_w1>m_w3 && m_w2>m_w4) {
			if(m_mirrorx==0) {
				switch(m_r) {
					case 0:   line.position=getP(3, Y, R, ABS); line.direction=YMAX; break;
					case 90:  line.position=getP(3, X, R, ABS); line.direction=XMAX; break;
					case 180: line.position=getP(3, Y, R, ABS); line.direction=YMIN; break;
					case 270: line.position=getP(3, X, R, ABS); line.direction=XMIN; break;
					}
			} else if(m_mirrorx==1) {
				switch(m_r) {
					case 0:   line.position=getP(3, Y, R, ABS); line.direction=YMIN; break;
					case 90:  line.position=getP(3, X, R, ABS); line.direction=XMIN; break;
					case 180: line.position=getP(3, Y, R, ABS); line.direction=YMAX; break;
					case 270: line.position=getP(3, X, R, ABS); line.direction=XMAX; break;
					}
				}
		} else if(m_w1>m_w3 && m_w2<m_w4) {
			switch(m_r) {
				case 0:   line.position=getP(2, X, R, ABS); line.direction=XMAX; break;
				case 90:  line.position=getP(2, Y, R, ABS); line.direction=YMIN; break;
				case 180: line.position=getP(2, X, R, ABS); line.direction=XMIN; break;
				case 270: line.position=getP(2, Y, R, ABS); line.direction=YMAX; break;
				}
		} else if(m_w1<m_w3 && m_w2<m_w4) {
			if(m_mirrorx==0) {
				switch(m_r) {
					case 0:   line.position=getP(1, Y, R, ABS); line.direction=YMIN; break;
					case 90:  line.position=getP(1, X, R, ABS); line.direction=XMIN; break;
					case 180: line.position=getP(1, Y, R, ABS); line.direction=YMAX; break;
					case 270: line.position=getP(1, X, R, ABS); line.direction=XMAX; break;
					}
			} else if(m_mirrorx==1) {
				switch(m_r) {
					case 0:   line.position=getP(1, Y, R, ABS); line.direction=YMAX; break;
					case 90:  line.position=getP(1, X, R, ABS); line.direction=XMAX; break;
					case 180: line.position=getP(1, Y, R, ABS); line.direction=YMIN; break;
					case 270: line.position=getP(1, X, R, ABS); line.direction=XMIN; break;
					}
				}
		} else if(m_w1<m_w3 && m_w2>m_w4) {
			switch(m_r) {
				case 0:   line.position=getP(4, X, R, ABS); line.direction=XMIN; break;
				case 90:  line.position=getP(4, Y, R, ABS); line.direction=YMAX; break;
				case 180: line.position=getP(4, X, R, ABS); line.direction=XMAX; break;
				case 270: line.position=getP(4, Y, R, ABS); line.direction=YMIN; break;
				}
		} else {
			return(1);
			}
	} else if(_n==1) {
		if(m_w1>m_w3 && m_w2>m_w4) {
			switch(m_r) {
				case 0:   line.position=getP(3, X, R, ABS); line.direction=XMAX; break;
				case 90:  line.position=getP(3, Y, R, ABS); line.direction=YMIN; break;
				case 180: line.position=getP(3, X, R, ABS); line.direction=XMIN; break;
				case 270: line.position=getP(3, Y, R, ABS); line.direction=YMAX; break;
				}
		} else if(m_w1>m_w3 && m_w2<m_w4) {
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
		} else if(m_w1<m_w3 && m_w2<m_w4) {
			switch(m_r) {
				case 0:   line.position=getP(1, X, R, ABS); line.direction=XMIN; break;
				case 90:  line.position=getP(1, Y, R, ABS); line.direction=YMAX; break;
				case 180: line.position=getP(1, X, R, ABS); line.direction=XMAX; break;
				case 270: line.position=getP(1, Y, R, ABS); line.direction=YMIN; break;
				}
		} else if(m_w1<m_w3 && m_w2>m_w4) {
			if(m_mirrorx==0) {
				switch(m_r) {
					case 0:   line.position=getP(4, Y, R, ABS); line.direction=YMAX; break;
					case 90:  line.position=getP(4, X, R, ABS); line.direction=XMAX; break;
					case 180: line.position=getP(4, Y, R, ABS); line.direction=YMIN; break;
					case 270: line.position=getP(4, X, R, ABS); line.direction=XMIN; break;
					}
			} else if(m_mirrorx==1) {
				switch(m_r) {
					case 0:   line.position=getP(4, Y, R, ABS); line.direction=YMIN; break;
					case 90:  line.position=getP(4, X, R, ABS); line.direction=XMIN; break;
					case 180: line.position=getP(4, Y, R, ABS); line.direction=YMAX; break;
					case 270: line.position=getP(4, X, R, ABS); line.direction=XMAX; break;
					}
				}
		} else {
			return(1);
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
int Mcross::getOemsMeshInterface(int const _net, OemsLine& line) const {
	long double Wlong13= (m_w1>m_w3) ? m_w1 : m_w3;
	long double Wlong24= (m_w2>m_w4) ? m_w2 : m_w4;

	if(_net==1
	&&(adjacent1.first==nullptr
	||(adjacent1.first!=nullptr
	&& adjacent1.first->isOemsMeshInterface(adjacent1.second, (m_w1==m_w3 || m_w2==m_w4) ? Wlong13 : m_w1)))) {
		switch(m_r) {
			case 0:   line.position=getP(0, X, R, ABS); line.direction=XMIN; break;
			case 90:  line.position=getP(0, Y, R, ABS); line.direction=YMAX; break;
			case 180: line.position=getP(0, X, R, ABS); line.direction=XMAX; break;
			case 270: line.position=getP(0, Y, R, ABS); line.direction=YMIN; break;
			}
	} else if(_net==2
	       &&(adjacent2.first==nullptr
	       ||(adjacent2.first!=nullptr
	       && adjacent2.first->isOemsMeshInterface(adjacent2.second, (m_w1==m_w3 || m_w2==m_w4) ? Wlong24 : m_w2)))) {
		int p=(m_w1<m_w3 && m_w2<m_w4) ? 3 : 1;
		if(m_mirrorx==0) {
			switch(m_r) {
				case 0:   line.position=getP(p, Y, R, ABS); line.direction=YMIN; break;
				case 90:  line.position=getP(p, X, R, ABS); line.direction=XMIN; break;
				case 180: line.position=getP(p, Y, R, ABS); line.direction=YMAX; break;
				case 270: line.position=getP(p, X, R, ABS); line.direction=XMAX; break;
				}
		} else if(m_mirrorx==1) {
			switch(m_r) {
				case 0:   line.position=getP(p, Y, R, ABS); line.direction=YMAX; break;
				case 90:  line.position=getP(p, X, R, ABS); line.direction=XMAX; break;
				case 180: line.position=getP(p, Y, R, ABS); line.direction=YMIN; break;
				case 270: line.position=getP(p, X, R, ABS); line.direction=XMIN; break;
				}
			}
	} else if(_net==3
	       &&(adjacent3.first==nullptr
	       ||(adjacent3.first!=nullptr
	       && adjacent3.first->isOemsMeshInterface(adjacent3.second, (m_w1==m_w3 || m_w2==m_w4) ? Wlong13 : m_w3)))) {
		int p=(m_w1>m_w3 && m_w2<m_w4)
		    ||(m_w1<m_w3 && m_w2<m_w4)
		    ? 3 : 1;
		switch(m_r) {
			case 0:   line.position=getP(p, X, R, ABS); line.direction=XMAX; break;
			case 90:  line.position=getP(p, Y, R, ABS); line.direction=YMIN; break;
			case 180: line.position=getP(p, X, R, ABS); line.direction=XMIN; break;
			case 270: line.position=getP(p, Y, R, ABS); line.direction=YMAX; break;
			}
	} else if(_net==4
	       &&(adjacent4.first==nullptr
	       ||(adjacent4.first!=nullptr
	       && adjacent4.first->isOemsMeshInterface(adjacent4.second, (m_w1==m_w3 || m_w2==m_w4) ? Wlong24 : m_w4)))) {
		int p=(m_w1>m_w3 && m_w2>m_w4)
		    ||(m_w1>m_w3 && m_w2<m_w4)
		    ||(m_w1<m_w3 && m_w2<m_w4)
		    ? 5 : 3;
		if(m_mirrorx==0) {
			switch(m_r) {
				case 0:   line.position=getP(p, Y, R, ABS); line.direction=YMAX; break;
				case 90:  line.position=getP(p, X, R, ABS); line.direction=XMAX; break;
				case 180: line.position=getP(p, Y, R, ABS); line.direction=YMIN; break;
				case 270: line.position=getP(p, X, R, ABS); line.direction=XMIN; break;
				}
		} else if(m_mirrorx==1) {
			switch(m_r) {
				case 0:   line.position=getP(p, Y, R, ABS); line.direction=YMIN; break;
				case 90:  line.position=getP(p, X, R, ABS); line.direction=XMIN; break;
				case 180: line.position=getP(p, Y, R, ABS); line.direction=YMAX; break;
				case 270: line.position=getP(p, X, R, ABS); line.direction=XMAX; break;
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
bool Mcross::isOemsMeshInterface(int const _port, long double const _w) const {
	if(m_w1==m_w3 || m_w2==m_w4) {
		long double Wlong13= (m_w1>m_w3) ? m_w1 : m_w3;
		long double Wlong24= (m_w2>m_w4) ? m_w2 : m_w4;
		switch(_port) {
			case 1: case 3: return(_w>Wlong13 ? true : false);
			case 2: case 4: return(_w>Wlong24 ? true : false);
			default : return(false);
			}
	} else {
		switch(_port) {
			case 1: return(_w>m_w1 ? true : false);
			case 2: return(_w>m_w2 ? true : false);
			case 3: return(_w>m_w3 ? true : false);
			case 4: return(_w>m_w4 ? true : false);
			default: return(false);
			}
		}
	}

//******************************************************************************
int Mcross::setAdjacent(int const _port, shared_ptr<Element> const& adjacent, int const adjacent_port) {
	switch(_port) {
		case 1: adjacent1={ adjacent, adjacent_port }; break;
		case 2: adjacent2={ adjacent, adjacent_port }; break;
		case 3: adjacent3={ adjacent, adjacent_port }; break;
		case 4: adjacent4={ adjacent, adjacent_port }; break;
		default: return(1);
		}
	return(0);
	}
