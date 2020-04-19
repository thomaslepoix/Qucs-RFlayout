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

	int check_qucsstudio(std::ifstream& f_sch, std::string& n_tmp);
	int generate_netlist(std::string const& n_sch, std::string const& n_net);
	void parse_schematic(std::ifstream& f_sch);
	void parse_netlist(std::ifstream& f_net);
	void warn_unprintable(void);

	int open_file(std::ifstream& file, std::string const name);
	long double suffix(std::string const s_sci, std::string const s_eng, bool const is_length);
	std::string check_void(std::string const match, std::string const label);
	std::string mstub_shift(bool const xy, std::string const str, std::string const r);

public:
	SchParser(Data& _data);
	int run(void);
	void clear(void);
};

#ifdef QRFL_UNITTEST
#undef private
#endif // QRFL_UNITTEST

#endif // SCHPARSER_HPP
