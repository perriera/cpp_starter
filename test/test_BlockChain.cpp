#include <fstream>
#include <iostream>// std::cout
#include <sstream>// std::stringstream
#include <string>// std::string

#include "../include/chessmind/ai/CrossTableIO.hpp"
#include "../include/chessmind/ai/CrossTableLine.hpp"
#include "../include/chessmind/ai/CrossTableMap.hpp"
#include "../include/chessmind/blockchain/Block.hpp"
#include "../include/chessmind/fen/FENReader.hpp"
#include "../include/chessmind/stat/StatWriter.hpp"
#include "catch.hpp"
// #include "extras/Directory.hpp"
// #include "extras/ansi_colors.hpp"
#include "extras/crc32_support.hpp"
#include "extras/crc64_support.hpp"
#include "extras/string_support.hpp"

using namespace std;

// SCENARIO("Verify CrossTableIO can replay a BlockChain move", "[BlockChain]")
// {

//   string filename = "data/ct/KASPAROV.csv";
//   ifstream myCTfile(filename);
//   REQUIRE(myCTfile.good());
//   CrossTableIO crossTableIO;
//   myCTfile >> crossTableIO;
//   crossTableIO.verbose(true);

//   // BlockInterface *y;

//   {
//     FENLine fenLine(
//       "rnbqkbnr/pp1ppppp/8/2p5/4P3/2N5/PPPP1PPP/R1BQKBNR b KQkq - 0 0");
//     CrossTableLine replay = crossTableIO.predict(fenLine);
//     REQUIRE(replay.moves_size() == 4);
//   }

//   {
//     FENLine fenLine(
//       "rnbqkbnr/pp1ppppp/8/2p5/4P3/2N5/PPPP2PP/R1BQKBNR b KQkq - 0 0");
//     REQUIRE_THROWS_AS(crossTableIO.predict(fenLine), CrossTableException);
//   }

//   {
//     FENLine fenLine("2q3k1/7p/2p2Qp1/3p2K1/3Pp2P/4P3/5PP1/8 b - - 0 0");
//     REQUIRE(crossTableIO.predict(fenLine).moves_size() > 0);
//   }

//   {
//     FENLine fenLine("3b4/1q3kpp/1Np2p2/p1Pp1Pn1/P2P1B2/4Q2P/6P1/6K1 b - - 0 0");
//     auto result = crossTableIO.predict(fenLine);
//     REQUIRE(result.moves_size() > 0);
//   }
// }
