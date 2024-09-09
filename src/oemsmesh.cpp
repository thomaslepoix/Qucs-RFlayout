///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#include <algorithm>
#include <iostream>

#include "oemsmesh.hpp"
using namespace std;

//******************************************************************************
OemsMesh::OemsMesh(vector<shared_ptr<Element>> const& elements, bool const _sort) {
	for(shared_ptr<Element> const& element : elements) {
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
	if(_sort) {
		sort(x);
		sort(y);
		}
	}

// Sort no high_res lines and put high_res ones at the end.
//******************************************************************************
void OemsMesh::sort(vector<OemsLine>& a) {
	vector<OemsLine> tmp;
	for(OemsLine& it : a) {
		if(!it.high_res) {
			tmp.push_back(it);
			}
		}
	std::sort(begin(tmp), end(tmp));
	for(OemsLine& it : a) {
		if(it.high_res) {
			tmp.push_back(it);
			}
		}
	a.swap(tmp);
	}
