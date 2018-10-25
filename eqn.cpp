#include "eqn.h"
using namespace std;

Eqn::Eqn(string _label,
			string _type,
			short _mirrorx,
			short _r,
			short _nport) :
	Element(_label, _type, _mirrorx, _r, _nport)
	{}

Eqn::~Eqn() {
	}

////////////////////////////////////////////////////////////////////////////////

long double Eqn::getW(void) {
	return(0);
	}
long double Eqn::getW1(void) {
	return(0);
	}
long double Eqn::getW2(void) {
	return(0);
	}
long double Eqn::getW3(void) {
	return(0);
	}
long double Eqn::getW4(void) {
	return(0);
	}
long double Eqn::getL(void) {
	return(0);
	}
long double Eqn::getD(void) {
	return(0);
	}
long double Eqn::getS(void) {
	return(0);
	}
long double Eqn::getRi(void) {
	return(0);
	}
long double Eqn::getRo(void) {
	return(0);
	}
short Eqn::getAlpha(void) {
	return(0);
	}
string Eqn::getNet1(void) {
	return("");
	}
string Eqn::getNet2(void) {
	return("");
	}
string Eqn::getNet3(void) {
	return("");
	}
string Eqn::getNet4(void) {
	return("");
	}
int Eqn::setNet1(string _net1) {
	return(1);
	}
int Eqn::setNet2(string _net2) {
	return(1);
	}
int Eqn::setNet3(string _net3) {
	return(1);
	}
int Eqn::setNet4(string _net4) {
	return(1);
	}
