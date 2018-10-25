#include "element.h"
using namespace std;

Element::Element(string _label,
				string _type,
				short _mirrorx,
				short _r,
				short _nport) :
	m_label(_label),
	m_type(_type),
	m_mirrorx(_mirrorx),
	m_r(_r),
	m_nport(_nport)
	{}

Element::~Element() {
	}

std::string Element::getLabel(void) {
	return(m_label);
	}

std::string Element::getType(void) {
	return(m_type);
	}

short Element::getMirrorx(void) {
	return(m_mirrorx);
	}

short Element::getR(void) {
	return(m_r);
	}

short Element::getNport(void) {
	return(m_nport);
	}

long double Element::getX(void) {
	return(m_x);
	}

long double Element::getY(void) {
	return(m_y);
	}

int Element::setX(long double _x) {
	m_x=_x;
	return(0);
	}

int Element::setY(long double _y) {
	m_y=_y;
	return(0);
	}
