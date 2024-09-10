///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#include "mopen.hpp"
using namespace std;

//******************************************************************************
string const Mopen::m_descriptor("microstrip_open");

//******************************************************************************
Mopen::Mopen(string _label,
			string _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			string _subst,
			long double const _w) :
	Element(std::move(_label), std::move(_type), _active, _mirrorx, _r, 1, std::move(_subst)),
	m_w(_w)
	{}

//******************************************************************************
string Mopen::getDescriptor() const {
	return m_descriptor;
	}

//******************************************************************************
long double Mopen::getW() const {
	return m_w;
	}

//******************************************************************************
string Mopen::getNet1() const {
	return m_net1;
	}

//******************************************************************************
int Mopen::setNet1(string const& _net1) {
	m_net1=_net1;
	return 0;
	}

//******************************************************************************
void Mopen::getEdge(int const /*_net*/, long double& edge, short& dir) const {
	edge=m_w;
	switch(m_r) {
		case 0: dir=XMIN; break;
		case 90: dir=YMAX; break;
		case 180: dir=XMAX; break;
		case 270: dir=YMIN; break;
		}
	}

//******************************************************************************
bool Mopen::isOemsMeshInterface(int const _port, long double const /*_w*/) const {
	if(_port==1) {
		return true;
	} else {
		return false;
		}
	}

//******************************************************************************
int Mopen::setAdjacent(int const _port, Element* adjacent, int const adjacent_port) {
	switch(_port) {
		case 1: adjacent1={ adjacent, adjacent_port }; break;
		default: return 1;
		}
	return 0;
	}
