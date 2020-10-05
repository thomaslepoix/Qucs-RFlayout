/***************************************************************************
                               converter.hpp
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

#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <array>
#include <memory>
#include <vector>

#include "data.hpp"
#include "schparser.hpp"
#include "xycalculator.hpp"
#include "layoutwriter.hpp"

//******************************************************************************
class Converter {
private:
	Data& data;
	SchParser parser;
	XyCalculator xycalculator;
	LayoutWriter const layoutwriter;

public:
	Converter(Data& data);
	~Converter()=default;

	void reset();
	int run();
	int read();
	int write(std::vector<std::string>& out_names) const;
	int size() const;

	std::vector<std::shared_ptr<Element>> const& get_tab_all() const;
	std::array<long double, 4> const& get_extrem_pos() const;
};

#endif // CONVERTER_HPP
