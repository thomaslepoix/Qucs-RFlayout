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

//******************************************************************************
class Loggable {
private:
	friend class Logger;
	virtual void log(std::stringstream& in);
public:
	Loggable(void)=default;
	~Loggable(void)=default;
};

//******************************************************************************
class Logger {
private:
	typedef void (Logger::*func)(std::stringstream&);
	func f;

	template<typename T>
	friend Logger& operator<<(Logger& log, T const& in);

	void func_cli(std::stringstream& in);
	void func_gui(std::stringstream& in);
	void print(std::stringstream& in);

public:
	Loggable* obj=nullptr;

	Logger(void);
	~Logger(void)=default;
	void set_mode(bool gui);
};

//******************************************************************************
extern Logger log_err;

//******************************************************************************
template<typename T>
Logger& operator<<(Logger& logger, T const& in) {
	std::stringstream ss;
	ss << in;
	logger.print(ss);
	return(logger);
	}

#endif // LOGGER_HPP
