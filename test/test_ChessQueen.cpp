#include <fstream>
#include <iostream> // std::cout
#include <sstream>  // std::stringstream
#include <string>   // std::string

#include "../include/chessmind/game/ChessBoard.hpp"
#include "../include/chessmind/game/ChessExceptions.hpp"
#include "../include/chessmind/game/ChessQueen.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO("Verify WhiteQueen correctly placed", "[ChessBoard]") {
  ChessBoard board;
  board.moveWhiteSymbol("e4");
  cout << board.draw() << endl;
  WhiteQueen queen('d', '1');
  REQUIRE(queen.moves().size() == 0);
  queen.invalidate(&board);
  REQUIRE(queen.moves().size() == 4);
  REQUIRE(queen.moves()[0] == "e2");
  REQUIRE(queen.moves()[1] == "f3");
  REQUIRE(queen.moves()[2] == "g4");
  REQUIRE(queen.moves()[3] == "h5");
}

SCENARIO("Verify BlackQueen correctly placed", "[ChessBoard]") {
  ChessBoard board;
  board.moveBlackSymbol("e5");
  cout << board.draw() << endl;
  BlackQueen queen('d', '8');
  REQUIRE(queen.moves().size() == 0);
  queen.invalidate(&board);
  REQUIRE(queen.moves().size() == 4);
  REQUIRE(queen.moves()[0] == "e7");
  REQUIRE(queen.moves()[1] == "f6");
  REQUIRE(queen.moves()[2] == "g5");
  REQUIRE(queen.moves()[3] == "h4");
}

SCENARIO("Verify ChessQueen incorrectly placed", "[ChessBoard]") {
  REQUIRE_THROWS_AS(WhiteQueen('a', '0'), OutOfBoundsException);
  REQUIRE_THROWS_AS(WhiteQueen('?', '0'), OutOfBoundsException);
  REQUIRE_THROWS_AS(BlackQueen('h', '9'), OutOfBoundsException);
  REQUIRE_THROWS_AS(BlackQueen('h', '?'), OutOfBoundsException);
}

SCENARIO("Verify WhiteQueen correctly moved", "[ChessBoard]") {
  ChessBoard board;
  board.moveWhiteSymbol("e4");
  cout << board.draw() << endl;
  WhiteQueen queen('d', '1');
  REQUIRE(queen.moves().size() == 0);
  queen.invalidate(&board);
  REQUIRE(queen.moves().size() == 4);
  board.moveWhiteSymbol("Qg4");
  cout << board.draw() << endl;
}

SCENARIO("Verify BlackQueen correctly moved", "[ChessBoard]") {
  ChessBoard board;
  board.moveBlackSymbol("e5");
  cout << board.draw() << endl;
  BlackQueen queen('d', '8');
  REQUIRE(queen.moves().size() == 0);
  queen.invalidate(&board);
  REQUIRE(queen.moves().size() == 4);
  board.moveBlackSymbol("Qg5");
  cout << board.draw() << endl;
}