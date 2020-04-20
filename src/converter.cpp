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
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "converter.hpp"
using namespace std;

Converter::Converter(Data& _data) :
	data(_data),
	parser(_data),
	xycalculator(_data),
	layoutwriter(_data)
	{}

Converter::~Converter(void) {
	for(std::shared_ptr<Element> it : data.tab_all) {
		it->prev=nullptr;
		}
	}

void Converter::reset(string n_sch, string out_dir, string out_format) {
	data.n_sch=n_sch;
	data.out_dir=out_dir;
	data.out_format=out_format;
	}

void Converter::clear(void) {
	for(std::shared_ptr<Element> it : data.tab_all) {
		it->prev=nullptr;
		}
	data.clear();
	parser.clear();
	xycalculator.clear();
	}

int Converter::run(void) {
	int ret;
	if((ret=(parser.run()
	|| xycalculator.run()
	|| layoutwriter.run()
	))) {
		return(ret);
		}

	return(0);
	}

int Converter::read(void) {
	int ret;
	if((ret=(parser.run()
	|| xycalculator.run()
	))) {
		return(ret);
		}

	return(0);
	}

int Converter::write(vector<string>& out_names) {
	return(layoutwriter.run(&out_names));
	}

int Converter::size(void) {
	return(data.tab_all.size());
	 }

vector<shared_ptr<Element>> const& Converter::get_tab_all(void) {
	return(data.tab_all);
	}

array<long double, 4> const& Converter::get_extrem_pos(void) {
	return(data.extrem_pos);
	}
