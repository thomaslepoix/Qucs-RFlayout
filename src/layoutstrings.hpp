///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

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
