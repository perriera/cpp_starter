#include <fstream>
#include <iostream>// std::cout
#include <sstream>// std::stringstream
#include <string>// std::string

#include "../include/cpp_starter/ai/CrossTableIO.hpp"
#include "../include/cpp_starter/ai/CrossTableLine.hpp"
#include "../include/cpp_starter/ai/CrossTableMap.hpp"
#include "../include/cpp_starter/blockchain/Block.hpp"
#include "../include/cpp_starter/fen/FENReader.hpp"
#include "../include/cpp_starter/stat/StatWriter.hpp"
#include "catch.hpp"
#include "extras/crc32_support.hpp"
#include "extras/crc64_support.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO("Verify CrossTableIO can replay a KASPAROV move", "[CrossTableIOX]")
{

  string filename = "data/ct/KASPAROV.csv";
  // string filename = "data/ctx/ALL.csv";
  ifstream myCTfile(filename);
  REQUIRE(myCTfile.good());
  CrossTableIO crossTableIO;
  myCTfile >> crossTableIO;
  crossTableIO.verbose(true);

  {
    FENLine fenLine(
      "rnbqkbnr/pp1ppppp/8/2p5/4P3/2N5/PPPP1PPP/R1BQKBNR b KQkq - 0 0");
    CrossTableLine replay = crossTableIO.predict(fenLine);
    auto moves = replay.moves_size();
    REQUIRE(moves >= 4);
  }

  {
    FENLine fenLine(
      "rnbqkbnr/pp1ppppp/8/2p5/4P3/2N5/PPPP2PP/R1BQKBNR b KQkq - 0 0");
    REQUIRE_THROWS_AS(crossTableIO.predict(fenLine), CrossTableException);
  }

  {
    FENLine fenLine("2q3k1/7p/2p2Qp1/3p2K1/3Pp2P/4P3/5PP1/8 b - - 0 0");
    auto moves = crossTableIO.predict(fenLine);
    REQUIRE(moves.moves_size() > 0);
  }

  {
    FENLine fenLine("3b4/1q3kpp/1Np2p2/p1Pp1Pn1/P2P1B2/4Q2P/6P1/6K1 b - - 0 0");
    auto moves = crossTableIO.predict(fenLine).moves_size();
    REQUIRE(moves > 0);
  }
}

SCENARIO("Verify CrossTableIO (test every move)", "[CrossTableIOX]")
{

  string filename = "data/ct/KASPAROV.csv";
  CrossTableIO crossTableIO;
  ifstream myCTfile(filename);
  REQUIRE(myCTfile.good());
  myCTfile >> crossTableIO;

  {
    ifstream myCTfile(filename);
    REQUIRE(myCTfile.good());
    string text;
    getline(myCTfile, text);
    while (true) {
      CrossTableLine cursor;
      myCTfile >> cursor;
      if (!myCTfile.good())
        break;
      StatLine statLine = cursor;
      FENLine fenLine = statLine;
      cout << fenLine.layout() << endl;
      auto results = crossTableIO.predict(fenLine);
      REQUIRE(results.moves_size() > 0);
      cout << results << endl;
    }
  }
}

SCENARIO("Verify CrossTableIO (test ALL_X_Y(fixed).csv)", "[CrossTableIOX]")
{
  string filename = "data/ctx/ALL_X&Y.csv";
  // string filename = "data/ct/KASPAROV.csv";
  ifstream myCTfile(filename);
  REQUIRE(myCTfile.good());
  CrossTableIO crossTableIO;
  myCTfile >> crossTableIO;
  crossTableIO.verbose(true);

  {
    FENLine fenLine(
      "rnbqkbnr/pp1ppppp/8/2p5/4P3/2N5/PPPP1PPP/R1BQKBNR b KQkq - 0 0");
    CrossTableLine replay = crossTableIO.predict(fenLine);
    REQUIRE(replay.moves_size() > 4);
  }

  {
    FENLine fenLine(
      "rnbqkbnr/pp1ppppp/8/2p5/4P3/2N5/PPPP2PP/R1BQKBNR b KQkq - 0 0");
    REQUIRE_THROWS_AS(crossTableIO.predict(fenLine), CrossTableException);
  }

  {
    FENLine fenLine("2q3k1/7p/2p2Qp1/3p2K1/3Pp2P/4P3/5PP1/8 b - - 0 0");
    REQUIRE(crossTableIO.predict(fenLine).moves_size() > 0);
  }

  {
    FENLine fenLine("3b4/1q3kpp/1Np2p2/p1Pp1Pn1/P2P1B2/4Q2P/6P1/6K1 b - - 0 0");
    REQUIRE(crossTableIO.predict(fenLine).moves_size() > 0);
  }
}

SCENARIO("Verify CrossTableIO can replay a ALL.scv move", "[CrossTableIOX]")
{

  string filename = "data/ctx/ALL.csv";
  ifstream myCTfile(filename);
  REQUIRE(myCTfile.good());
  CrossTableIO crossTableIO;
  myCTfile >> crossTableIO;
  crossTableIO.verbose(true);

  {
    FENLine fenLine(
      "rnbqkbnr/pp1ppppp/8/2p5/4P3/2N5/PPPP1PPP/R1BQKBNR b KQkq - 0 0");
    CrossTableLine replay = crossTableIO.predict(fenLine);
    auto moves = replay.moves_size();
    REQUIRE(moves >= 5);
  }

  {
    FENLine fenLine(
      "rnbqkbnr/pp1ppppp/8/2p5/4P3/2N5/PPPP2PP/R1BQKBNR b KQkq - 0 0");
    REQUIRE_THROWS_AS(crossTableIO.predict(fenLine), CrossTableException);
  }

  {
    FENLine fenLine("2q3k1/7p/2p2Qp1/3p2K1/3Pp2P/4P3/5PP1/8 b - - 0 0");
    auto moves = crossTableIO.predict(fenLine).moves_size();
    REQUIRE(moves > 0);
  }

  {
    FENLine fenLine("3b4/1q3kpp/1Np2p2/p1Pp1Pn1/P2P1B2/4Q2P/6P1/6K1 b - - 0 0");
    auto moves = crossTableIO.predict(fenLine).moves_size();
    REQUIRE(moves > 0);
  }
}
