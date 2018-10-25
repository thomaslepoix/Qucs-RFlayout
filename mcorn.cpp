#include "mcorn.h"
using namespace std;

Mcorn::Mcorn(string _label,
			string _type,
			short _mirrorx,
			short _r,
			short _nport,
			long double _w) :
	Element(_label, _type, _mirrorx, _r, _nport),
	m_w(_w)
	{}

Mcorn::~Mcorn() {
	}

long double Mcorn::getW(void) {
	return(m_w);
	}

string Mcorn::getNet1(void) {
	return(m_net1);
	}

string Mcorn::getNet2(void) {
	return(m_net2);
	}

int Mcorn::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

int Mcorn::setNet2(string _net2) {
	m_net2=_net2;
	return(0);
	}

////////////////////////////////////////////////////////////////////////////////

long double Mcorn::getW1(void) {
	return(0);
	}
long double Mcorn::getW2(void) {
	return(0);
	}
long double Mcorn::getW3(void) {
	return(0);
	}
long double Mcorn::getW4(void) {
	return(0);
	}
long double Mcorn::getL(void) {
	return(0);
	}
long double Mcorn::getD(void) {
	return(0);
	}
long double Mcorn::getS(void) {
	return(0);
	}
long double Mcorn::getRi(void) {
	return(0);
	}
long double Mcorn::getRo(void) {
	return(0);
	}
short Mcorn::getAlpha(void) {
	return(0);
	}
string Mcorn::getNet3(void) {
	return("");
	}
string Mcorn::getNet4(void) {
	return("");
	}
int Mcorn::setNet3(string _net3) {
	return(1);
	}
int Mcorn::setNet4(string _net4) {
	return(1);
	}
