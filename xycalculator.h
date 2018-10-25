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

int xycalculator(Element** tab_undone, int& nelem);
int tab_remove(Element** tab_undone, int& nundone, int& nelem, Element* current);
bool purgefind(Element** tab_all, int& nelem, Element* current, std::string _net);
int purgenets(Element** tab_all, int& nelem);
int activenets(Element* _elem);
int netmin(Element* _elem);
int findnext(Element** tab_all, int& nelem, Element* current, int& current_net, Element*& next);
int xystep(Element* _elem, int _net, long double& xstep, long double& ystep);

#endif
