/***************************************************************************
                               layoutwriter.h
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

#ifndef LAYOUTWRITER_H
#define LAYOUTWRITER_H

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <regex>
#include <cmath>

#include "microstrip/microstrip.h"

int layoutwriter(std::vector<std::shared_ptr<Element>> const& tab_all, long double* const& extrem_pos, std::string const& n_sch, std::string const& out_dir, std::string const& out_format);
int write_kicad_pcb(std::vector<std::shared_ptr<Element>> const& tab_all, std::ofstream& f_out);
int write_kicad_mod(std::vector<std::shared_ptr<Element>> const& tab_all, std::string const& name, std::ofstream& f_out);
int write_lht(std::vector<std::shared_ptr<Element>> const& tab_all, long double* const& extrem_pos, std::ofstream& f_out);

#endif // LAYOUTWRITER_H
