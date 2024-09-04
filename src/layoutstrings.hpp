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

#pragma once

#include <string>

//******************************************************************************
struct oems_m {
	oems_m()=delete;
	static std::string const write_touchstone_m; // From CTB v0.0.35 tarball
	static std::string const plotFF3D_frames;
	static std::string const plotSmith;
	static std::string const oemshll_cli;
	static std::string const oemshll_plotVSWR;
	static std::string const oemshll_plotFeedImpedance;
	static std::string const oemshll_plotSParameters;
	static std::string const oemshll_plotSmithChart;
	static std::string const oemshll_plotPhaseResponse;
	static std::string const oemshll_plotPhaseDelay;
	static std::string const oemshll_plotGroupDelay;
	static std::string const oemshll_postProcess;
};

//******************************************************************************
struct pcbrnd_lht {
	pcbrnd_lht()=delete;
	static std::string const fonts;
};
