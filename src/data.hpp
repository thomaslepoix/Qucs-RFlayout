///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#pragma once

#include <array>
#include <filesystem>
#include <memory>
#include <sstream>
#include <tuple>
#include <vector>

#include "microstrip/element.hpp"

//******************************************************************************
class Block {
public:
	std::vector<std::shared_ptr<Element>> elements;
	std::shared_ptr<Element> subst;
	std::shared_ptr<Element> subst_local; // Substrate adjusted to each block
	std::array<long double, 4> metal_boundary;
	std::array<long double, 4> margin_boundary;
	long double margin;

	Block();
	~Block()=default;
	void shift(long double const x, long double const y);
//	void shift(long double const x, long double const y, bool const apply_shift); //TODO apply_shift : adapt subst size to shifted ports
	void calcul_boundaries();
//	void calcul_boundaries(bool const apply_shift=false); //TODO apply_shift : adapt subst size to shifted ports
	void print_extrem_pos() const;
	void print() const;
};

//******************************************************************************
class Data {
public:

	// Discarded on reset
	std::vector<std::shared_ptr<Element>> all_elements;
	std::vector<std::shared_ptr<Block>> all_blocks;
//	std::vector<std::shared_ptr<Substrate>> all_substrates;

//	std::vector<std::shared_ptr<Element>> all_elem;
//	std::vector<std::vector<std::shared_ptr<Element>>> all_elem_block;
//	std::vector<std::vector<std::shared_ptr<Element>>> all_elem_subst;

	std::array<long double, 4> metal_boundary;
	std::array<long double, 4> margin_boundary; // extrem coords of elements (subst included) + margins

	bool is_volume_error; // is 3D representation possible?
	std::string volume_error; // 3D error messages buffer

	std::vector<std::string> excluded_elements;
	std::vector<std::string> used_elements;

	// Handles '--port-shift N X Y' arg.
	std::vector<std::tuple<unsigned long, std::string, std::string>> port_shift_args;
	// Handles '--port-size N L W' arg.
	std::vector<std::tuple<unsigned long, std::string, std::string>> port_size_args;

	// Saved on reset
	std::string qucs_binary;
	std::filesystem::path n_sch;
	std::filesystem::path n_net;
	std::filesystem::path out_dir;
	std::string out_format;
	bool export_each_block;
	bool export_each_subst;
	bool keep_tmp_files;

	unsigned int subst_margin_factor;
	long double port_default_l;

	unsigned int oems_boundary_factor;
	unsigned int oems_highres_div;
	unsigned int oems_metalres_div;
	unsigned int oems_substres_div;
	unsigned int oems_timeres;
	std::string oems_end_criteria;
	std::string oems_nf2ff_center;
	bool oems_sort_metalresmesh;
	bool oems_pkg;

	Data();
	Data(Data const& data);
	Data& operator=(Data const&)=default;
	~Data();
};
