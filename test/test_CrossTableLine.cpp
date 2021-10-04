#include <fstream>
#include <iostream>// std::cout
#include <sstream>// std::stringstream
#include <string>// std::string

#include "../include/cpp_starter/ai/CrossTableLine.hpp"
#include "../include/cpp_starter/fen/FENReader.hpp"
#include "../include/cpp_starter/stat/StatWriter.hpp"
#include "catch.hpp"
#include "extras/ansi_colors.hpp"
#include "extras/crc32_support.hpp"
#include "extras/crc64_support.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO("Verify CrossTableLine ('KASPAROV.ct')", "[CrossTableLine]")
{
  ifstream myFENfile("data/fen/KASPAROV.FEN");
  REQUIRE(myFENfile.good());
  ifstream myPGNfile("data/pgn/KASPAROV.PGN");
  REQUIRE(myPGNfile.good());

  try {
    while (myFENfile.good() && myPGNfile.good()) {
      FENReader fenReader;
      myFENfile >> fenReader;

      PGNGame pgnReader;
      myPGNfile >> pgnReader;

      StatWriter statWriter;
      statWriter.convert(fenReader, pgnReader);

      auto statLines = statWriter.lines();
      for (auto statLine : statLines) {
        cout << statLine << endl;
      }
    }
  }
  catch (exception& ex) {
    cout << ex.what() << endl;
  }
}
