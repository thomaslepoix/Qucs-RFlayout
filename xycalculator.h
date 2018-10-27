#ifndef XYCALCULATOR_H
#define XYCALCULATOR_H

#include <iostream>
#include <stack>

#include "eqn.h"
#include "pac.h"
#include "mcorn.h"
#include "mcross.h"
#include "mcoupled.h"
#include "mgap.h"
#include "mmbend.h"
#include "mlin.h"
#include "mopen.h"
#include "mrstub.h"
#include "mstep.h"
#include "mtee.h"
#include "mvia.h"

int xycalculator(Element** const& tab_all, int const& nelem);
int tab_remove(Element** const& tab_undone, int& nundone, int const& nelem, Element* const& current);
bool purgefind(Element** const& tab_all, int const& nelem, Element* const& current, std::string const _net);
int purgenets(Element** const& tab_all, int const& nelem);
int activenets(Element* const& _elem);
int netmin(Element* const& _elem);
int findnext(Element** const& tab_all, int const& nelem, Element* const& current, int& current_net, Element*& next);
int xystep(Element* const& _elem, int const _net, long double& xstep, long double& ystep);

#endif