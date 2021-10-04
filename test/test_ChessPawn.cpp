#include <fstream>
#include <iostream>// std::cout
#include <sstream>// std::stringstream
#include <string>// std::string

#include "../include/cpp_starter/game/ChessBoard.hpp"
#include "../include/cpp_starter/game/ChessExceptions.hpp"
#include "../include/cpp_starter/game/ChessPawn.hpp"
#include "../include/cpp_starter/pgn/PGNGame.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO("Verify White ChessPawn correctly placed", "[ChessBoard]")
{
  ChessBoard board;
  WhitePawn pawn('a', '2');
  REQUIRE(pawn.moves().size() == 0);
  pawn.invalidate(&board);
  REQUIRE(pawn.moves().size() == 2);
  REQUIRE(pawn.moves()[0] == "a3");
  REQUIRE(pawn.moves()[1] == "a4");
  // REQUIRE(pawn.black_or_white()==true);
}

SCENARIO("Verify Black ChessPawn correctly placed", "[ChessBoard]")
{
  ChessBoard board;
  BlackPawn pawn('a', '7');
  REQUIRE(pawn.moves().size() == 0);
  pawn.invalidate(&board);
  REQUIRE(pawn.moves().size() == 2);
  REQUIRE(pawn.moves()[0] == "a6");
  REQUIRE(pawn.moves()[1] == "a5");
  // REQUIRE(pawn.black_or_white()==false);
}

SCENARIO("Verify ChessPawn incorrectly placed", "[ChessBoard]")
{
  REQUIRE_THROWS_AS(WhitePawn('a', '0'), OutOfBoundsException);
  REQUIRE_THROWS_AS(WhitePawn('?', '0'), OutOfBoundsException);
  REQUIRE_THROWS_AS(BlackPawn('h', '9'), OutOfBoundsException);
  REQUIRE_THROWS_AS(BlackPawn('h', '?'), OutOfBoundsException);
}

SCENARIO("Verify ChessPawn calculate all possible positions", "[ChessBoard]")
{
  ChessBoard board;
  WhitePawn pawn('a', '2');
  auto moves = pawn.allCalculatedMoves(&board);
  REQUIRE(moves.size() == 2);
  REQUIRE(moves[0] == "a3");
  REQUIRE(moves[1] == "a4");
}

SCENARIO("Verify ChessPawn can get a chess piece class for a location",
  "[ChessBoard]")
{
  ChessBoard board;
  cout << board.draw();
  ChessPiece chessPiece = board.pieceAt('e', '2');
  REQUIRE(chessPiece.col() == 'e');
  REQUIRE(chessPiece.row() == '2');
  REQUIRE(chessPiece.moves().size() == 2);
  REQUIRE(chessPiece.moves()[0] == "e3");
  REQUIRE(chessPiece.moves()[1] == "e4");
}

SCENARIO("Verify ChessPawn can execute 'exd4'", "[PGNotation]")
{
  ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  ChessBoard board;
  board = game.playGameUntil(board, "exd4");
  REQUIRE(board.symbolAt("d4") == 'p');
  REQUIRE(board.symbolAt("e5") == 'P');
  board.moveBlackSymbol("exd4");
  cout << board.draw();
  REQUIRE(board.symbolAt("d4") == 'P');
  REQUIRE(board.symbolAt("e5") == ' ');
}
