/***************************************************************************
                               oemsmesh.cpp
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

#include <iostream>

#include "oemsmesh.hpp"
using namespace std;

//******************************************************************************
OemsMesh::OemsMesh(vector<shared_ptr<Element>>& elements) {
	for(shared_ptr<Element> element : elements) {
		for(int i=0;i<element->getOemsNcorelines();i++) {
			OemsLine line;
			if(!element->getOemsMeshCore(i, line)) {
				if(line.direction==XMIN || line.direction==XMAX) {
					x.push_back(line);
				} else if(line.direction==YMIN || line.direction==YMAX) {
					y.push_back(line);
					}
				}
			}
		for(int i=1;i<=element->getNport();i++) {
			OemsLine line;
			if(!element->getOemsMeshInterface(i, line)) {
				if(line.direction==XMIN || line.direction==XMAX) {
					x.push_back(line);
				} else if(line.direction==YMIN || line.direction==YMAX) {
					y.push_back(line);
					}
				}
			}

		}
	}
