/***************************************************************************
                               test_schparser.cpp
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

#include <catch.hpp>

#include "schparser.hpp"
using namespace std;

SCENARIO("check_void()", "[schparser][toolbox]") {

	Data data;
	SchParser parser(data);

	GIVEN("check_void() must replace null strings by 0") {

		WHEN("Input string is null") {
			THEN("Output string must be 0") {
				REQUIRE(parser.check_void("", "deadbeef") == "0");
				}
			}

		WHEN("Input string is not null") {
			THEN("Output string must be unchanged") {
				REQUIRE(parser.check_void("test", "deadbeef") == "test");
				}
			}
		}
	}
