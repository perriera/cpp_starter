#include <fstream>
#include <iostream>// std::cout
#include <map>
#include <sstream>// std::stringstream
#include <string>// std::string

#include "../include/chessmind/fen/FENReader.hpp"
#include "../include/chessmind/pgn/PGNGame.hpp"
#include "../include/chessmind/stat/StatWriter.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO("Verify StatWriter", "[StatWriter]")
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

  ofstream outfile("data/csv/kasparov_muratkuliev_1973.csv");
  REQUIRE(outfile.good());
  outfile << statWriter.csv_out();
}

SCENARIO("Verify StatWriter SetSAN", "[StatWriter]")
{
  ifstream myFENfile("data/fen/kasparov_tal_1980.fen");
  REQUIRE(myFENfile.good());
  FENReader fenReader;
  myFENfile >> fenReader;
  cout << fenReader.lines().size() << endl;
  REQUIRE(fenReader.lines().size() == 55);

  ifstream myPGNfile("data/pgn/kasparov_tal_1980.pgn");
  REQUIRE(myPGNfile.good());
  PGNGame pgnGame;
  myPGNfile >> pgnGame;
  cout << pgnGame.pgnmoves().size() << endl;
  REQUIRE(pgnGame.pgnmoves().size() == 27);

  StatWriter statWriter;
  statWriter.convert(fenReader, pgnGame);

  ofstream outfile("data/csv/kasparov_tal_1980.csv");
  REQUIRE(outfile.good());
  outfile << statWriter.csv_out();
}

SCENARIO("Verify StatWriter ('KASPAROV.FEN') EOF", "[StatWriter]")
{
  REQUIRE(true);
}

SCENARIO("Verify StatWriter ('KASPAROV.FEN')", "[StatWriter]")
{
  ifstream myFENfile("data/fen/KASPAROV.FEN");
  REQUIRE(myFENfile.good());
  ifstream myPGNfile("data/pgn/KASPAROV.PGN");
  REQUIRE(myPGNfile.good());
  ofstream outfile("data/csv/KASPAROV.csv");
  REQUIRE(outfile.good());

  int cnt = 0;
  try {
    while (myFENfile.good() && myPGNfile.good()) {
      FENReader fenReader;
      myFENfile >> fenReader;

      PGNGame pgnGame;
      myPGNfile >> pgnGame;

      StatWriter statWriter;
      statWriter.convert(fenReader, pgnGame);

      outfile << statWriter.csv_out();
      cnt++;
    }
  }
  catch (exception& ex) {
    cout << ex.what() << endl;
    cout << "gamed matched: " << cnt << endl;
  }
}

SCENARIO("Verify StatWriter i/o streams", "[StatWriter]")
{
  ifstream myFENfile("data/fen/KASPAROV.FEN");
  REQUIRE(myFENfile.good());
  ifstream myPGNfile("data/pgn/KASPAROV.PGN");
  REQUIRE(myPGNfile.good());

  int cnt = 0;
  try {
    while (myFENfile.good() && myPGNfile.good()) {
      FENReader fenReader;
      myFENfile >> fenReader;

      PGNGame pgnGame;
      myPGNfile >> pgnGame;

      StatWriter statWriter;
      statWriter.convert(fenReader, pgnGame);

      string sample_file = "data/stat/KASPAROV.stat";
      {
        ofstream outfile(sample_file);
        REQUIRE(outfile.good());
        outfile << statWriter;
      }

      StatWriter testWriter;
      {
        ifstream infile(sample_file);
        REQUIRE(infile.good());
        infile >> testWriter;
      }
      REQUIRE(testWriter == statWriter);

      cout << cnt++ << endl;
    }
  }
  catch (exception& ex) {
    cout << ex.what() << endl;
    cout << "gamed matched: " << cnt << endl;
  }
}
