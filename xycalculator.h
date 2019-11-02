/***************************************************************************
                               xycalculator.h
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

#ifndef XYCALCULATOR_H
#define XYCALCULATOR_H

#include <iostream>
#include <stack>
#include <vector>
#include <memory>

#include "microstrip/eqn.h"
#include "microstrip/pac.h"
#include "microstrip/mcorn.h"
#include "microstrip/mcross.h"
#include "microstrip/mcoupled.h"
#include "microstrip/mgap.h"
#include "microstrip/mmbend.h"
#include "microstrip/mlin.h"
#include "microstrip/mopen.h"
#include "microstrip/mrstub.h"
#include "microstrip/mstep.h"
#include "microstrip/mtee.h"
#include "microstrip/mvia.h"

int xycalculator(std::vector<std::shared_ptr<Element>>& tab_all, long double* extrem_pos);
int tab_remove(std::vector<std::shared_ptr<Element>>& tab_undone, std::shared_ptr<Element> const& current);
bool purgefind(std::vector<std::shared_ptr<Element>> const& tab_all, std::shared_ptr<Element> const& current, std::string const _net);
int purgenets(std::vector<std::shared_ptr<Element>> const& tab_all);
bool checkonenet(std::vector<std::shared_ptr<Element>> const& tab_all, std::string const _net);
int checkintersection(std::vector<std::shared_ptr<Element>> const& tab_all);
int activenets(std::shared_ptr<Element> const& _elem);
int netmin(std::shared_ptr<Element> const& _elem);
int findnext(std::vector<std::shared_ptr<Element>> const& tab_all, std::shared_ptr<Element> const& current, int& current_net, std::shared_ptr<Element>& next);
int xystep(std::shared_ptr<Element> const& _elem, int const _net, long double& xstep, long double& ystep);

/*
int tab_remove(Element** const& tab_undone, int& nundone, int const& nelem, Element* const& current);
bool purgefind(Element** const& tab_all, int const& nelem, Element* const& current, std::string const _net);
int purgenets(Element** const& tab_all, int const& nelem);
int activenets(Element* const& _elem);
int netmin(Element* const& _elem);
int findnext(Element** const& tab_all, int const& nelem, Element* const& current, int& current_net, Element*& next);
int xystep(Element* const& _elem, int const _net, long double& xstep, long double& ystep);*/

#endif // XYCALCULATOR_H
