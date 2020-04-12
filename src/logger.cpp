/***************************************************************************
                               logger.cpp
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

#include <iostream>

#include "logger.hpp"
using namespace std;

logger log_err;

void logger::func_cli(stringstream& in) {
	cerr << in.str();
	}

void logger::func_gui(stringstream& in) {
	*obj << in;
	}

void logger::print(stringstream& in) {
	(this->*f)(in);
	}

logger::logger(void) : f(&logger::func_cli) {
	}

void logger::set_mode(bool gui) {
	if(gui) f=&logger::func_gui;
	else f=&logger::func_cli;
	}

