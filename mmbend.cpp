#include "mmbend.h"
using namespace std;

Mmbend::Mmbend(string _label,
			string _type,
			short _mirrorx,
			short _r,
			short _nport,
			long double _w) :
	Element(_label, _type, _mirrorx, _r, _nport),
	m_w(_w)
	{}

Mmbend::~Mmbend() {
	}

long double Mmbend::getW(void) {
	return(m_w);
	}

string Mmbend::getNet1(void) {
	return(m_net1);
	}

string Mmbend::getNet2(void) {
	return(m_net2);
	}

int Mmbend::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

int Mmbend::setNet2(string _net2) {
	m_net2=_net2;
	return(0);
	}

////////////////////////////////////////////////////////////////////////////////

long double Mmbend::getW1(void) {
	return(0);
	}
long double Mmbend::getW2(void) {
	return(0);
	}
long double Mmbend::getW3(void) {
	return(0);
	}
long double Mmbend::getW4(void) {
	return(0);
	}
long double Mmbend::getL(void) {
	return(0);
	}
long double Mmbend::getD(void) {
	return(0);
	}
long double Mmbend::getS(void) {
	return(0);
	}
long double Mmbend::getRi(void) {
	return(0);
	}
long double Mmbend::getRo(void) {
	return(0);
	}
short Mmbend::getAlpha(void) {
	return(0);
	}
string Mmbend::getNet3(void) {
	return("");
	}
string Mmbend::getNet4(void) {
	return("");
	}
int Mmbend::setNet3(string _net3) {
	return(1);
	}
int Mmbend::setNet4(string _net4) {
	return(1);
	}
