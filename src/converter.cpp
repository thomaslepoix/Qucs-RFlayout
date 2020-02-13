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

Converter::Converter(string _n_sch, string _out_dir, string _out_format) :
	parser(tab_all, n_sch),
	xycalculator(tab_all, extrem_pos),
	layoutwriter(tab_all, extrem_pos, n_sch, out_dir, out_format),
	n_sch(_n_sch),
	out_dir(_out_dir),
	out_format(_out_format)
	{}

Converter::~Converter(void) {
	for(std::shared_ptr<Element> it : tab_all) {
		it->prev=nullptr;
		}
	}

void Converter::reset(string _n_sch, string _out_dir, string _out_format) {
	n_sch=_n_sch;
	out_dir=_out_dir;
	out_format=_out_format;
	}

void Converter::clear(void) {
	for(std::shared_ptr<Element> it : tab_all) {
		it->prev=nullptr;
		}
	tab_all.clear();
	tab_all.shrink_to_fit();
	parser.clear();
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

int Converter::write(string& out_name) {
	return(layoutwriter.run(&out_name));
	}

int Converter::size(void) {
	return(tab_all.size());
	 }

vector<shared_ptr<Element>> const& Converter::get_tab_all(void) {
	return(tab_all);
	}

array<long double, 4> const& Converter::get_extrem_pos(void) {
	return(extrem_pos);
	}

