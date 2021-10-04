#include <fstream>
#include <iostream>// std::cout
#include <sstream>// std::stringstream
#include <string>// std::string

#include "../include/cpp_starter/pgn/PGNReader.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO("Verify ReplayGameX", "[ReplayGame]")
{
  ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
  REQUIRE(myfile.good());
  PGNReader parser;
  myfile >> parser;
  REQUIRE(parser.lines().size() == 35);
}
