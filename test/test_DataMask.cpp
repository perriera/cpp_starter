#include <fstream>
#include <iostream>// std::cout
#include <sstream>// std::stringstream
#include <string>// std::string

#include "../include/chessmind/fen/FENReader.hpp"
#include "../include/chessmind/masking/DataMask.hpp"
#include "../include/chessmind/stat/StatHeader.hpp"
#include "../include/chessmind/stat/StatWriter.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO("Verify DataMask ('kasparov_tal_1980.fen')", "[DataMask]")
{
  ifstream myFENfile("data/fen/kasparov_tal_1980.fen");
  REQUIRE(myFENfile.good());
  FENReader fenReader;
  myFENfile >> fenReader;
  cout << fenReader.lines().size() << endl;
  REQUIRE(fenReader.lines().size() == 55);

  ifstream myPGNfile("data/pgn/kasparov_tal_1980.pgn");
  REQUIRE(myPGNfile.good());
  PGNGame pgnReader;
  myPGNfile >> pgnReader;
  cout << pgnReader.pgnmoves().size() << endl;
  REQUIRE(pgnReader.pgnmoves().size() == 27);

  StatWriter statWriter;
  statWriter.convert(fenReader, pgnReader);

  ofstream outfile("data/masked/kasparov_tal_1980.masked.csv");
  REQUIRE(outfile.good());
  DataMask masker;
  masker.mask(statWriter.lines());
  outfile << StatHeader() << endl;
  outfile << masker;
}

SCENARIO("Verify DataMask ('KASPAROV.FEN')", "[DataMask]")
{
  ifstream myFENfile("data/fen/KASPAROV.FEN");
  REQUIRE(myFENfile.good());
  ifstream myPGNfile("data/pgn/KASPAROV.PGN");
  REQUIRE(myPGNfile.good());
  ofstream outfile("data/masked/KASPAROV.masked.csv");
  REQUIRE(outfile.good());

  outfile << StatHeader() << endl;

  int cnt = 0;
  try {
    while (myFENfile.good() && myPGNfile.good()) {
      FENReader fenReader;
      myFENfile >> fenReader;

      PGNGame pgnReader;
      myPGNfile >> pgnReader;

      StatWriter statWriter;
      statWriter.convert(fenReader, pgnReader);

      DataMask masker;
      masker.mask(statWriter.lines());
      outfile << masker;

      cnt++;
    }
  }
  catch (exception& ex) {
    cout << ex.what() << endl;
    cout << "gamed matched: " << cnt << endl;
  }
}
