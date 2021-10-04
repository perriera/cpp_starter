#include <fstream>
#include <iostream> 
#include <sstream> 
#include <string>
#include "catch.hpp"
#include "extras/string_support.hpp"
#include "../include/cpp_starter/pgn/PGNGame.hpp"
#include "../include/cpp_starter/game/ChessBoard.hpp"

using namespace std;

SCENARIO("Verify PGNtoFENInterface can be read PGN file", "[PGNtoFEN]")
{
    ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
    REQUIRE(myfile.good());
    PGNGame game;
    myfile >> game;
    REQUIRE(game.parameters().size() == 12);
    REQUIRE(game.pgnmoves().size() == 32);
}

SCENARIO("Verify PGNtoFENInterface can convertToFEN", "[PGNtoFEN]")
{
    ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
    REQUIRE(myfile.good());
    PGNGame game;
    myfile >> game;
    //    game.convertToFEN();


}

