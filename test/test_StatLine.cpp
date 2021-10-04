#include <fstream>
#include <iostream>// std::cout
#include <map>
#include <sstream>// std::stringstream
#include <string>// std::string

#include "../include/cpp_starter/fen/FENReader.hpp"
#include "../include/cpp_starter/pgn/PGNGame.hpp"
#include "../include/cpp_starter/stat/StatWriter.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO("Verify StatLine", "[StatLine]")
{
  ifstream myFENfile("data/fen/kasparov_muratkuliev_1973.fen");
  REQUIRE(myFENfile.good());
  FENReader fenReader;
  myFENfile >> fenReader;
  cout << fenReader.lines().size() << endl;
  REQUIRE(fenReader.lines().size() == 64);

  ifstream myPGNfile("data/pgn/kasparov_muratkuliev_1973.pgn");
  REQUIRE(myPGNfile.good());
  PGNGame pgnGame;
  myPGNfile >> pgnGame;
  cout << pgnGame.pgnmoves().size() << endl;
  REQUIRE(pgnGame.pgnmoves().size() == 32);

  StatWriter statWriter;
  statWriter.convert(fenReader, pgnGame);

  StatLines lines = statWriter.lines();
  REQUIRE(lines.size() > 0);

  try {
    for (StatLine line : lines) {
      stringstream ss;
      ss << line;
      StatLine copy;
      cout << line << endl;
      ss >> copy;
      REQUIRE(line == copy);
    }
  }
  catch (exception& ex) {
    cout << ex.what() << endl;
  }
}
