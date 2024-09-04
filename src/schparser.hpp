///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#pragma once

#include <filesystem>
#include <fstream>
#include <initializer_list>
#include <memory>

#include "data.hpp"

#ifdef QRFL_UNITTEST
#define private public
#endif // QRFL_UNITTEST

//******************************************************************************
class SchParser {
private:
	Data& data;

	void parse_port_shift_args();
	void parse_port_size_args();

	int check_qucsstudio(std::ifstream& f_sch, std::filesystem::path& n_tmp, bool& is_qucsstudio) const;
	int generate_netlist(std::filesystem::path const& n_sch, std::filesystem::path const& n_net) const;

	void parse_data(std::ifstream& f_dat, std::vector<std::pair<std::string, long double>>& variables) const;
	void parse_schematic_datafile(std::ifstream& f_sch, std::filesystem::path& n_dat, bool& is_there_eqn) const;
	void parse_schematic_components(std::ifstream& f_sch, std::vector<std::pair<std::string, long double>>& variables, std::vector<std::string>& unprintables);
	void parse_netlist(std::ifstream& f_net);

	void warn_unprintable(std::vector<std::string> const& unprintables) const;
	void rm_tmp_files(std::initializer_list<std::string> const args) const;

	long double suffix(std::string const s_sci, std::string const s_eng, bool const is_length) const;
	long double process_field(std::vector<std::pair<std::string, long double>> const& variables, std::string const variable, std::string const value, std::string const s_sci, std::string const s_eng, std::string const label, bool const is_length) const;
	std::string check_void(std::string const match, std::string const label="") const;
	std::string mstub_shift(bool const xy, std::string const str, std::string const r) const;

public:
	SchParser(Data& _data);
	~SchParser()=default;
	int run();
};

#ifdef QRFL_UNITTEST
#undef private
#endif // QRFL_UNITTEST
