#include "mgap.h"
using namespace std;

Mgap::Mgap(string _label,
			string _type,
			short _mirrorx,
			short _r,
			short _nport,
			long double _w1,
			long double _w2,
			long double _s) :
	Element(_label, _type, _mirrorx, _r, _nport),
	m_w1(_w1),
	m_w2(_w2),
	m_s(_s)
	{}

Mgap::~Mgap() {
	}

long double Mgap::getW1(void) {
	return(m_w1);
	}

long double Mgap::getW2(void) {
	return(m_w2);
	}

long double Mgap::getS(void) {
	return(m_s);
	}

string Mgap::getNet1(void) {
	return(m_net1);
	}

string Mgap::getNet2(void) {
	return(m_net2);
	}

int Mgap::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

int Mgap::setNet2(string _net2) {
	m_net2=_net2;
	return(0);
	}

////////////////////////////////////////////////////////////////////////////////

long double Mgap::getW(void) {
	return(0);
	}
long double Mgap::getW3(void) {
	return(0);
	}
long double Mgap::getW4(void) {
	return(0);
	}
long double Mgap::getL(void) {
	return(0);
	}
long double Mgap::getD(void) {
	return(0);
	}
long double Mgap::getRi(void) {
	return(0);
	}
long double Mgap::getRo(void) {
	return(0);
	}
short Mgap::getAlpha(void) {
	return(0);
	}
string Mgap::getNet3(void) {
	return("");
	}
string Mgap::getNet4(void) {
	return("");
	}
int Mgap::setNet3(string _net3) {
	return(1);
	}
int Mgap::setNet4(string _net4) {
	return(1);
	}
