#include <fstream>
#include <iostream> // std::cout
#include <sstream>  // std::stringstream
#include <string>   // std::string

#include "../include/cpp_starter/game/ChessBishop.hpp"
#include "../include/cpp_starter/game/ChessBoard.hpp"
#include "../include/cpp_starter/game/ChessExceptions.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO("Verify ChessBishop correctly placed", "[ChessBoard]") {
  ChessBoard board;
  board.moveWhiteSymbol("d4");
  cout << board.draw() << endl;
  WhiteBishop bishop('c', '1');
  REQUIRE(bishop.moves().size() == 0);
  bishop.invalidate(&board);
  REQUIRE(bishop.moves().size() == 5);
  REQUIRE(bishop.moves()[0] == "d2");
  REQUIRE(bishop.moves()[1] == "e3");
  REQUIRE(bishop.moves()[2] == "f4");
  REQUIRE(bishop.moves()[3] == "g5");
  REQUIRE(bishop.moves()[4] == "h6");
}

SCENARIO("Verify ChessBishop incorrectly placed", "[ChessBoard]") {
  REQUIRE_THROWS_AS(WhiteBishop('a', '0'), OutOfBoundsException);
  REQUIRE_THROWS_AS(WhiteBishop('?', '0'), OutOfBoundsException);
  REQUIRE_THROWS_AS(BlackBishop('h', '9'), OutOfBoundsException);
  REQUIRE_THROWS_AS(BlackBishop('h', '?'), OutOfBoundsException);
}

SCENARIO("Verify ChessBishop calculate all possible positions",
  "[ChessBoard]") {
  ChessBoard board;
  board.move("a2a3");
  cout << board.draw() << endl;
  WhiteBishop bishop('a', '1');
  bishop.invalidate(&board);
  REQUIRE(bishop.moves().size() == 0);
}
