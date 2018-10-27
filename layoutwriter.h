#ifndef LAYOUTWRITER_H
#define LAYOUTWRITER_H

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <regex>
#include <cmath>

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

int layoutwriter(Element** const& tab_all, int const& nelem, std::string const& n_sch, std::string const& out_format);
int write_kicad_pcb(Element** const& tab_all, int const& nelem, std::ofstream& f_out);

#endif
