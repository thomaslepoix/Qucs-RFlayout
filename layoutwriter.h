/***************************************************************************
                               layoutwriter.h
                             ------------------
    begin                : Thu Oct 25 2018
    copyright            : (C) 2018 by Thomas Lepoix
    email                : thomas.lepoix@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

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

int layoutwriter(Element** const& tab_all, int const& nelem, std::string const& n_sch, std::string const& out_dir, std::string const& out_format);
int write_kicad_pcb(Element** const& tab_all, int const& nelem, std::ofstream& f_out);
int write_kicad_mod(Element** const& tab_all, int const& nelem, std::string const& name, std::ofstream& f_out);

#endif
