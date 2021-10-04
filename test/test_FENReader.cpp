#include <fstream>
#include <iostream>// std::cout
#include <sstream>// std::stringstream
#include <string>// std::string

#include "../include/chessmind/fen/FENReader.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

//
// for f in videos/*; do ffmpeg -i "$f" "compressed/$(basename "${f%.*}").mkv";
// done for f in pgn/*; do ./pgn-extract -Wepd "$f" "pgn/$(basename
// "${f%.*}").PGN" -o"fen/$(basename "${f%.*}").FEN"; done
//

SCENARIO("Verify FENReader read", "[FENReader]")
{
  ifstream myfile("data/fen/kasparov_muratkuliev_1973.fen");
  REQUIRE(myfile.good());
  FENReader parser;
  myfile >> parser;
  cout << parser.lines().size() << endl;
  REQUIRE(parser.lines().size() == 64);
  for (auto line : parser.lines())
    cout << line << endl;
  cout << "thank you" << endl;
}

SCENARIO("Verify FENReader col/row navigation", "[FENReader]")
{
  ifstream myfile("data/fen/kasparov_muratkuliev_1973.fen");
  REQUIRE(myfile.good());
  FENReader parser;
  myfile >> parser;
  cout << parser.lines().size() << endl;
  REQUIRE(parser.lines().size() == 64);
  FENPlacement placement;
  cout << placement.placement(0, 0) << endl;
  REQUIRE(placement.placement(0, 0) == 'r');
  cout << placement.placement(0, 0) << endl;
  REQUIRE(placement.symbolAt('a', '8') == 'r');
  REQUIRE(placement.symbolAt('a', '1') == 'R');
  REQUIRE(placement.symbolAt('e', '2') == 'P');
  REQUIRE(placement.symbolAt('e', '7') == 'p');
  REQUIRE(placement.symbolAt('e', '1') == 'K');
  REQUIRE(placement.symbolAt('e', '8') == 'k');
  REQUIRE(placement.symbolAt('e', '4') == ' ');
  REQUIRE(placement.symbolAt('e', '5') == ' ');
}

// SCENARIO("Verify FENReader", "[FENReader]")
// {
//     ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
//     REQUIRE(myfile.good());
//     FENReader parser;
//     myfile >> parser;
//     REQUIRE(parser.lines().size() == 35);
// }
