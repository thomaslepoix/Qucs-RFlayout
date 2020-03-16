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

#include <iostream>
#include <stack>
#include <vector>
#include <memory>
#include <array>

#include "logger.hpp"
#include "microstrip/microstrip.hpp"

class XyCalculator {
private:
	std::vector<std::shared_ptr<Element>>& tab_all;
	std::array<long double, 4>& extrem_pos;

	int tab_remove(std::vector<std::shared_ptr<Element>>& tab_undone, std::shared_ptr<Element> const& current);
	bool purgefind(std::shared_ptr<Element> const& current, std::string const _net);
	int purgenets(void);
	bool checkonenet(std::string const _net);
	int checkintersection(void);
	int activenets(std::shared_ptr<Element> const& _elem);
	int netmin(std::shared_ptr<Element> const& _elem);
	int findnext(std::shared_ptr<Element> const& current, int& current_net, std::shared_ptr<Element>& next);

public:
	XyCalculator(std::vector<std::shared_ptr<Element>>& _tab_all, std::array<long double, 4>& _extrem_pos);
	int run(void);
	void clear(void);
};

#endif // XYCALCULATOR_HPP
