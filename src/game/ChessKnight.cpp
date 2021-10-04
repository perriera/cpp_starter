#include "../include/chessmind/game/ChessKnight.hpp"
#include "../include/chessmind/game/ChessBoard.hpp"
#include "../include/chessmind/game/ChessExceptions.hpp"
#include "../include/chessmind/game/ChessPawn.hpp"
#include "extras/string_support.hpp"
#include <iostream>

using namespace std;

MovesTable ChessKnight::allCalculatedMoves(const ChessBoard *board) {
  MovesTable possibleMoves;
  char _col = col();
  char _row = row();
  possibleMoves.push_back(ChessPawn::addPosition(_col + 1, _row + 2));
  possibleMoves.push_back(ChessPawn::addPosition(_col - 1, _row + 2));
  possibleMoves.push_back(ChessPawn::addPosition(_col + 1, _row - 2));
  possibleMoves.push_back(ChessPawn::addPosition(_col - 1, _row - 2));
  possibleMoves.push_back(ChessPawn::addPosition(_col + 2, _row + 1));
  possibleMoves.push_back(ChessPawn::addPosition(_col - 2, _row + 1));
  possibleMoves.push_back(ChessPawn::addPosition(_col + 2, _row - 1));
  possibleMoves.push_back(ChessPawn::addPosition(_col - 2, _row - 1));
  return allLegalMoves(possibleMoves, board);
}