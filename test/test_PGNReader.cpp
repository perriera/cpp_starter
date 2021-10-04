#include <fstream>
#include <iostream>// std::cout
#include <sstream>// std::stringstream
#include <string>// std::string

#include "../include/chessmind/pgn/PGNReader.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO("Verify PGNReader (kasparov_muratkuliev_1973)", "[PGNReader]")
{
  ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
  REQUIRE(myfile.good());
  PGNReader parser;
  myfile >> parser;
  REQUIRE(parser.lines().size() == 35);
}

SCENARIO("Verify PGNReader (kasparov_smyslov_1988.pgn)", "[PGNReader]")
{
  ifstream myfile("data/pgn/kasparov_smyslov_1988.pgn");
  REQUIRE(myfile.good());
  PGNReader parser;
  myfile >> parser;
  cout << parser.lines().size() << endl;
  REQUIRE(parser.lines().size() == 17);
}
