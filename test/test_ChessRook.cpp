#include <fstream>
#include <iostream> // std::cout
#include <sstream>  // std::stringstream
#include <string>   // std::string

#include "../include/cpp_starter/game/ChessBoard.hpp"
#include "../include/cpp_starter/game/ChessExceptions.hpp"
#include "../include/cpp_starter/game/ChessRook.hpp"
#include "../include/cpp_starter/pgn/PGNGame.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO("Verify ChessRook correctly placed", "[ChessRook]") {
  ChessBoard board;
  board.move("a2a3");
  cout << board.draw() << endl;
  WhiteRook rook('a', '1');
  REQUIRE(rook.moves().size() == 0);
  rook.invalidate(&board);
  REQUIRE(rook.moves().size() == 1);
  REQUIRE(rook.moves()[0] == "a2");
  ChessPiece rightRook = board.pieceAt("a1");
  REQUIRE(rightRook.moves()[0] == "a2");
}

SCENARIO("Verify ChessRook incorrectly placed", "[ChessRook]") {
  REQUIRE_THROWS_AS(WhiteRook('a', '0'), OutOfBoundsException);
  REQUIRE_THROWS_AS(WhiteRook('?', '0'), OutOfBoundsException);
  REQUIRE_THROWS_AS(BlackRook('h', '9'), OutOfBoundsException);
  REQUIRE_THROWS_AS(BlackRook('h', '?'), OutOfBoundsException);
}

SCENARIO("Verify ChessRook calculate all possible positions", "[ChessRook]") {
  ChessBoard board;
  board.move("a2a3");
  cout << board.draw() << endl;
  WhiteRook rook('a', '1');
  rook.invalidate(&board);
  REQUIRE(rook.moves().size() == 1);
  REQUIRE(rook.moves()[0] == "a2");
}

SCENARIO("Verify ChessRook jumps correctly", "[ChessRook]") {
  ifstream myfile("data/pgn/KASPAROV.PGN");
  REQUIRE(myfile.good());
  PGNGames games;
  myfile >> games;
  REQUIRE(games.size() == 2400);

  int cnt = 0;
  for (auto game : games.games()) {
    cout << game.parameters() << endl;
    ChessBoard board;
    try {
      board = game.playGameUntil(board, "Rc6");
      cout << board.draw();
      REQUIRE(board.symbolAt("h6") == 'r');
      REQUIRE(board.symbolAt("c4") == 'r');
      REQUIRE(board.symbolAt("c6") == ' ');
      ChessPiece wrongRook = board.pieceAt("h6");
      ChessPiece rightRook = board.pieceAt("c4");
      board.moveWhiteSymbol("Rc6");
      cout << board.draw();
      REQUIRE(board.symbolAt("h6") == 'r');
      REQUIRE(board.symbolAt("c4") == ' ');
      REQUIRE(board.symbolAt("c6") == 'r');
      break;
    }
    catch (exception& ex) {
      cout << game.parameters() << endl;
      cout << ex.what() << " Game No: " << cnt << endl;
      cout << endl;
    }
    cout << " Game No: " << cnt << endl;
  }
}
