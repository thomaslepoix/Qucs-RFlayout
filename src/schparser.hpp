/***************************************************************************
                               parser.hpp
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

#ifndef SCHPARSER_HPP
#define SCHPARSER_HPP

#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <memory>

#include "logger.hpp"
#include "microstrip/microstrip.hpp"

#ifdef QRFL_UNITTEST
#define private public
#endif // QRFL_UNITTEST

class SchParser {
private:
	std::vector<std::shared_ptr<Element>>& tab_all;
	std::string const& n_sch;
	std::vector<std::string> unprintables;

	long double suffix(std::string const s_sci, std::string const s_eng);
	std::string check_void(std::string match, std::string label);
	std::string mstub_shift(bool const xy, std::string const str, std::string const r);
	void warn_unprintable(void);

public:
	SchParser(std::vector<std::shared_ptr<Element>>& _tab_all, std::string const& _n_sch);
	int run(void);
	void clear(void);
};

#ifdef QRFL_UNITTEST
#undef private
#endif // QRFL_UNITTEST

#endif // SCHPARSER_HPP
