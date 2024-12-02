///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#pragma once

#include <memory>
#include <vector>

#include "oemsline.hpp"
#include "microstrip/element.hpp"

//******************************************************************************
class OemsMesh {
private:
	void sort(std::vector<OemsLine>& a) const;

public:
	std::vector<OemsLine> x;
	std::vector<OemsLine> y;

	OemsMesh(std::vector<std::shared_ptr<Element>> const& elements, bool const _sort);
	~OemsMesh()=default;
};
