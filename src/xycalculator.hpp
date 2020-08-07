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
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef XYCALCULATOR_HPP
#define XYCALCULATOR_HPP

#include <memory>
#include <vector>

#include "data.hpp"
#include "microstrip/element.hpp"

class XyCalculator {
private:
	Data& data;

	// Main functions
	bool check_intersection(void);
	void populate_adjacents(void);
	void resolve_pac_shapes(void);
	void place_elements(void);
	void place_blocks(void);

	// Toolbox functions
	int get_port(std::shared_ptr<Element> const& element, std::string const net);
	void sort_blocks(std::vector<std::shared_ptr<Block>> blocks, std::vector<std::shared_ptr<Element>> substs);
	int add_to_block(std::shared_ptr<Block>& block, std::shared_ptr<Element> const& element);
	int tab_remove(std::vector<std::shared_ptr<Element>>& elements, std::shared_ptr<Element> const& element);
	bool purgefind(std::shared_ptr<Element> const& element, std::string const net);
	int purge_nets(void);
	int purge_blocks(void);
	bool check_onenet(std::string const net);
	int activenets(std::shared_ptr<Element> const& element);
	int netmin(std::shared_ptr<Element> const& element);
	void findnext(std::shared_ptr<Element> const& current, int& current_net, std::shared_ptr<Element>& next);

public:
	XyCalculator(Data& _data);
	~XyCalculator(void)=default;

	// Interface functions
	int run(void);
};

#endif // XYCALCULATOR_HPP
