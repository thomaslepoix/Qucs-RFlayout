#include "mopen.h"
using namespace std;

Mopen::Mopen(string _label,
			string _type,
			short _mirrorx,
			short _r,
			short _nport,
			long double _w) :
	Element(_label, _type, _mirrorx, _r, _nport),
	m_w(_w)
	{}

Mopen::~Mopen() {
	}

long double Mopen::getW(void) {
	return(m_w);
	}

string Mopen::getNet1(void) {
	return(m_net1);
	}

int Mopen::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

////////////////////////////////////////////////////////////////////////////////

long double Mopen::getW1(void) {
	return(0);
	}
long double Mopen::getW2(void) {
	return(0);
	}
long double Mopen::getW3(void) {
	return(0);
	}
long double Mopen::getW4(void) {
	return(0);
	}
long double Mopen::getL(void) {
	return(0);
	}
long double Mopen::getD(void) {
	return(0);
	}
long double Mopen::getS(void) {
	return(0);
	}
long double Mopen::getRi(void) {
	return(0);
	}
long double Mopen::getRo(void) {
	return(0);
	}
short Mopen::getAlpha(void) {
	return(0);
	}
string Mopen::getNet2(void) {
	return("");
	}
string Mopen::getNet3(void) {
	return("");
	}
string Mopen::getNet4(void) {
	return("");
	}
int Mopen::setNet2(string _net2) {
	return(1);
	}
int Mopen::setNet3(string _net3) {
	return(1);
	}
int Mopen::setNet4(string _net4) {
	return(1);
	}
