///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#include "mstep.hpp"
using namespace std;

//******************************************************************************
string const Mstep::m_descriptor("microstrip_step");

//******************************************************************************
Mstep::Mstep(string _label,
			string _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			string _subst,
			long double const _w1,
			long double const _w2) :
	Element(std::move(_label), std::move(_type), _active, _mirrorx, _r, 2, std::move(_subst)),
	m_w1(_w1),
	m_w2(_w2)
	{}

//******************************************************************************
string Mstep::getDescriptor() const {
	return(m_descriptor);
	}

//******************************************************************************
long double Mstep::getW1() const {
	return(m_w1);
	}

//******************************************************************************
long double Mstep::getW2() const {
	return(m_w2);
	}

//******************************************************************************
string Mstep::getNet1() const {
	return(m_net1);
	}

//******************************************************************************
string Mstep::getNet2() const {
	return(m_net2);
	}

//******************************************************************************
int Mstep::setNet1(string const& _net1) {
	m_net1=_net1;
	return(0);
	}

//******************************************************************************
int Mstep::setNet2(string const& _net2) {
	m_net2=_net2;
	return(0);
	}

//******************************************************************************
void Mstep::getEdge(int const _net, long double& edge, short& dir) const {
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
		}
	}

//******************************************************************************
int Mstep::getOemsNcorelines() const {
	return(1);
	}

//******************************************************************************
int Mstep::getOemsMeshCore(int const _n, OemsLine& line) const {
	if(_n!=0 || m_w1==m_w2)
		return(1);

	bool is_w1_longer;
	if(adjacent1.first!=nullptr
	&& adjacent2.first!=nullptr) {
		is_w1_longer=(m_w1>m_w2 ? true : false);
	} else if(adjacent1.first!=nullptr
	       && adjacent2.first==nullptr) {
		is_w1_longer=true;
	} else if(adjacent1.first==nullptr
	       && adjacent2.first!=nullptr) {
		is_w1_longer=false;
		}

	switch(m_r) {
		case 0:
			line.position=m_x;
			line.direction=(is_w1_longer ? XMAX : XMIN);
			break;
		case 90:
			line.position=m_y;
			line.direction=(is_w1_longer ? YMIN : YMAX);
			break;
		case 180:
			line.position=m_x;
			line.direction=(is_w1_longer ? XMIN : XMAX);
			break;
		case 270:
			line.position=m_y;
			line.direction=(is_w1_longer ? YMAX : YMIN);
			break;
		}

	line.label=m_label;
	line.type=m_type;
	line.third_rule=true;
	return(0);
	}

//******************************************************************************
int Mstep::setAdjacent(int const _port, shared_ptr<Element> const& adjacent, int const adjacent_port) {
	switch(_port) {
		case 1: adjacent1={ adjacent, adjacent_port }; break;
		case 2: adjacent2={ adjacent, adjacent_port }; break;
		default: return(1);
		}
	return(0);
	}
