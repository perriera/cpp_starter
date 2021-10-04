#include <fstream>
#include <iostream>// std::cout
#include <sstream>// std::stringstream
#include <string>// std::string
#include <filesystem>

#include "../include/chessmind/ai/CrossTableLine.hpp"
#include "../include/chessmind/ai/CrossTableMap.hpp"
#include "../include/chessmind/fen/FENReader.hpp"
#include "../include/chessmind/stat/StatWriter.hpp"
#include "catch.hpp"
#include "extras/files.hpp"
#include "extras/ansi_colors.hpp"
#include "extras/crc32_support.hpp"
#include "extras/crc64_support.hpp"
#include "extras/string_support.hpp"

using namespace std;
using namespace extras;
namespace fs = std::filesystem;

/**
 * @brief Verify CrossTableMap ('KASPAROV.ct')
 *
 * Document test
 *
 */
SCENARIO("Verify CrossTableMap (generate 'KASPAROV.ct')", "[CrossTableMap]")
{
  ifstream myFENfile("data/fen/KASPAROV.FEN");
  REQUIRE(myFENfile.good());
  ifstream myPGNfile("data/pgn/KASPAROV.PGN");
  REQUIRE(myPGNfile.good());

  CrossTableMap crossTableMap;

  try {
    while (myFENfile.good() && myPGNfile.good()) {
      FENReader fenReader;
      myFENfile >> fenReader;

      PGNGame pgnReader;
      myPGNfile >> pgnReader;

      StatWriter statWriter;
      statWriter.convert(fenReader, pgnReader);

      auto statLines = statWriter.lines();
      crossTableMap.train(statLines);
    }
  }
  catch (exception& ex) {
    cout << ex.what() << endl;
  }

  string filename = "data/ct/KASPAROV.csv";
  {
    ofstream myCTfile(filename);
    REQUIRE(myCTfile.good());
    myCTfile << crossTableMap;
  }
  {
    ifstream myCTfile(filename);
    REQUIRE(myCTfile.good());
    CrossTableMap crossTableMap2;
    myCTfile >> crossTableMap2;
    REQUIRE(crossTableMap2 == crossTableMap);
  }
}

/**
 * @brief Verify CrossTableMap ('KASPAROV.ct')
 *
 * Depends on previoius tet.
 *
 */
SCENARIO("Verify CrossTableMap (reload 'KASPAROV.ct')", "[CrossTableMap]")
{

  ifstream myFENfile("data/fen/KASPAROV.FEN");
  REQUIRE(myFENfile.good());
  string filename = "data/ct/KASPAROV.csv";
  ifstream myCTfile(filename);
  REQUIRE(myCTfile.good());
  CrossTableMap crossTableMap;
  myCTfile >> crossTableMap;

  while (myFENfile.good()) {
    FENReader fenReader;
    myFENfile >> fenReader;

    if (!myFENfile.good())
      break;

    auto fenLines = fenReader.lines();
    auto startingFenLine = fenLines[0];
    REQUIRE_THROWS_AS(crossTableMap.predict(startingFenLine),
      CrossTableMapException);
    int cnt1 = 0;
    int cnt2 = 0;
    for (FENLine fenLine : fenLines) {
      try {
        crossTableMap.predict(fenLine);
        cnt1++;
      }
      catch (CrossTableMapException& ex) {
        cnt2++;
      }
    }
    // REQUIRE(cnt1>0);
    // REQUIRE(cnt2==3);
  }
}

// rnbqkbnr/pp1ppppp/8/2p5/4P3/2N5/PPPP1PPP/R1BQKBNR b KQkq - c 0

SCENARIO("Verify CrossTableMap can replay a KASPAROV move",
  "[CrossTableMapX]")
{

  string filename = "data/ct/KASPAROV.csv";
  ifstream myCTfile(filename);
  REQUIRE(myCTfile.good());
  CrossTableMap crossTableMap;
  myCTfile >> crossTableMap;

  FENLine fenLine(
    "rnbqkbnr/pp1ppppp/8/2p5/4P3/2N5/PPPP1PPP/R1BQKBNR b KQkq - Z 0");
  CrossTableLine replay = crossTableMap.predict(fenLine);

  REQUIRE(replay.moves_size() == 4);
}

