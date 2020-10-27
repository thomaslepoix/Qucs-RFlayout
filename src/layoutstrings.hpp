/***************************************************************************
                               layoutstrings.hpp
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

#ifndef LAYOUTSTRINGS_HPP
#define LAYOUTSTRINGS_HPP

#include <string>

//******************************************************************************
struct oems_m {
	oems_m()=delete;
	static std::string const write_touchstone_m; // From CTB v0.0.35 tarball
	static std::string const plotFF3D_frames;
	static std::string const plotSmith;
	static std::string const oemsgen_cli;
	static std::string const oemsgen_plotVSWR;
	static std::string const oemsgen_plotFeedImpedance;
	static std::string const oemsgen_plotSParameters;
	static std::string const oemsgen_plotSmithChart;
	static std::string const oemsgen_postProcess;
};

//******************************************************************************
struct pcbrnd_lht {
	pcbrnd_lht()=delete;
	static std::string const fonts;
};

#endif // LAYOUTSTRINGS_HPP
