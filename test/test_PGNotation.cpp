#include <fstream>
#include <iostream>// std::cout
#include <sstream>// std::stringstream
#include <string>// std::string

#include "../include/chessmind/game/ChessBoard.hpp"
#include "../include/chessmind/game/ChessPosition.hpp"
#include "../include/chessmind/pgn/PGNGame.hpp"
#include "../include/chessmind/pgn/PGNotation.hpp"
#include "../include/chessmind/pgn/notation/TypeCastle.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO("Verify PGNotation can do (PGN Type1) 'e2'", "[PGNotation]")
{
  GIVEN("read/write stream")
  {
    PGNotation san;
    stringstream ss;
    ss << "e2";
    ss >> san;
    REQUIRE(san == "e2");
  }
  GIVEN("board.moveWhiteSymbol")
  {
    ChessBoard board;
    REQUIRE(board.symbolAt("e2") == 'p');
    REQUIRE(board.symbolAt("e4") == ' ');
    cout << board.draw();
    board.moveWhiteSymbol("e4");
    cout << board.draw();
    REQUIRE(board.symbolAt("e2") == ' ');
    REQUIRE(board.symbolAt("e4") == 'p');
  }
}

SCENARIO("Verify PGNotation can play (PGN Type1) all white pawns",
  "[PGNotation]")
{
  ChessBoard board;
  for (char col = 'a'; col < 'i'; col++) {
    ChessPosition from(col, '2');
    ChessPosition to(col, '4');
    REQUIRE(board.symbolAt(from) == 'p');
    REQUIRE(board.symbolAt(to) == ' ');
    cout << board.draw();
    board.moveWhiteSymbol(to);
    cout << board.draw();
    REQUIRE(board.symbolAt(from) == ' ');
    REQUIRE(board.symbolAt(to) == 'p');
  }
}

SCENARIO("Verify PGNotation can read (PGN Type2) 'Nc3'", "[PGNotation]")
{
  PGNotation notation;
  stringstream ss;
  ss << "Nc3";
  ss >> notation;
  REQUIRE(notation == "Nc3");
  REQUIRE(notation.piece() == 'N');
  REQUIRE(notation.san() == "c3");
}

SCENARIO("Verify PGNotation can play (PGN Type2) 'Nc3'", "[PGNotation]")
{
  ChessBoard board;
  REQUIRE(board.symbolAt("b1") == 'n');
  REQUIRE(board.symbolAt("c3") == ' ');
  cout << board.draw();
  board.moveWhiteSymbol("Nc3");
  cout << board.draw();
  REQUIRE(board.symbolAt("b1") == ' ');
  REQUIRE(board.symbolAt("c3") == 'n');
}

SCENARIO("Verify PGNotation can play (PGN Type3) 'exd4'", "[PGNotation]")
{
  PGNotation notation;
  stringstream ss;
  ss << "exd4";
  ss >> notation;
  REQUIRE(notation == "exd4");
  REQUIRE(notation.piece() == 'e');
  REQUIRE(notation.san() == "d4");
}

SCENARIO("Verify PGNotation can execute 'exd4'", "[PGNotation]")
{
  ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  ChessBoard board;
  try {
    board = game.playGameUntil(board, "exd4");
    REQUIRE(board.symbolAt("d4") == 'p');
    REQUIRE(board.symbolAt("e5") == 'P');
    board.moveBlackSymbol("exd4");
    cout << board.draw();
    REQUIRE(board.symbolAt("d4") == 'P');
    REQUIRE(board.symbolAt("e5") == ' ');
  }
  catch (std::exception& ex) {
    cout << ex.what() << endl;
  }
}

