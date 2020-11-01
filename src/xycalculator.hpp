/***************************************************************************
                               xycalculator.hpp
                             ------------------
    begin                : Thu Oct 25 2018
    copyright            : (C) 2018 by Thomas Lepoix
    email                : thomas.lepoix@protonmail.ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef XYCALCULATOR_HPP
#define XYCALCULATOR_HPP

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

#endif // XYCALCULATOR_HPP
