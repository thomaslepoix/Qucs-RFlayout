///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#include "converter.hpp"
using namespace std;

//******************************************************************************
Converter::Converter(Data& _data) :
	data(_data),
	parser(_data),
	xycalculator(_data),
	layoutwriter(_data)
	{}

//******************************************************************************
void Converter::reset() {
	data.reset();
	}

//******************************************************************************
int Converter::run() {
	int ret;
	if((ret=(parser.run()
	|| xycalculator.run()
	|| layoutwriter.run()
	))) {
		return ret;
		}

	return 0;
	}

//******************************************************************************
int Converter::read() {
	int ret;
	if((ret=(parser.run()
	|| xycalculator.run()
	))) {
		return ret;
		}

	return 0;
	}

//******************************************************************************
int Converter::write(vector<string>& out_names) const {
	return layoutwriter.run(&out_names);
	}

//******************************************************************************
int Converter::size() const {
	return data.all_elements.size();
	}

//******************************************************************************
vector<shared_ptr<Element>> const& Converter::get_all_elements() const {
	return data.all_elements;
	}

//******************************************************************************
array<long double, 4> const& Converter::get_extrem_pos() const {
	return data.margin_boundary;
	}
