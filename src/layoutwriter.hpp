///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#pragma once

#define _USE_MATH_DEFINES

#include <filesystem>
#include <fstream>
#include <memory>

#include "data.hpp"

//******************************************************************************
class LayoutWriter {
private:
	Data const& data;

	int check_m() const;
	int write(Block const& block, long double const offset_x, long double const offset_y, std::filesystem::path const& n_out, std::string const& name, std::vector<std::string>* out_names) const;
	//TODO array<long double, 2> offset ?
	void write_kicad_pcb(Block const& block, std::ofstream& f_out, long double const offset_x, long double const offset_y, std::string const& name) const;
	void write_kicad_mod(Block const& block, std::ofstream& f_out, long double const offset_x, long double const offset_y, std::string const& name) const;
	void write_lht(Block const& block, std::ofstream& f_out, long double const offset_x, long double const offset_y, std::string const& name) const;
	void write_m(Block const& block, std::ofstream& f_out, long double const offset_x, long double const offset_y, std::string const& name) const;
	void write_svg(Block const& block, std::ofstream& f_out, long double const offset_x, long double const offset_y, std::string const& name) const;

public:
	explicit LayoutWriter(Data const& _data);
	~LayoutWriter()=default;
	int run(std::vector<std::string>* out_names=nullptr) const;
};
