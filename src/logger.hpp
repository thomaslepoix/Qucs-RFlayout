/***************************************************************************
                               logger.hpp
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

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <sstream>

// Prefer log_err instead of cerr
// Do not use std::endl or std::flush with logger objects

class MainWindow;
void operator<<(MainWindow& obj, std::stringstream& in);

class logger {
private:
	typedef void (logger::*func)(std::stringstream&);
	func f;

	template<typename T>
	friend logger& operator<<(logger& log, T const& in);

	void func_cli(std::stringstream& in);
	void func_gui(std::stringstream& in);
	void print(std::stringstream& in);

public:
	MainWindow* obj=nullptr;

	logger(void);
	void set_mode(bool gui);
};

extern logger log_err;

template<typename T>
logger& operator<<(logger& log, T const& in) {
	std::stringstream ss;
	ss << in;
	log.print(ss);
	return(log);
	}

#endif // LOGGER_HPP
