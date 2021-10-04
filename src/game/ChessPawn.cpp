#include "../include/cpp_starter/game/ChessPawn.hpp"
#include "../include/cpp_starter/game/ChessBoard.hpp"
#include "../include/cpp_starter/game/ChessExceptions.hpp"
#include "extras/string_support.hpp"
#include <iostream>

using namespace std;

string ChessPawn::addPosition(char col, char row) {
  stringstream move;
  move << col << row;
  string move_pos = move.str();
  return move_pos;
}

bool enPassantDetected(const ChessBoard* board, char col, char row,
  bool left_of_right) {
  string lastMove = board->lastMove();
  if (lastMove != "") {
    string pos_of_piece_to_check;
    pos_of_piece_to_check += lastMove[2];
    pos_of_piece_to_check += lastMove[3];
    char symbol_at_pos = board->symbolAt(pos_of_piece_to_check);
    if (toupper(symbol_at_pos) != 'P')
      return false;
    auto _col = col;
    stringstream to;
    if (left_of_right)
      to << --_col << row;
    else
      to << ++_col << row;
    string move = to.str();
    int r1 = lastMove[1];
    int r2 = row;
    int r3 = lastMove[3];
    int c1 = lastMove[0];
    int c2 = _col;
    bool goingUp = r1 < r2&& r2 < r3;
    bool goingDown = r1 > r2 && r2 > r3;
    if (c1 == c2 && goingUp)
      return true;
    if (c1 == c2 && goingDown)
      return true;
  }
  return false;
}

MovesTable addPawnMove(const ChessPiece* piece, const MovesTable& moves,
  char col, char row, const ChessBoard* board,
  bool takeable) {
  MovesTable duplicate = moves;
  {
    stringstream to;
    to << col << row;
    string move = to.str();
    if (!board->spaceOccupied(piece, move))
      duplicate.push_back(move);
  }
  auto enPassant1 = enPassantDetected(board, col, row, true);
  if (col > 'a' && (takeable || enPassant1)) {
    auto _col = col;
    stringstream to;
    to << --_col << row;
    string move = to.str();
    if (enPassant1 || board->squarePawnAttackable(piece, move))
      duplicate.push_back(move);
  }
  auto enPassant2 = enPassantDetected(board, col, row, false);
  if (col < 'h' && (takeable || enPassant2)) {
    auto _col = col;
    stringstream to;
    to << ++_col << row;
    string move = to.str();
    if (enPassant2 || board->squarePawnAttackable(piece, move))
      duplicate.push_back(move);
  }
  return duplicate;
}

bool ChessPawn::pawnAtStart() const {
  if (row() == '2' && symbol() == 'p')
    return true;
  if (row() == '7' && symbol() == 'P')
    return true;
  return false;
}

static bool pawnAtStartClearToJump(const ChessPiece* piece, char col, char row,
  const ChessBoard* board) {
  ChessPosition pos(col, row);
  return !board->spaceOccupied(piece, pos);
}

MovesTable ChessPawn::allCalculatedMoves(const ChessBoard* board) {
  MovesTable possibleMoves;
  possibleMoves = addPawnMove(this, possibleMoves, col(),
    row() + this->direction(), board, true);
  if (pawnAtStart() &&
    pawnAtStartClearToJump(this, col(), row() + this->direction(), board))
    possibleMoves = addPawnMove(this, possibleMoves, col(),
      row() + this->direction() * 2, board, false);
  return allLegalMoves(possibleMoves, board);
}

// MovesTable ChessPawn::selectMoveThatLandsOnThatSpot(char piece, char col,
// char row, const std::string& san)
// {

// }
