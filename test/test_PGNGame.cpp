#include <string>   // std::string
#include <iostream> // std::cout
#include <sstream>  // std::stringstream
#include <fstream>

#include "catch.hpp"
#include "extras/string_support.hpp"
#include "../include/cpp_starter/pgn/PGNGame.hpp"
#include "../include/cpp_starter/game/ChessBoard.hpp"

using namespace std;

SCENARIO("Verify ChessGame can be read PGN file", "[PGNGane]")
{
    ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
    REQUIRE(myfile.good());
    PGNGame game;
    myfile >> game;
    REQUIRE(game.parameters().size() == 12);
    REQUIRE(game.pgnmoves().size() == 32);
}

SCENARIO("Verify ChessGame can be read PGN file (play)", "[PGNGane]")
{
    ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
    REQUIRE(myfile.good());
    PGNGame game;
    myfile >> game;
    ChessBoard board;
    for (auto move : game.pgnmoves()) {
        // board.move(move);
        cout << move << endl;
    }
    REQUIRE(game.parameters().size() == 12);
    REQUIRE(game.pgnmoves().size() == 32);
}

// SCENARIO("Verify ChessGame can be read another PGN file", "[ChessGame]")
// {
//     ifstream myfile("data/pgn/rafael_sarkisov_kasparov_1974.pgn");
//     REQUIRE(myfile.good());
//     PGNGame game;
//     myfile >> game;
//     REQUIRE(game.parameters().size() == 12);
//     REQUIRE(game.moves().size() == 35);
// }

// SCENARIO("Verify ChessGame can be output", "[ChessGame]")
// {
//     ifstream myfile("data/pgn/kasparov_muratkuliev_1973.pgn");
//     REQUIRE(myfile.good());
//     PGNGame game;
//     myfile >> game;
//     stringstream ss;
//     ss << game;
//     REQUIRE(ss.str().size() > 0);
//     REQUIRE(game.moves().size() == 32);
// }

// SCENARIO("Verify ChessGames can read a PGN archive", "[ChessGame]")
// {
//     ifstream myfile("data/pgn/KASPAROV.PGN");
//     REQUIRE(myfile.good());
//     PGNGames game;
//     myfile >> game;
//     REQUIRE(game.size() == 2401);
// }

// // SCENARIO("Verify ChessGames can play all the games in the KASPAROV PGN
// archive", "[ChessGame]")
// // {
// //     ifstream myfile("data/pgn/KASPAROV.PGN");
// //     REQUIRE(myfile.good());
// //     PGNGames games;
// //     myfile >> games;
// //     REQUIRE(games.size() == 2401);

// //     int cnt = 0;
// //     for (auto game : games.games())
// //     {
// //         cout << game.parameters() << endl;
// //         ChessBoard board;
// //         try
// //         {
// //             board = game.playGameUntil(board,"Rfxd2");
// //             board.moveWhiteSymbol("Rfxd2");
// //             cout << board.draw();
// //             cnt++;
// //         }
// //         catch (exception &ex)
// //         {
// //             cout << game.parameters() << endl;
// //             cout << ex.what() << " Game No: " << cnt << endl;
// //             cout << endl;
// //         }
// //         cout << " Game No: " << cnt << endl;
// //     }
// // }

// SCENARIO("Verify ChessGames can read another PGN archive", "[ChessGame]")
// {
//     ifstream myfile("data/pgn/CARLSEN.PGN");
//     REQUIRE(myfile.good());
//     PGNGames game;
//     myfile >> game;
//     REQUIRE(game.size() == 3594);
// }
