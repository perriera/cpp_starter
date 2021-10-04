#include <fstream>
#include <iostream> // std::cout
#include <sstream>  // std::stringstream
#include <string>   // std::string

#include "../include/chessmind/game/ChessExceptions.hpp"
#include "../include/chessmind/game/ChessPosition.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO("Verify ChessPosition can do (PGN Type1) 'e2'", "[ChessPosition]") {

  GIVEN("constructor") {
    ChessPosition pos("e1");
    REQUIRE(pos == "e1");
    REQUIRE_THROWS_AS(ChessPosition("e0"), ChessPositionException);
    REQUIRE_THROWS_AS(ChessPosition("i1"), ChessPositionException);
    REQUIRE_THROWS_AS(ChessPosition("a9"), ChessPositionException);
    REQUIRE_THROWS_AS(ChessPosition("9"), ChessPositionException);
    REQUIRE_THROWS_AS(ChessPosition(""), ChessPositionException);
    REQUIRE_THROWS_AS(ChessPosition("999"), ChessPositionException);
  }
  GIVEN("read/write stream") {
    ChessPosition pos;
    stringstream ss;
    ss << "e2";
    ss >> pos;
    REQUIRE(pos == "e2");
    REQUIRE(pos != "e1");
  }
  GIVEN("ChessPosition stream testing") {
    string columns = "a1b2c3d4";
    stringstream ss;
    ss << columns;
    int cnt = 0;
    while (true) {
      ChessPosition cc;
      ss >> cc;
      if (!ss.good())
        break;
      cout << cc << flush;
      cnt++;
    }
    REQUIRE(cnt == columns.size() / 2);
  }

  GIVEN("assigment to string") {
    ChessPosition pos;
    REQUIRE(pos != "e2");
    pos = "e2";
    REQUIRE(pos == "e2");
  }
  GIVEN("assigment to another") {
    ChessPosition a("a2");
    ChessPosition b;
    REQUIRE(b != a);
    b = a;
    REQUIRE(a == b);
  }
  GIVEN("assigment to another") {
    ChessPosition a("a1");
    ChessPosition b("a2");
    REQUIRE(a != b);
  }
}

SCENARIO("Verify ChessPosition octals", "[ChessPosition]") {
  GIVEN("toOctal") {
    ChessPosition pos("e1");
    int test = pos.toOctal();
    REQUIRE(pos == "e1");
    REQUIRE(test == 40);
  }
  GIVEN("fromOctal") {
    ChessPosition pos;
    REQUIRE(pos == "a1");
    pos.fromOctal(40);
    REQUIRE(pos == "e1");
  }
}
