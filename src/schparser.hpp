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

#include <fstream>
#include <memory>

#include "data.hpp"

#ifdef QRFL_UNITTEST
#define private public
#endif // QRFL_UNITTEST

class SchParser {
private:
	Data& data;
	std::vector<std::string> unprintables;

	long double suffix(std::string const s_sci, std::string const s_eng, bool is_length);
	std::string check_void(std::string match, std::string label);
	std::string mstub_shift(bool const xy, std::string const str, std::string const r);
	void warn_unprintable(void);

public:
	SchParser(Data& _data);
	int run(void);
	void clear(void);
};

#ifdef QRFL_UNITTEST
#undef private
#endif // QRFL_UNITTEST

#endif // SCHPARSER_HPP
