///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#include "oemsline.hpp"

//******************************************************************************
bool operator<(OemsLine const& a, OemsLine const& b) {
	return a.position<b.position ? true : false;
	}
