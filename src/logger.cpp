///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#include <iostream>

#include "logger.hpp"
using namespace std;

//******************************************************************************
Logger log_err;

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

