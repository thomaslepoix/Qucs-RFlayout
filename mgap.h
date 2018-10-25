#ifndef MGAP_H
#define MGAP_H

#include "element.h"

class Mgap : public Element {
private :
	long double m_w1;
	long double m_w2;
	long double m_s;
	std::string m_net1;
	std::string m_net2;
public :
	Mgap(std::string _label,
		std::string _type,
		short _mirrorx,
		short _r,
		short _nport,
		long double _w1,
		long double _w2,
		long double _s);
	~Mgap();
	long double getW1(void);
	long double getW2(void);
	long double getS(void);
	std::string getNet1(void);
	std::string getNet2(void);
	int setNet1(std::string _net1);
	int setNet2(std::string _net2);
////////////////////////////////////////////////////////////////////////////////
	long double getW(void);
	long double getW3(void);
	long double getW4(void);
	long double getL(void);
	long double getD(void);
	long double getRi(void);
	long double getRo(void);
	short getAlpha(void);
	std::string getNet3(void);
	std::string getNet4(void);
	int setNet3(std::string _net3);
	int setNet4(std::string _net4);
};

#endif

