///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#pragma once

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

	std::vector<std::shared_ptr<Element>> const& get_all_elements() const;
	std::array<long double, 4> const& get_extrem_pos() const;
};
