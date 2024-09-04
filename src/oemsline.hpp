///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#pragma once

#include <memory>
#include <string>

// High resolution meshlines work by pair. To be printed as hres lines, it is
// required that both lines of a pair are contiguous in a OemsMesh.dir vector
// Otherwise both will be printed as regular metal resolution lines

//******************************************************************************
struct OemsLine {
	long double position;
	int direction;
	bool third_rule;
	bool high_res=false;
	std::string label;
	std::string type;
};

//******************************************************************************
bool operator<(OemsLine const& a, OemsLine const& b);
