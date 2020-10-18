/***************************************************************************
                               mvia.cpp
                             ------------------
    begin                : Thu Oct 25 2018
    copyright            : (C) 2018 by Thomas Lepoix
    email                : thomas.lepoix@protonmail.ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "mvia.hpp"
using namespace std;

//******************************************************************************
string const Mvia::m_descriptor("microstrip_via");

//******************************************************************************
Mvia::Mvia(string const _label,
			string const _type,
			bool const _active,
			bool const _mirrorx,
			short const _r,
			string const _subst,
			long double const _d) :
	Element(_label, _type, _active, _mirrorx, _r, 1, _subst),
	m_d(_d)
	{}

//******************************************************************************
string Mvia::getDescriptor() const {
	return(m_descriptor);
	}

//******************************************************************************
long double Mvia::getD() const {
	return(m_d);
	}

//******************************************************************************
string Mvia::getNet1() const {
	return(m_net1);
	}

//******************************************************************************
int Mvia::setNet1(string const _net1) {
	m_net1=_net1;
	return(0);
	}

//******************************************************************************
void Mvia::getEdge(int const /*_net*/, long double& edge, short& dir) const {
	edge=m_d;
	switch(m_r) {
		case 0: dir=XMIN; break;
		case 90: dir=YMAX; break;
		case 180: dir=XMAX; break;
		case 270: dir=YMIN; break;
		}
	}

//******************************************************************************
int Mvia::getOemsNcorelines() const {
	return(3);
	}

//******************************************************************************
int Mvia::getOemsMeshCore(int const _n, OemsLine& line) const {
	if(_n==0) {
		switch(m_r) {
			case 0:   line.position=m_y+m_d/2; line.direction=YMAX; break;
			case 90:  line.position=m_x+m_d/2; line.direction=XMAX; break;
			case 180: line.position=m_y-m_d/2; line.direction=YMIN; break;
			case 270: line.position=m_x-m_d/2; line.direction=XMIN; break;
			}
	} else if(_n==1) {
		switch(m_r) {
			case 0:   line.position=m_x+m_d/2; line.direction=XMAX; break;
			case 90:  line.position=m_y-m_d/2; line.direction=YMIN; break;
			case 180: line.position=m_x-m_d/2; line.direction=XMIN; break;
			case 270: line.position=m_y+m_d/2; line.direction=YMAX; break;
			}
	} else if(_n==2) {
		switch(m_r) {
			case 0:   line.position=m_y-m_d/2; line.direction=YMIN; break;
			case 90:  line.position=m_x-m_d/2; line.direction=XMIN; break;
			case 180: line.position=m_y+m_d/2; line.direction=YMAX; break;
			case 270: line.position=m_x+m_d/2; line.direction=XMAX; break;
			}
	} else {
		return(1);
		}

	line.label=m_label;
	line.type=m_type;
	line.third_rule=true;
	return(0);
	}

//******************************************************************************
int Mvia::getOemsMeshInterface(int const _net, OemsLine& line) const {
	if(_net==1
	&&(adjacent1.first==nullptr
	||(adjacent1.first!=nullptr && adjacent1.first->isOemsMeshInterface(adjacent1.second, m_d)))) {
		switch(m_r) {
			case 0:   line.position=m_x-m_d/2; line.direction=XMIN; break;
			case 90:  line.position=m_y+m_d/2; line.direction=YMAX; break;
			case 180: line.position=m_x+m_d/2; line.direction=XMAX; break;
			case 270: line.position=m_y-m_d/2; line.direction=YMIN; break;
			}
	} else {
		return(1);
		}

	line.label=m_label;
	line.type=m_type;
	line.third_rule=true;
	return(0);
	}

//******************************************************************************
bool Mvia::isOemsMeshInterface(int const _port, long double const _w) const {
	if(_port==1) {
		return(_w>m_d ? true : false);
	} else {
		return(false);
		}
	}

//******************************************************************************
int Mvia::setAdjacent(int const _port, shared_ptr<Element> const& adjacent, int const adjacent_port) {
	switch(_port) {
		case 1:
			adjacent1.first=adjacent;
			adjacent1.second=adjacent_port;
			break;
		default:
			return(1);
		}
	return(0);
	}
