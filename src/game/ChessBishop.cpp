#include "../include/cpp_starter/game/ChessBishop.hpp"
#include "../include/cpp_starter/game/ChessBoard.hpp"
#include "../include/cpp_starter/game/ChessExceptions.hpp"
#include "extras/string_support.hpp"
#include <iostream>

using namespace std;

MovesTable ChessBishop::addDirection(char col, char row, bool up, bool right,
  const ChessBoard* board,
  const ChessPiece* piece) {
  MovesTable moves;
  string from;
  from += col;
  from += row;
  try {
    while (true) {
      col = col + ((1 * up) != 0 ? 1 : -1);
      row = row + ((1 * right) != 0 ? 1 : -1);
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

MovesTable ChessBishop::allCalculatedMoves(const ChessBoard* board) {
  MovesTable possibleMoves;
  MovesTable v1 = addDirection(col(), row(), true, true, board, this);
  MovesTable v2 = addDirection(col(), row(), true, false, board, this);
  MovesTable v3 = addDirection(col(), row(), false, true, board, this);
  MovesTable v4 = addDirection(col(), row(), false, false, board, this);
  possibleMoves.insert(possibleMoves.end(), v1.begin(), v1.end());
  possibleMoves.insert(possibleMoves.end(), v2.begin(), v2.end());
  possibleMoves.insert(possibleMoves.end(), v3.begin(), v3.end());
  possibleMoves.insert(possibleMoves.end(), v4.begin(), v4.end());
  return allLegalMoves(possibleMoves, board);
  ;
}