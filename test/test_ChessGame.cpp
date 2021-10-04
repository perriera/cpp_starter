#include <fstream>
#include <iostream> 
#include <sstream> 
#include <string>
#include "catch.hpp"
#include "extras/string_support.hpp"
#include "../include/chessmind/pgn/PGNGame.hpp"
#include "../include/chessmind/game/ChessBoard.hpp"

using namespace std;

SCENARIO("Verify ChessGameInterface can be read PGN file", "[ChessGame]")
{
    ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
    REQUIRE(myfile.good());
    PGNGame game;
    myfile >> game;
    REQUIRE(game.parameters().size() == 12);
    REQUIRE(game.pgnmoves().size() == 32);
}

SCENARIO("Verify ChessGameInterface can show a chess board", "[ChessGame]")
{
    ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
    REQUIRE(myfile.good());
    PGNGame game;
    myfile >> game;
    REQUIRE(game.parameters().size() == 12);
    REQUIRE(game.pgnmoves().size() == 32);
    stringstream ss;
    ss << game.board();
    REQUIRE(ss.str().size() > 0);
}

SCENARIO("Verify ChessGameInterface can show next move", "[ChessGame]")
{
    ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
    REQUIRE(myfile.good());
    PGNGame game;
    myfile >> game;
    REQUIRE(game.parameters().size() == 12);
    REQUIRE(game.pgnmoves().size() == 32);
    int cnt = 0;
    while (true) {
        try {
            game.next();
            cout << game.board();
            cnt++;
        }
        catch (EndOfGameReachedException& ex) {
            break;
        }
    }
    REQUIRE(cnt == game.pgnmoves().size() * 2);
    while (true) {
        try {
            game.previous();
            cout << game.board();
            cnt--;
        }
        catch (StartOfGameReachedException& ex) {
            break;
        }
    }
    REQUIRE(cnt == 0);
}

SCENARIO("Verify ChessGameInterface can move chess pieces", "[CHES-9]")
{
    ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
    REQUIRE(myfile.good());

    GIVEN("we need to know what chess moves were made in a chess game")
        WHEN("we use the moves() method on the ChessGameInterface") {
        THEN("we are given the moves of a given chess game") {
            PGNGame game;
            myfile >> game;
            REQUIRE(game.parameters().size() == 12);
            REQUIRE(game.pgnmoves().size() == 32);
            ChessGameInterface& i = game;
            REQUIRE(i.moves().size() == 64);
        }
    }
}

