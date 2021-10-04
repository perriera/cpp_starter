#include <fstream>
#include <iostream> // std::cout
#include <sstream>  // std::stringstream
#include <string>   // std::string

#include "../include/cpp_starter/game/ChessBoard.hpp"
#include "../include/cpp_starter/game/ChessExceptions.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO(
  "Verify ChessBoard can movetext in Standard Algebraic Notation (SAN) White",
  "[ChessBoard]") {
  ChessBoard board;
  cout << board.draw();
  REQUIRE(board.symbolAt("e2") == 'p');
  REQUIRE(board.symbolAt("e4") == ' ');
  board.moveWhiteSymbol("e4");
  REQUIRE(board.symbolAt("e2") == ' ');
  REQUIRE(board.symbolAt("e4") == 'p');
  cout << board.draw();
}

SCENARIO(
  "Verify ChessBoard can movetext in Standard Algebraic Notation (SAN) Black",
  "[ChessBoard]") {
  ChessBoard board;
  cout << board.draw();
  REQUIRE(board.symbolAt("e7") == 'P');
  REQUIRE(board.symbolAt("e5") == ' ');
  board.moveBlackSymbol("e5");
  REQUIRE(board.symbolAt("e7") == ' ');
  REQUIRE(board.symbolAt("e5") == 'P');
  cout << board.draw();
}

SCENARIO("Verify ChessBoard can do two moves", "[ChessBoard]") {
  ChessBoard board;
  cout << board.draw();
  REQUIRE(board.symbolAt("e2") == 'p');
  REQUIRE(board.symbolAt("e4") == ' ');
  REQUIRE(board.symbolAt("e7") == 'P');
  REQUIRE(board.symbolAt("e5") == ' ');
  board.moveWhiteSymbol("e4");
  board.moveBlackSymbol("e5");
  REQUIRE(board.symbolAt("e2") == ' ');
  REQUIRE(board.symbolAt("e4") == 'p');
  REQUIRE(board.symbolAt("e7") == ' ');
  REQUIRE(board.symbolAt("e5") == 'P');
  cout << board.draw_inverted();
}

SCENARIO(
  "Verify ChessBoard can movetext (SAN) White can't make an impossible move",
  "[ChessBoard]") {
  ChessBoard board;
  cout << board.draw();
  REQUIRE(board.symbolAt("e2") == 'p');
  REQUIRE(board.symbolAt("e4") == ' ');
  //  REQUIRE_THROWS_AS(board.moveWhiteSymbol("e5"),NoAvailableMovesException);
}

SCENARIO(
  "Verify ChessBoard can movetext (SAN) Black can't make an impossible move",
  "[ChessBoard]") {
  ChessBoard board;
  cout << board.draw();
  REQUIRE(board.symbolAt("e7") == 'P');
  REQUIRE(board.symbolAt("e5") == ' ');
  //  REQUIRE_THROWS_AS(board.moveBlackSymbol("e4"),NoAvailableMovesException);
}
