#include <fstream>
#include <iostream>// std::cout
#include <sstream>// std::stringstream
#include <string>// std::string

#include "../include/chessmind/game/ChessBoard.hpp"
#include "../include/chessmind/game/ChessExceptions.hpp"
#include "../include/chessmind/game/ChessKing.hpp"
#include "../include/chessmind/pgn/PGNGame.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO("Verify WhiteKing correctly placed", "[ChessBoard]")
{
  ChessBoard board;
  board.moveWhiteSymbol("e4");
  cout << board.draw() << endl;
  WhiteKing king('e', '1');
  REQUIRE(king.moves().size() == 0);
  king.invalidate(&board);
  REQUIRE(king.moves().size() == 1);
  REQUIRE(king.moves()[0] == "e2");
}

SCENARIO("Verify BlackKing correctly placed", "[ChessBoard]")
{
  ChessBoard board;
  board.moveBlackSymbol("e5");
  cout << board.draw() << endl;
  BlackKing king('e', '8');
  REQUIRE(king.moves().size() == 0);
  king.invalidate(&board);
  REQUIRE(king.moves().size() == 1);
  REQUIRE(king.moves()[0] == "e7");
}

SCENARIO("Verify ChessKing incorrectly placed", "[ChessBoard]")
{
  REQUIRE_THROWS_AS(WhiteKing('a', '0'), OutOfBoundsException);
  REQUIRE_THROWS_AS(WhiteKing('?', '0'), OutOfBoundsException);
  REQUIRE_THROWS_AS(BlackKing('h', '9'), OutOfBoundsException);
  REQUIRE_THROWS_AS(BlackKing('h', '?'), OutOfBoundsException);
}

SCENARIO("Verify WhiteKing correctly moved", "[ChessBoard]")
{
  ChessBoard board;
  board.moveWhiteSymbol("e4");
  cout << board.draw() << endl;
  WhiteKing king('e', '1');
  REQUIRE(king.moves().size() == 0);
  king.invalidate(&board);
  REQUIRE(king.moves().size() == 1);
  REQUIRE_THROWS_AS(board.moveWhiteSymbol("Ke3"), NoAvailableMovesException);
  board.moveWhiteSymbol("Ke2");
  cout << board.draw() << endl;
}

SCENARIO("Verify BlackKing correctly moved", "[ChessBoard]")
{
  ChessBoard board;
  board.moveBlackSymbol("e5");
  cout << board.draw() << endl;
  BlackKing king('e', '8');
  REQUIRE(king.moves().size() == 0);
  king.invalidate(&board);
  REQUIRE(king.moves().size() == 1);
  REQUIRE_THROWS_AS(board.moveBlackSymbol("Ke6"), NoAvailableMovesException);
  board.moveBlackSymbol("Ke7");
  cout << board.draw() << endl;
}

SCENARIO("Verify WhiteKing can castle", "[ChessBoard]")
{
  ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  ChessBoard board;
  board = game.playGameUntil(board, "O-O");
  board.moveWhiteSymbol("O-O");
  cout << board.draw();
}