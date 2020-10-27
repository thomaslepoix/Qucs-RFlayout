/***************************************************************************
                               converter.cpp
                             ------------------
    begin                : Thu Oct 25 2018
    copyright            : (C) 2018 by Thomas Lepoix
    email                : thomas.lepoix@protonmail.ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "converter.hpp"
using namespace std;

//******************************************************************************
Converter::Converter(Data& _data) :
	data(_data),
	parser(_data),
	xycalculator(_data),
	layoutwriter(_data)
	{}

//******************************************************************************
void Converter::reset() {
	data=Data(data);
	}

//******************************************************************************
int Converter::run() {
	int ret;
	if((ret=(parser.run()
	|| xycalculator.run()
	|| layoutwriter.run()
	))) {
		return(ret);
		}

	return(0);
	}

//******************************************************************************
int Converter::read() {
	int ret;
	if((ret=(parser.run()
	|| xycalculator.run()
	))) {
		return(ret);
		}

	return(0);
	}

//******************************************************************************
int Converter::write(vector<string>& out_names) const {
	return(layoutwriter.run(&out_names));
	}

//******************************************************************************
int Converter::size() const {
	return(data.tab_all.size());
	}

//******************************************************************************
vector<shared_ptr<Element>> const& Converter::get_tab_all() const {
	return(data.tab_all);
	}

//******************************************************************************
array<long double, 4> const& Converter::get_extrem_pos() const {
	return(data.margin_boundary);
	}
