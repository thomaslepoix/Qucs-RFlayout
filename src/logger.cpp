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

//******************************************************************************
Logger log_err;

//******************************************************************************
void Loggable::log(stringstream& /*in*/) {
	}

//******************************************************************************
void Logger::func_cli(stringstream& in) {
	cerr << in.str();
	}

//******************************************************************************
void Logger::func_gui(stringstream& in) {
	obj->log(in);
	}

//******************************************************************************
void Logger::print(stringstream& in) {
	(this->*f)(in);
	}

//******************************************************************************
Logger::Logger() : f(&Logger::func_cli) {
	}

//******************************************************************************
void Logger::set_mode(bool gui) {
	if(gui) f=&Logger::func_gui;
	else f=&Logger::func_cli;
	}

