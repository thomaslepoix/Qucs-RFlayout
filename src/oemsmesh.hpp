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
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef OEMSMESH_HPP
#define OEMSMESH_HPP

#include <memory>
#include <vector>

#include "oemsline.hpp"
#include "microstrip/element.hpp"

//******************************************************************************
class OemsMesh {
public:
	std::vector<OemsLine> x;
	std::vector<OemsLine> y;

	OemsMesh(std::vector<std::shared_ptr<Element>>& elements);
	~OemsMesh(void)=default;
};

#endif // OEMSMESH_HPP
