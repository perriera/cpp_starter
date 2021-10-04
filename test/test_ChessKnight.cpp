#include <fstream>
#include <iostream> // std::cout
#include <sstream>  // std::stringstream
#include <string>   // std::string

#include "../include/cpp_starter/game/ChessBoard.hpp"
#include "../include/cpp_starter/game/ChessExceptions.hpp"
#include "../include/cpp_starter/game/ChessKnight.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO("Verify ChessKnight correctly placed", "[ChessBoard]") {
  ChessBoard board;
  WhiteKnight knight('b', '1');
  REQUIRE(knight.moves().size() == 0);
  knight.invalidate(&board);
  REQUIRE(knight.moves().size() == 2);
  REQUIRE(knight.moves()[0] == "c3");
  REQUIRE(knight.moves()[1] == "a3");
}

SCENARIO("Verify ChessKnight incorrectly placed", "[ChessBoard]") {
  REQUIRE_THROWS_AS(WhiteKnight('a', '0'), OutOfBoundsException);
  REQUIRE_THROWS_AS(WhiteKnight('?', '0'), OutOfBoundsException);
  REQUIRE_THROWS_AS(BlackKnight('h', '9'), OutOfBoundsException);
  REQUIRE_THROWS_AS(BlackKnight('h', '?'), OutOfBoundsException);
}

SCENARIO("Verify ChessKnight calculate all possible positions",
  "[ChessBoard]") {
  ChessBoard board;
  WhiteKnight knight('b', '1');
  auto moves = knight.allCalculatedMoves(&board);
  REQUIRE(moves.size() == 2);
  REQUIRE(moves[0] == "c3");
  REQUIRE(moves[1] == "a3");
}
