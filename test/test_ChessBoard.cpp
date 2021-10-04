#include <fstream>
#include <iostream>// std::cout
#include <sstream>// std::stringstream
#include <string>// std::string

#include "../include/chessmind/game/ChessBoard.hpp"
#include "../include/chessmind/game/ChessExceptions.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

static void test_board(istream &in)
{
  ChessBoard board;
  in >> board;
}

SCENARIO("Verify ChessBoard can be read PGN file", "[ChessBoard]")
{
  ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
  REQUIRE(myfile.good());
  REQUIRE_THROWS_AS(test_board(myfile), PGNFormatDetectedException);
}

SCENARIO("Verify ChessBoard can draw a chess board", "[ChessBoard]")
{
  ChessBoard board;
  cout << board.draw();
}

SCENARIO("Verify ChessBoard can draw a chess board inverted", "[ChessBoard]")
{
  ChessBoard board;
  cout << board.draw_inverted();
}

SCENARIO("Verify ChessBoard has pieces in correct spot", "[ChessBoard]")
{
  ChessBoard board;
  REQUIRE(board.symbolAt('a', '8') == 'R');
  REQUIRE(board.symbolAt('a', '1') == 'r');
  REQUIRE(board.symbolAt('h', '1') == 'r');
  REQUIRE(board.symbolAt('h', '8') == 'R');
  REQUIRE(board.symbolAt("b1") == 'n');
  REQUIRE(board.symbolAt("b8") == 'N');
}

SCENARIO("Verify ChessBoard can detect a bad position", "[ChessBoard]")
{
  ChessBoard board;
  REQUIRE_THROWS_AS(board.symbolAt('a', '0'), OutOfBoundsException);
  REQUIRE_THROWS_AS(board.symbolAt('0', '1'), OutOfBoundsException);
  REQUIRE_THROWS_AS(board.symbolAt('i', '1'), OutOfBoundsException);
  REQUIRE_THROWS_AS(board.symbolAt('a', '9'), OutOfBoundsException);
}

SCENARIO("Verify ChessBoard can detect a bad move", "[ChessBoard]")
{
  ChessBoard board;
  REQUIRE_THROWS_AS(board.move("?2e4"), OutOfBoundsException);
  REQUIRE_THROWS_AS(board.move("e?e4"), OutOfBoundsException);
  REQUIRE_THROWS_AS(board.move("e2?4"), OutOfBoundsException);
  REQUIRE_THROWS_AS(board.move("e2e?"), OutOfBoundsException);
}

SCENARIO("Verify ChessBoard can move a chess piece", "[ChessBoard]")
{
  ChessBoard board;
  cout << board.draw();
  REQUIRE(board.symbolAt("e2") == 'p');
  REQUIRE(board.symbolAt("e4") == ' ');
  board.move("e2e4");
  REQUIRE(board.symbolAt("e2") == ' ');
  REQUIRE(board.symbolAt("e4") == 'p');
  cout << board.draw();
}
