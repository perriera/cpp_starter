#include "../include/cpp_starter/game/ChessRook.hpp"
#include "../include/cpp_starter/game/ChessBoard.hpp"
#include "../include/cpp_starter/game/ChessExceptions.hpp"
#include "extras/string_support.hpp"
#include <iostream>

using namespace std;

MovesTable ChessRook::addDirection(char col, char row, int up, int right,
  const ChessBoard* board,
  const ChessPiece* piece) {
  MovesTable moves;
  string from;
  from += col;
  from += row;
  try {
    while (true) {
      col = col + up;
      row = row + right;
      string to;
      to += col;
      to += row;
      if (!board->spaceOccupiable(piece, to))
        throw OutOfBoundsException(to);
      if (board->spaceTakeable(piece, to)) {
        moves.push_back(to);
        break;
      }
      moves.push_back(to);
    }
  }
  catch (OutOfBoundsException& ex) {
  }
  return moves;
}

MovesTable ChessRook::allCalculatedMoves(const ChessBoard* board) {
  MovesTable possibleMoves;
  MovesTable v1 = addDirection(col(), row(), 1, 0, board, this);
  MovesTable v2 = addDirection(col(), row(), -1, 0, board, this);
  MovesTable v3 = addDirection(col(), row(), 0, 1, board, this);
  MovesTable v4 = addDirection(col(), row(), 0, -1, board, this);
  possibleMoves.insert(possibleMoves.end(), v1.begin(), v1.end());
  possibleMoves.insert(possibleMoves.end(), v2.begin(), v2.end());
  possibleMoves.insert(possibleMoves.end(), v3.begin(), v3.end());
  possibleMoves.insert(possibleMoves.end(), v4.begin(), v4.end());
  auto test = allLegalMoves(possibleMoves, board);
  return test;
}