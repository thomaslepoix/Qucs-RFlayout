// g++ ../test/unit/test{,_schparser}.cpp ../src/schparser.cpp -I../src/ -I~/testcatch/ -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/ -fPIC -o test

#include <catch.hpp>
#include "schparser.hpp"
using namespace std;

SCENARIO("", "[schparser]") {
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
