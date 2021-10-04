#include "../include/cpp_starter/game/ChessQueen.hpp"
#include "../include/cpp_starter/game/ChessBishop.hpp"
#include "../include/cpp_starter/game/ChessBoard.hpp"
#include "../include/cpp_starter/game/ChessExceptions.hpp"
#include "../include/cpp_starter/game/ChessRook.hpp"
#include "extras/string_support.hpp"
#include <iostream>

using namespace std;

MovesTable ChessQueen::allCalculatedMoves(const ChessBoard* board) {
  MovesTable possibleMoves;
  {
    MovesTable v1 = ChessRook::addDirection(col(), row(), 1, 0, board, this);
    MovesTable v2 = ChessRook::addDirection(col(), row(), -1, 0, board, this);
    MovesTable v3 = ChessRook::addDirection(col(), row(), 0, 1, board, this);
    MovesTable v4 = ChessRook::addDirection(col(), row(), 0, -1, board, this);
    possibleMoves.insert(possibleMoves.end(), v1.begin(), v1.end());
    possibleMoves.insert(possibleMoves.end(), v2.begin(), v2.end());
    possibleMoves.insert(possibleMoves.end(), v3.begin(), v3.end());
    possibleMoves.insert(possibleMoves.end(), v4.begin(), v4.end());
  }
  {
    MovesTable v1 =
      ChessBishop::addDirection(col(), row(), true, true, board, this);
    MovesTable v2 =
      ChessBishop::addDirection(col(), row(), true, false, board, this);
    MovesTable v3 =
      ChessBishop::addDirection(col(), row(), false, true, board, this);
    MovesTable v4 =
      ChessBishop::addDirection(col(), row(), false, false, board, this);
    possibleMoves.insert(possibleMoves.end(), v1.begin(), v1.end());
    possibleMoves.insert(possibleMoves.end(), v2.begin(), v2.end());
    possibleMoves.insert(possibleMoves.end(), v3.begin(), v3.end());
    possibleMoves.insert(possibleMoves.end(), v4.begin(), v4.end());
  }
  auto test = allLegalMoves(possibleMoves, board);
  return test;
}