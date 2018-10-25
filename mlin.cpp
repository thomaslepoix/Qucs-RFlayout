#include "mlin.h"
using namespace std;

Mlin::Mlin(string _label,
			string _type,
			short _mirrorx,
			short _r,
			short _nport,
			long double _w,
			long double _l) :
	Element(_label, _type, _mirrorx, _r, _nport),
	m_w(_w),
	m_l(_l)
	{}

Mlin::~Mlin() {
	}

long double Mlin::getW(void) {
	return(m_w);
	}

long double Mlin::getL(void) {
	return(m_l);
	}

string Mlin::getNet1(void) {
	return(m_net1);
	}

string Mlin::getNet2(void) {
	return(m_net2);
	}

int Mlin::setNet1(string _net1) {
	m_net1=_net1;
	return(0);
	}

int Mlin::setNet2(string _net2) {
	m_net2=_net2;
	return(0);
	}

////////////////////////////////////////////////////////////////////////////////

long double Mlin::getW1(void) {
	return(0);
	}
long double Mlin::getW2(void) {
	return(0);
	}
long double Mlin::getW3(void) {
	return(0);
	}
long double Mlin::getW4(void) {
	return(0);
	}
long double Mlin::getD(void) {
	return(0);
	}
long double Mlin::getS(void) {
	return(0);
	}
long double Mlin::getRi(void) {
	return(0);
	}
long double Mlin::getRo(void) {
	return(0);
	}
short Mlin::getAlpha(void) {
	return(0);
	}
string Mlin::getNet3(void) {
	return("");
	}
string Mlin::getNet4(void) {
	return("");
	}
int Mlin::setNet3(string _net3) {
	return(1);
	}
int Mlin::setNet4(string _net4) {
	return(1);
	}
