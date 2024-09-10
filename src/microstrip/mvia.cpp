///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#include "mvia.hpp"
using namespace std;

//******************************************************************************
string const Mvia::m_descriptor("microstrip_via");

//******************************************************************************
Mvia::Mvia(string _label,
			string _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			string _subst,
			long double const _d) :
	Element(std::move(_label), std::move(_type), _active, _mirrorx, _r, 1, std::move(_subst)),
	m_d(_d)
	{}

//******************************************************************************
string Mvia::getDescriptor() const {
	return m_descriptor;
	}

//******************************************************************************
long double Mvia::getD() const {
	return m_d;
	}

//******************************************************************************
string Mvia::getNet1() const {
	return m_net1;
	}

//******************************************************************************
int Mvia::setNet1(string const& _net1) {
	m_net1=_net1;
	return 0;
	}

//******************************************************************************
void Mvia::getEdge(int const /*_net*/, long double& edge, short& dir) const {
	edge=m_d;
	switch(m_r) {
		case 0: dir=XMIN; break;
		case 90: dir=YMAX; break;
		case 180: dir=XMAX; break;
		case 270: dir=YMIN; break;
		}
	}

//******************************************************************************
int Mvia::getOemsNcorelines() const {
	return 3;
	}

//******************************************************************************
int Mvia::getOemsMeshCore(int const _n, OemsLine& line) const {
	if(_n==0) {
		switch(m_r) {
			case 0:   line.position=m_y+m_d/2; line.direction=YMAX; break;
			case 90:  line.position=m_x+m_d/2; line.direction=XMAX; break;
			case 180: line.position=m_y-m_d/2; line.direction=YMIN; break;
			case 270: line.position=m_x-m_d/2; line.direction=XMIN; break;
			}
	} else if(_n==1) {
		switch(m_r) {
			case 0:   line.position=m_x+m_d/2; line.direction=XMAX; break;
			case 90:  line.position=m_y-m_d/2; line.direction=YMIN; break;
			case 180: line.position=m_x-m_d/2; line.direction=XMIN; break;
			case 270: line.position=m_y+m_d/2; line.direction=YMAX; break;
			}
	} else if(_n==2) {
		switch(m_r) {
			case 0:   line.position=m_y-m_d/2; line.direction=YMIN; break;
			case 90:  line.position=m_x-m_d/2; line.direction=XMIN; break;
			case 180: line.position=m_y+m_d/2; line.direction=YMAX; break;
			case 270: line.position=m_x+m_d/2; line.direction=XMAX; break;
			}
	} else {
		return 1;
		}

	line.label=m_label;
	line.type=m_type;
	line.third_rule=true;
	return 0;
	}

//******************************************************************************
int Mvia::getOemsMeshInterface(int const _net, OemsLine& line) const {
	if(_net==1
	&&(adjacent1.first==nullptr
	||(adjacent1.first!=nullptr && adjacent1.first->isOemsMeshInterface(adjacent1.second, m_d)))) {
		switch(m_r) {
			case 0:   line.position=m_x-m_d/2; line.direction=XMIN; break;
			case 90:  line.position=m_y+m_d/2; line.direction=YMAX; break;
			case 180: line.position=m_x+m_d/2; line.direction=XMAX; break;
			case 270: line.position=m_y-m_d/2; line.direction=YMIN; break;
			}
	} else {
		return 1;
		}

	line.label=m_label;
	line.type=m_type;
	line.third_rule=true;
	return 0;
	}

//******************************************************************************
bool Mvia::isOemsMeshInterface(int const _port, long double const _w) const {
	if(_port==1) {
		return(_w>m_d ? true : false);
	} else {
		return false;
		}
	}

//******************************************************************************
int Mvia::setAdjacent(int const _port, Element* adjacent, int const adjacent_port) {
	switch(_port) {
		case 1: adjacent1={ adjacent, adjacent_port }; break;
		default: return 1;
		}
	return 0;
	}
