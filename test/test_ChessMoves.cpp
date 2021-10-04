#include <fstream>
#include <iostream>// std::cout
#include <sstream>// std::stringstream
#include <string>// std::string

#include "../include/cpp_starter/game/ChessBoard.hpp"
#include "../include/cpp_starter/game/ChessExceptions.hpp"
#include "../include/cpp_starter/game/ChessMoves.hpp"
#include "../include/cpp_starter/game/ChessPosition.hpp"
#include "../include/cpp_starter/pgn/PGNGame.hpp"
#include "../include/cpp_starter/pgn/PGNotation.hpp"
#include "../include/cpp_starter/pgn/notation/TypeCastle.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO("Verify ChessMove", "[ChessMove]")
{

  GIVEN("constructor")
  {
    ChessMove move("e2e4");
    // test2
    REQUIRE(move == "e2e4");
    REQUIRE_THROWS_AS(ChessMove("?1e4"), ChessMoveException);
    REQUIRE_THROWS_AS(ChessMove("e1i4"), ChessMoveException);
    REQUIRE_THROWS_AS(ChessMove("e0i4"), ChessMoveException);
    REQUIRE_THROWS_AS(ChessMove("e0e9"), ChessMoveException);
    REQUIRE_THROWS_AS(ChessMove("e"), ChessMoveException);
    REQUIRE_THROWS_AS(ChessMove("eeeee"), ChessMoveException);
  }
  GIVEN("read/write stream")
  {
    ChessMove move;
    stringstream ss;
    ss << "e2e4";
    ss >> move;
    REQUIRE(move == "e2e4");
    REQUIRE(move != "e4e2");
  }
  GIVEN("assigment to string")
  {
    ChessMove move;
    move = "e2e4";
    REQUIRE(move == "e2e4");
  }
  GIVEN("assigment to another")
  {
    ChessMove a("e2e4");
    ChessMove b;
    b = a;
    REQUIRE(a == b);
  }
  GIVEN("not equal")
  {
    ChessMove a("a2g5");
    ChessMove b("a2g4");
    REQUIRE(a != b);
  }
  GIVEN("ChessPosition stream testing")
  {
    string columns = "a1b2c3d4";
    stringstream ss;
    ss << columns;
    int cnt = 0;
    while (true) {
      ChessMove cc;
      ss >> cc;
      if (!ss.good())
        break;
      cout << cc << flush;
      cnt++;
    }
    REQUIRE(cnt == columns.size() / 4);
  }
  GIVEN("a & b")
  {
    ChessMove chessMove("e2e4");
    REQUIRE(chessMove.a() == "e2");
    REQUIRE(chessMove.b() == "e4");
  }
}

SCENARIO("Verify ChessMoves", "[ChessMove]")
{

  GIVEN("we have multple ChessMove instances")
    WHEN("we put those instances inside ChessMoves")
    THEN("we easily retrieve them for later")
  {
    ChessMoves moves;
    moves.push_back("e2e4");
    REQUIRE(moves.front() == "e2e4");
  }
}

SCENARIO("Verify ChessMoves (select moves of starting column)", "[ChessMove]")
{

  GIVEN("we have multple ChessMove instances")
    WHEN("we need to find only those moves that belong to a particular column")
    THEN("we need to retrieve only those moves that start from that column")
  {
    ifstream myfile("data/pgn/kasparov_privorotsky_1974.pgn");
    REQUIRE(myfile.good());
    PGNGame game;
    myfile >> game;
    ChessBoard board;
    try {
      ChessBoard board;
      board = game.playGameUntil(board, "cxd4");
      REQUIRE(board.symbolAt("c5") == 'P');
      REQUIRE(board.symbolAt("e5") == 'P');
      REQUIRE(board.symbolAt("d4") == 'b');
      cout << board.draw();
      board.moveBlackSymbol("cxd4");
      GIVEN("we have multple ChessMove instances")
      {
        ChessMoves allMoves = { "c5d4", "e5d4" };
        ChessMoves selected = selectColumns(allMoves, 'c');
      }
      cout << board.draw();
      REQUIRE(board.symbolAt("c5") == ' ');
      REQUIRE(board.symbolAt("e5") == 'P');
      REQUIRE(board.symbolAt("d4") == 'P');
    }
    catch (exception& ex) {
      cout << game.parameters() << endl;
      cout << ex.what() << endl;
      cout << endl;
    }
  }
}

SCENARIO("Verify ChessMove octals", "[ChessMove]")
{
  GIVEN("toOctal")
  {
    ChessMove pos("e2e4");
    int test = pos.toOctal();
    REQUIRE(pos == "e2e4");
    REQUIRE(test == 4143);
  }
  GIVEN("fromOctal")
  {
    ChessMove pos;
    REQUIRE(pos == "a1a1");
    pos.fromOctal(4143);
    REQUIRE(pos == "e2e4");
  }
}
