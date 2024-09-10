///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#pragma once

#include <sstream>

// Inherit to make a class loggable in GUI mode. Then implement the 'log'
// member function.
//******************************************************************************
class Loggable {
private:
	friend class Logger;
	virtual void log(std::stringstream& in)=0;
public:
	Loggable()=default;
	virtual ~Loggable()=default;
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

	Logger();
	~Logger()=default;
	void set_mode(bool gui);
};

// Prefer log_err instead of cerr.
// Do not use std::endl or std::flush with Logger objects.
//******************************************************************************
extern Logger log_err;

//******************************************************************************
template<typename T>
Logger& operator<<(Logger& logger, T const& in) {
	std::stringstream ss;
	ss << in;
	logger.print(ss);
	return logger;
	}
