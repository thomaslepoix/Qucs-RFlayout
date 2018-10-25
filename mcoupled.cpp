#include "mcoupled.h"
using namespace std;

Mcoupled::Mcoupled(string _label,
			string _type,
			short _mirrorx,
			short _r,
			short _nport,
			long double _w,
			long double _l,
			long double _s) :
	Element(_label, _type, _mirrorx, _r, _nport),
	m_w(_w),
	m_l(_l),
	m_s(_s)
	{}

Mcoupled::~Mcoupled() {
	}

long double Mcoupled::getW(void) {
	return(m_w);
	}

long double Mcoupled::getL(void) {
	return(m_l);
	}

long double Mcoupled::getS(void) {
	return(m_s);
	}

string Mcoupled::getNet1(void) {
	return(m_net1);
	}

string Mcoupled::getNet2(void) {
	return(m_net2);
	}

string Mcoupled::getNet3(void) {
	return(m_net3);
	}

string Mcoupled::getNet4(void) {
	return(m_net4);
	}

int Mcoupled::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

int Mcoupled::setNet2(string _net2) {
	m_net2=_net2;
	return(0);
	}

int Mcoupled::setNet3(string _net3) {
	m_net3=_net3;
	return(0);
	}

int Mcoupled::setNet4(string _net4) {
	m_net4=_net4;
	return(0);
	}

////////////////////////////////////////////////////////////////////////////////

long double Mcoupled::getW1(void) {
	return(0);
	}
long double Mcoupled::getW2(void) {
	return(0);
	}
long double Mcoupled::getW3(void) {
	return(0);
	}
long double Mcoupled::getW4(void) {
	return(0);
	}
long double Mcoupled::getD(void) {
	return(0);
	}
long double Mcoupled::getRi(void) {
	return(0);
	}
long double Mcoupled::getRo(void) {
	return(0);
	}
short Mcoupled::getAlpha(void) {
	return(0);
	}