SCENARIO("Verify PGNotation can execute kasparov_ivanchuk_1995.pgn",
  "[PGNotation]")
{
  ifstream myfile("data/pgn/kasparov_ivanchuk_1995.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  cout << game.pgnmoves().size() << endl;
  ChessBoard board;
  board = game.playGameEnd(board);
}

SCENARIO("Verify PGNotation can execute 'O-O'", "[PGNotation]")
{
  ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  ChessBoard board;
  board = game.playGameUntil(board, "O-O");
  REQUIRE(board.symbolAt("e1") == 'k');
  REQUIRE(board.symbolAt("f1") == ' ');
  REQUIRE(board.symbolAt("g1") == ' ');
  REQUIRE(board.symbolAt("h1") == 'r');
  cout << board.draw();
  board.moveWhiteSymbol("O-O");
  cout << board.draw();
  REQUIRE(board.symbolAt("e1") == ' ');
  REQUIRE(board.symbolAt("f1") == 'r');
  REQUIRE(board.symbolAt("g1") == 'k');
  REQUIRE(board.symbolAt("h1") == ' ');
}

SCENARIO("Verify PGNotation can play 'Bxc6'", "[PGNotation]")
{
  ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  ChessBoard board;
  board = game.playGameUntil(board, "Bxc6");
  REQUIRE(board.symbolAt("a4") == 'b');
  REQUIRE(board.symbolAt("c6") == 'N');
  board.moveWhiteSymbol("Bxc6");
  cout << board.draw();
  REQUIRE(board.symbolAt("a4") == ' ');
  REQUIRE(board.symbolAt("c6") == 'b');
}

SCENARIO("Verify PGNotation can play 'gxh6+' (check & enpassant)",
  "[PGNotation]")
{
  ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  ChessBoard board;
  board = game.playGameUntil(board, "h5");
  cout << board.draw();
  board.moveBlackSymbol("h5");
  cout << board.draw();
  REQUIRE(board.symbolAt("h6") == ' ');
  REQUIRE(board.symbolAt("h5") == 'P');
  REQUIRE(board.symbolAt("g5") == 'p');
  board.moveWhiteSymbol("gxh6+");
  cout << board.draw();
  REQUIRE(board.symbolAt("h6") == 'p');
  REQUIRE(board.symbolAt("h5") == ' ');
  REQUIRE(board.symbolAt("g5") == ' ');
}

SCENARIO("Verify PGNotation can do a Draw", "[PGNotation]")
{
  ifstream myfile("data/pgn/kengis_kasparov_1973.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  ChessBoard board;
  // board = game.playGameEnd(board);
  board = game.playGameUntil(board, "1/2-1/2");
  cout << board.draw();
  board.moveBlackSymbol("1/2-1/2");
  cout << board.draw();
}

SCENARIO("Verify PGNotation can play kasparov_vasilchenko_1973.pgn",
  "[PGNotation]")
{
  ifstream myfile("data/pgn/kasparov_vasilchenko_1973.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  ChessBoard board;
  board = game.playGameEnd(board);
}

SCENARIO("Verify PGNotation can play kasparov_averbakh_1974.pgn",
  "[PGNotation]")
{
  ifstream myfile("data/pgn/kasparov_averbakh_1974.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  ChessBoard board;
  try {
    ChessBoard board;
    board = game.playGameUntil(board, "c5");
    REQUIRE(board.symbolAt("c6") == 'P');
    REQUIRE(board.symbolAt("c5") == ' ');
    cout << board.draw();
    board.moveBlackSymbol("c5");
    cout << board.draw();
    REQUIRE(board.symbolAt("c6") == ' ');
    REQUIRE(board.symbolAt("c5") == 'P');
  }
  catch (exception& ex) {
    cout << game.parameters() << endl;
    cout << ex.what() << endl;
    cout << endl;
  }
}

SCENARIO(
  "Verify PGNotation can play rafael_sarkisov_kasparov_1974_N56.pgn, "
  "('b8=Q+')",
  "[PGNotation]")
{
  ifstream myfile("data/pgn/rafael_sarkisov_kasparov_1974_N56.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  ChessBoard board;
  try {
    ChessBoard board;
    board = game.playGameUntil(board, "b8=Q+");
    REQUIRE(board.symbolAt("b7") == 'p');
    REQUIRE(board.symbolAt("b8") == ' ');
    cout << board.draw();
    board.moveWhiteSymbol("b8=Q+");
    cout << board.draw();
    REQUIRE(board.symbolAt("b7") == ' ');
    REQUIRE(board.symbolAt("b8") == 'q');
  }
  catch (exception& ex) {
    cout << game.parameters() << endl;
    cout << ex.what() << endl;
    cout << endl;
  }
}

SCENARIO(
  "Verify PGNotation can play rafael_sarkisov_kasparov_1974_N56.pgn, "
  "('Nxb8')",
  "[PGNotation]")
{
  ifstream myfile("data/pgn/rafael_sarkisov_kasparov_1974_N56.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  ChessBoard board;
  try {
    ChessBoard board;
    board = game.playGameUntil(board, "Nxb8");
    REQUIRE(board.symbolAt("c6") == 'N');
    REQUIRE(board.symbolAt("b8") == 'q');
    cout << board.draw();
    board.moveBlackSymbol("Nxb8");
    cout << board.draw();
    REQUIRE(board.symbolAt("c6") == ' ');
    REQUIRE(board.symbolAt("b8") == 'N');
  }
  catch (exception& ex) {
    cout << game.parameters() << endl;
    cout << ex.what() << endl;
    cout << endl;
  }
}

SCENARIO("Verify PGNotation can play kasparov_malichikov_1977.pgn, ('cxd4')",
  "[PGNotation]")
{
  ifstream myfile("data/pgn/kasparov_malichikov_1977.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  ChessBoard board;
  try {
    ChessBoard board;
    board = game.playGameUntil(board, "cxd4");
    REQUIRE(board.symbolAt("c5") == 'P');
    REQUIRE(board.symbolAt("d4") == 'p');
    cout << board.draw();
    board.moveBlackSymbol("cxd4");
    cout << board.draw();
    REQUIRE(board.symbolAt("c5") == ' ');
    REQUIRE(board.symbolAt("d4") == 'P');
  }
  catch (exception& ex) {
    cout << game.parameters() << endl;
    cout << ex.what() << endl;
    cout << endl;
  }
}

SCENARIO("Verify PGNotation can play kasparov_privorotsky_1974.pgn, ('cxd4')",
  "[PGNotation]")
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
    REQUIRE(board.symbolAt("d4") == 'b');
    cout << board.draw();
    board.moveBlackSymbol("cxd4");
    cout << board.draw();
    REQUIRE(board.symbolAt("c5") == ' ');
    REQUIRE(board.symbolAt("d4") == 'P');
  }
  catch (exception& ex) {
    cout << game.parameters() << endl;
    cout << ex.what() << endl;
    cout << endl;
  }
}

SCENARIO("Verify PGNotation can kasparov_vasilchenko_1973", "[PGNotation]")
{
  ifstream myfile("data/pgn/kasparov_vasilchenko_1973.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  ChessBoard board;
  board = game.playGameEnd(board);
  cout << "done" << endl;
}

SCENARIO("Verify PGNotation can magerramov_kasparov_1973", "[PGNotation]")
{
  ifstream myfile("data/pgn/magerramov_kasparov_1973.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  try {
    ChessBoard board;
    board = game.playGameUntil(board, "cxd4");
    REQUIRE(board.symbolAt("c6") == 'N');
    REQUIRE(board.symbolAt("c5") == 'P');
    REQUIRE(board.symbolAt("d4") == 'p');
    cout << board.draw();
    board.moveBlackSymbol("cxd4");
    cout << board.draw();
    REQUIRE(board.symbolAt("c6") == 'N');
    REQUIRE(board.symbolAt("c5") == ' ');
    REQUIRE(board.symbolAt("d4") == 'P');
  }
  catch (exception& ex) {
    cout << game.parameters() << endl;
    cout << ex.what() << endl;
    cout << endl;
  }
}

SCENARIO("Verify PGNotation can kasparov_sokolov_1975.pgn", "[PGNotation]")
{
  ifstream myfile("data/pgn/kasparov_sokolov_1975.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  try {
    ChessBoard board;
    board = game.playGameUntil(board, "Rfe1");
    REQUIRE(board.symbolAt("f2") == 'q');
    REQUIRE(board.symbolAt("e1") == ' ');
    REQUIRE(board.symbolAt("f1") == 'r');
    cout << board.draw();
    board.moveWhiteSymbol("Rfe1");
    cout << board.draw();
    REQUIRE(board.symbolAt("f2") == 'q');
    REQUIRE(board.symbolAt("e1") == 'r');
    REQUIRE(board.symbolAt("f1") == ' ');
  }
  catch (exception& ex) {
    cout << game.parameters() << endl;
    cout << ex.what() << endl;
    cout << endl;
  }
}

SCENARIO("Verify PGNotation can einoris_kasparov_1975.pgn, ('Nbxd5')",
  "[PGNotationX]")
{
  ifstream myfile("data/pgn/einoris_kasparov_1975.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  try {
    ChessBoard board;
    board = game.playGameUntil(board, "Nbxd5");
    REQUIRE(board.symbolAt("b4") == 'N');
    REQUIRE(board.symbolAt("d5") == 'p');
    REQUIRE(board.symbolAt("f6") == 'N');
    cout << board.draw();
    board.moveBlackSymbol("Nbxd5");
    cout << board.draw();
    REQUIRE(board.symbolAt("b4") == ' ');
    REQUIRE(board.symbolAt("d5") == 'N');
    REQUIRE(board.symbolAt("f6") == 'N');
  }
  catch (exception& ex) {
    cout << game.parameters() << endl;
    cout << ex.what() << endl;
    cout << endl;
  }
}

SCENARIO("Verify PGNotation can einoris_kasparov_1975.pgn, ('Re8')",
  "[PGNotationX]")
{
  ifstream myfile("data/pgn/einoris_kasparov_1975.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  try {
    ChessBoard board;
    board = game.playGameUntil(board, "N8c7");
    REQUIRE(board.symbolAt("e8") == 'N');
    REQUIRE(board.symbolAt("c7") == ' ');
    cout << board.draw();
    board.moveBlackSymbol("N8c7");
    cout << board.draw();
    REQUIRE(board.symbolAt("e8") == ' ');
    REQUIRE(board.symbolAt("c7") == 'N');
  }
  catch (exception& ex) {
    cout << game.parameters() << endl;
    cout << ex.what() << endl;
    cout << endl;
  }
}

// SCENARIO("Verify PGNotation can tilichkin_kasparov_1975.pgn, ('Rd1')",
// "[PGNotationX]")
// {
//     ifstream myfile("data/pgn/tilichkin_kasparov_1975.pgn");
//     REQUIRE(myfile.good());
//     PGNGame game;
//     myfile >> game;
//     try
//     {
//         ChessBoard board;
//         board = game.playGameUntil(board, "Rd1");
//         REQUIRE(board.symbolAt("a1") == 'r');
//         REQUIRE(board.symbolAt("d1") == ' ');
//         cout << board.draw();
//         board.moveWhiteSymbol("Rd1");
//         cout << board.draw();
//         REQUIRE(board.symbolAt("a1") == ' ');
//         REQUIRE(board.symbolAt("d1") == 'r');
//     }
//     catch (exception &ex)
//     {
//         cout << game.parameters() << endl;
//         cout << ex.what() << endl;
//         cout << endl;
//     }
// }

// SCENARIO("Verify PGNotation can romanishin_kasparov_1975.pgn, ('Rh6#')",
// "[PGNotationX]")
// {
//     ifstream myfile("data/pgn/romanishin_kasparov_1975.pgn");
//     REQUIRE(myfile.good());
//     PGNGame game;
//     myfile >> game;
//     try
//     {
//         ChessBoard board;
//         board = game.playGameUntil(board, "Rh6#");
//         REQUIRE(board.symbolAt("d6") == 'r');
//         REQUIRE(board.symbolAt("h6") == ' ');
//         cout << board.draw();
//         board.moveWhiteSymbol("Rd1");
//         cout << board.draw();
//         REQUIRE(board.symbolAt("d6") == ' ');
//         REQUIRE(board.symbolAt("h6") == 'r');
//     }
//     catch (exception &ex)
//     {
//         cout << game.parameters() << endl;
//         cout << ex.what() << endl;
//         cout << endl;
//     }
// }

// SCENARIO("Verify PGNotation can kasparov_vdovin_1977_B43.pgn, ('Rgf5')",
// "[PGNotationX]")
// {
//     ifstream myfile("data/pgn/kasparov_vdovin_1977_B43.pgn");
//     REQUIRE(myfile.good());
//     PGNGame game;
//     myfile >> game;
//     try
//     {
//         ChessBoard board;
//         board = game.playGameUntil(board, "Rgf5");
//         REQUIRE(board.symbolAt("d6") == 'r');
//         REQUIRE(board.symbolAt("h6") == ' ');
//         cout << board.draw();
//         board.moveWhiteSymbol("Rgf5");
//         cout << board.draw();
//         REQUIRE(board.symbolAt("d6") == ' ');
//         REQUIRE(board.symbolAt("h6") == 'r');
//     }
//     catch (exception &ex)
//     {
//         cout << game.parameters() << endl;
//         cout << ex.what() << endl;
//         cout << endl;
//     }
// }

SCENARIO("Verify PGNotation can kasparov_dlugy_1988.pgn, ('Qh4!')",
  "[PGNotationX]")
{
  ifstream myfile("data/pgn/kasparov_dlugy_1988.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  try {
    ChessBoard board;
    board = game.playGameUntil(board, "Qh4!");
    REQUIRE(board.symbolAt("e7") == 'Q');
    REQUIRE(board.symbolAt("h4") == ' ');
    cout << board.draw();
    board.moveBlackSymbol("Qh4!");
    cout << board.draw();
    REQUIRE(board.symbolAt("e7") == ' ');
    REQUIRE(board.symbolAt("h4") == 'Q');
  }
  catch (exception& ex) {
    cout << game.parameters() << endl;
    cout << ex.what() << endl;
    cout << endl;
  }
}

SCENARIO("Verify PGNotation can kasparov_nikitin_1977.pgn, ('N6xd5')",
  "[PGNotationX]")
{
  ifstream myfile("data/pgn/kasparov_nikitin_1977.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  try {
    ChessBoard board;
    board = game.playGameUntil(board, "N6xd5");
    REQUIRE(board.symbolAt("b6") == 'N');
    REQUIRE(board.symbolAt("d5") == 'p');
    cout << board.draw();
    board.moveBlackSymbol("N6xd5");
    cout << board.draw();
    REQUIRE(board.symbolAt("b6") == ' ');
    REQUIRE(board.symbolAt("d5") == 'N');
  }
  catch (exception& ex) {
    cout << game.parameters() << endl;
    cout << ex.what() << endl;
    cout << endl;
  }
}

// SCENARIO("Verify PGNotation can kasparov_tal_1980.pgn, ('Ne2')",
// "[PGNotationX]")
// {
//     ifstream myfile("data/pgn/kasparov_tal_1980.pgn");
//     REQUIRE(myfile.good());
//     PGNGame game;
//     myfile >> game;
//     try
//     {
//         ChessBoard board;
//         board = game.playGameUntil(board, "Ne2");
//         REQUIRE(board.symbolAt("g1") == 'n');
//         REQUIRE(board.symbolAt("e2") == ' ');
//         cout << board.draw();
//         board.moveWhiteSymbol("Ne2");
//         cout << board.draw();
//         REQUIRE(board.symbolAt("g1") == ' ');
//         REQUIRE(board.symbolAt("e2") == 'n');
//     }
//     catch (exception &ex)
//     {
//         cout << game.parameters() << endl;
//         cout << ex.what() << endl;
//         cout << endl;
//     }
// }

SCENARIO("Verify PGNotation can kasparov_romanishin_1978.pgn, ('Re5')",
  "[PGNotationX]")
{
  ifstream myfile("data/pgn/kasparov_romanishin_1978.pgn");
  REQUIRE(myfile.good());
  PGNGame game;
  myfile >> game;
  try {
    ChessBoard board;
    board = game.playGameUntil(board, "Re5");
    REQUIRE(board.symbolAt("d5") == 'r');
    REQUIRE(board.symbolAt("e5") == ' ');
    cout << board.draw();
    board.moveWhiteSymbol("Re5");
    cout << board.draw();
    REQUIRE(board.symbolAt("d5") == ' ');
    REQUIRE(board.symbolAt("e5") == 'r');
  }
  catch (exception& ex) {
    cout << game.parameters() << endl;
    cout << ex.what() << endl;
    cout << endl;
  }
}

// SCENARIO("Verify PGNotation can play 'KASPAROV.PGN'", "[PGNotation]")
// {
//     ifstream myfile("data/pgn/KASPAROV.PGN");
//     REQUIRE(myfile.good());
//     PGNGames games;
//     myfile >> games;
//     REQUIRE(games.size() == 2401);

//     int cnt = 0;
//     for (auto game : games.games())
//     {
//         cout << game.parameters() << endl;
//         for (auto move : game.moves().moves())
//             cout << move << endl;
//         ChessBoard board;
//         try
//         {
//             switch (cnt)
//             {
//             case 18:
//             case 105:
//             case 106:
//                 break;
//             case 64:
//             case 113:
//             case 119:
//             case 209:
//             case 215:
//                 break;
//             default:
//                 board = game.playGameEnd(board);
//                 break;
//             }
//             cnt++;
//         }
//         catch (exception &ex)
//         {
//             cout << game.parameters() << endl;
//             cout << " Game No: " << cnt << " Issue: " << ex.what() << endl;
//             cout << endl;
//         }
//         cout << " Game No: " << cnt << endl;
//     }
// }
