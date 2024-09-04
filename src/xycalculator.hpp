///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#pragma once

#include <memory>
#include <vector>

#include "data.hpp"
#include "microstrip/element.hpp"

//******************************************************************************
class XyCalculator {
private:
	Data& data;

	// Main functions
	bool check_intersection() const;
	void populate_adjacents();
	void resolve_pac_shapes();
	void place_elements();
	void place_blocks();

	// Toolbox functions
	int get_port(std::shared_ptr<Element> const& element, std::string const net) const;
	void sort_blocks(std::vector<std::shared_ptr<Block>> blocks, std::vector<std::shared_ptr<Element>> substs);
	int add_to_block(std::shared_ptr<Block>& block, std::shared_ptr<Element> const& element);
	int tab_remove(std::vector<std::shared_ptr<Element>>& elements, std::shared_ptr<Element> const& element);
	bool purgefind(std::shared_ptr<Element> const& element, std::string const net) const;
	int purge_nets();
	int purge_blocks();
	bool check_onenet(std::string const net) const;
	int activenets(std::shared_ptr<Element> const& element) const;
	int netmin(std::shared_ptr<Element> const& element) const;
	void findnext(std::shared_ptr<Element> const& current, int& current_net, std::shared_ptr<Element>& next);

public:
	XyCalculator(Data& _data);
	~XyCalculator()=default;

	// Interface functions
	int run();
};
