/***************************************************************************
                               oemsmesh.hpp
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

#include <memory>
#include <vector>

#include "oemsline.hpp"
#include "microstrip/element.hpp"

//******************************************************************************
class OemsMesh {
private:
	void sort(std::vector<OemsLine>& a);

public:
	std::vector<OemsLine> x;
	std::vector<OemsLine> y;

	OemsMesh(std::vector<std::shared_ptr<Element>>& elements, bool const _sort);
	~OemsMesh()=default;
};
