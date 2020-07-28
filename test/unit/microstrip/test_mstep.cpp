/***************************************************************************
                               test_mstep.cpp
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

#include <catch.hpp>
#include <memory>

#include "microstrip/mstep.hpp"
using namespace std;

SCENARIO("Mstep::getEdge()", "[mstep][interface]") {

	GIVEN("Mstep with mirrorx=0 r=0") {
		shared_ptr<Element> mstep=shared_ptr<Element>(new Mstep("deadbeef", "deadbeef", true, 0, 0, "deadbeef", 1.5, 5.5));
		WHEN("net=1") {
			long double edge;
			short dir;
			mstep->getEdge(1, edge, dir);
			THEN("dir must be XMIN") {
				REQUIRE(dir == XMIN);
				}
			THEN("edge must be W1"){
				REQUIRE(edge == mstep->getW1());
				}
			}
		WHEN("net=2") {
			long double edge;
			short dir;
			mstep->getEdge(2, edge, dir);
			THEN("dir must be XMAX") {
				REQUIRE(dir == XMAX);
				}
			THEN("edge must be W2"){
				REQUIRE(edge == mstep->getW2());
				}
			}
		}

	GIVEN("Mstep with mirrorx=0 r=90") {
		shared_ptr<Element> mstep=shared_ptr<Element>(new Mstep("deadbeef", "deadbeef", true, 0, 90, "deadbeef", 1.5, 5.5));
		WHEN("net=1") {
			long double edge;
			short dir;
			mstep->getEdge(1, edge, dir);
			THEN("dir must be YMAX") {
				REQUIRE(dir == YMAX);
				}
			THEN("edge must be W1"){
				REQUIRE(edge == mstep->getW1());
				}
			}
		WHEN("net=2") {
			long double edge;
			short dir;
			mstep->getEdge(2, edge, dir);
			THEN("dir must be YMIN") {
				REQUIRE(dir == YMIN);
				}
			THEN("edge must be W2"){
				REQUIRE(edge == mstep->getW2());
				}
			}
		}

	GIVEN("Mstep with mirrorx=0 r=180") {
		shared_ptr<Element> mstep=shared_ptr<Element>(new Mstep("deadbeef", "deadbeef", true, 0, 180, "deadbeef", 1.5, 5.5));
		WHEN("net=1") {
			long double edge;
			short dir;
			mstep->getEdge(1, edge, dir);
			THEN("dir must be XMAX") {
				REQUIRE(dir == XMAX);
				}
			THEN("edge must be W1"){
				REQUIRE(edge == mstep->getW1());
				}
			}
		WHEN("net=2") {
			long double edge;
			short dir;
			mstep->getEdge(2, edge, dir);
			THEN("dir must be XMIN") {
				REQUIRE(dir == XMIN);
				}
			THEN("edge must be W2"){
				REQUIRE(edge == mstep->getW2());
				}
			}
		}

	GIVEN("Mstep with mirrorx=0 r=270") {
		shared_ptr<Element> mstep=shared_ptr<Element>(new Mstep("deadbeef", "deadbeef", true, 0, 270, "deadbeef", 1.5, 5.5));
		WHEN("net=1") {
			long double edge;
			short dir;
			mstep->getEdge(1, edge, dir);
			THEN("dir must be YMIN") {
				REQUIRE(dir == YMIN);
				}
			THEN("edge must be W1"){
				REQUIRE(edge == mstep->getW1());
				}
			}
		WHEN("net=2") {
			long double edge;
			short dir;
			mstep->getEdge(2, edge, dir);
			THEN("dir must be YMAX") {
				REQUIRE(dir == YMAX);
				}
			THEN("edge must be W2"){
				REQUIRE(edge == mstep->getW2());
				}
			}
		}

	GIVEN("Mstep with mirrorx=1 r=0") {
		shared_ptr<Element> mstep=shared_ptr<Element>(new Mstep("deadbeef", "deadbeef", true, 1, 0, "deadbeef", 1.5, 5.5));
		WHEN("net=1") {
			long double edge;
			short dir;
			mstep->getEdge(1, edge, dir);
			THEN("dir must be XMIN") {
				REQUIRE(dir == XMIN);
				}
			THEN("edge must be W1"){
				REQUIRE(edge == mstep->getW1());
				}
			}
		WHEN("net=2") {
			long double edge;
			short dir;
			mstep->getEdge(2, edge, dir);
			THEN("dir must be XMAX") {
				REQUIRE(dir == XMAX);
				}
			THEN("edge must be W2"){
				REQUIRE(edge == mstep->getW2());
				}
			}
		}

	GIVEN("Mstep with mirrorx=1 r=90") {
		shared_ptr<Element> mstep=shared_ptr<Element>(new Mstep("deadbeef", "deadbeef", true, 1, 90, "deadbeef", 1.5, 5.5));
		WHEN("net=1") {
			long double edge;
			short dir;
			mstep->getEdge(1, edge, dir);
			THEN("dir must be YMAX") {
				REQUIRE(dir == YMAX);
				}
			THEN("edge must be W1"){
				REQUIRE(edge == mstep->getW1());
				}
			}
		WHEN("net=2") {
			long double edge;
			short dir;
			mstep->getEdge(2, edge, dir);
			THEN("dir must be YMIN") {
				REQUIRE(dir == YMIN);
				}
			THEN("edge must be W2"){
				REQUIRE(edge == mstep->getW2());
				}
			}
		}

	GIVEN("Mstep with mirrorx=1 r=180") {
		shared_ptr<Element> mstep=shared_ptr<Element>(new Mstep("deadbeef", "deadbeef", true, 1, 180, "deadbeef", 1.5, 5.5));
		WHEN("net=1") {
			long double edge;
			short dir;
			mstep->getEdge(1, edge, dir);
			THEN("dir must be XMAX") {
				REQUIRE(dir == XMAX);
				}
			THEN("edge must be W1"){
				REQUIRE(edge == mstep->getW1());
				}
			}
		WHEN("net=2") {
			long double edge;
			short dir;
			mstep->getEdge(2, edge, dir);
			THEN("dir must be XMIN") {
				REQUIRE(dir == XMIN);
				}
			THEN("edge must be W2"){
				REQUIRE(edge == mstep->getW2());
				}
			}
		}

	GIVEN("Mstep with mirrorx=1 r=270") {
		shared_ptr<Element> mstep=shared_ptr<Element>(new Mstep("deadbeef", "deadbeef", true, 1, 270, "deadbeef", 1.5, 5.5));
		WHEN("net=1") {
			long double edge;
			short dir;
			mstep->getEdge(1, edge, dir);
			THEN("dir must be YMIN") {
				REQUIRE(dir == YMIN);
				}
			THEN("edge must be W1"){
				REQUIRE(edge == mstep->getW1());
				}
			}
		WHEN("net=2") {
			long double edge;
			short dir;
			mstep->getEdge(2, edge, dir);
			THEN("dir must be YMAX") {
				REQUIRE(dir == YMAX);
				}
			THEN("edge must be W2"){
				REQUIRE(edge == mstep->getW2());
				}
			}
		}
	}