SCENARIO("Test Directory class", "[CrossTableMap]")
{
  Directory directory("data/pgn");
  for (auto entry : directory.listing())
    cout << entry << endl;
  REQUIRE(directory.listing().size() > 0);
}

// SCENARIO("Train CrossTableMap with ALL chess sets we have",
//   "[CrossTableMap]")
// {

//   CrossTableMap crossTableMap;
//   string filename = "data/ctx/ALL.csv";

//   std::string path = "data/pgn";
//   for (const auto &entry : fs::directory_iterator(path)) {
//     string pgn_file = entry.path();
//     string fen_file = replace_all(pgn_file, "PGN", "FEN");
//     fen_file = replace_all(fen_file, "pgn", "fen");

//     cout << pgn_file << ' ' << fen_file << endl;

//     ifstream myFENfile(fen_file);
//     ifstream myPGNfile(pgn_file);

//     try {
//       cout << "Adding " << pgn_file << ":";

//       while (myFENfile.good() && myPGNfile.good()) {
//         FENReader fenReader;
//         myFENfile >> fenReader;

//         PGNGame pgnReader;
//         myPGNfile >> pgnReader;

//         cout << fenReader.lines().size() << endl;
//         cout << pgnReader.moves().size() << endl;

//         if (fenReader.lines().size() < 3)
//           break;
//         if (pgnReader.moves().size() < 3)
//           break;

//         StatWriter statWriter;
//         statWriter.convert(fenReader, pgnReader);

//         auto statLines = statWriter.lines();
//         crossTableMap.train(statLines);
//       }
//       cout << endl;
//     } catch (exception &ex) {
//       cout << pgn_file << " done (or skipped) " << pgn_file << endl;
//       cout << ex.what() << endl;
//     }

//     cout << "Updating " << filename << " ... " << endl;

//     ofstream myCTfile(filename);
//     REQUIRE(myCTfile.good());
//     myCTfile << crossTableMap;

//     cout << "Updated " << filename << endl;
//   }

//   {
//     ifstream myCTfile(filename);
//     REQUIRE(myCTfile.good());
//     CrossTableMap crossTableMap2;
//     myCTfile >> crossTableMap2;
//     REQUIRE(crossTableMap2 == crossTableMap);
//   }
// }

// SCENARIO("Load up trained CrossTableMap, (compare)", "[CrossTableMapXY]")
// {
//   string filename = "data/ctx/ALL.csv";
//   ifstream myCTfile(filename);
//   REQUIRE(myCTfile.good());
//   CrossTableMap crossTableMap2;
//   myCTfile >> crossTableMap2;
//   CrossTableMap crossTableMap1 = crossTableMap2;
//   REQUIRE(crossTableMap2 == crossTableMap1);
// }

// SCENARIO("Load up trained CrossTableMap", "[CrossTableMapX]")
// {

//     ifstream before("data/ctx/ALL_X_Y.csv");
//     ofstream after("data/ctx/ALL_X_Y(fixed).csv");
//     while(before.good()) {
//         string line;
//         getline(before,line);
//         line = replace_all(line,"-0", "- 0");
//         after << line << endl;
//     }
// }

// SCENARIO("Load up trained CrossTableMap", "[CrossTableMap]")
// {
//     ifstream in("data/ctx/ALL_X_Y(fixed).csv");
//     REQUIRE(in.good());
//     CrossTableMap crossTableMap;
//     in >> crossTableMap;
//     cout << crossTableMap.size() << endl;
//     REQUIRE(crossTableMap.size() == crossTableMap.size());
// }

SCENARIO("Load up trained CrossTableMap", "[CrossTableMap]")
{

  ifstream in("data/ctx/ALL_X_Y(fixed).csv");
  size_t max = 0;
  while (in.good()) {
    string line;
    getline(in, line);
    if (line.size() > max) {
      max = line.size();
      cout << line << endl;
    }
  }
  cout << max << endl;
}
