#include "mcross.h"
using namespace std;

Mcross::Mcross(string _label,
			string _type,
			short _mirrorx,
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
