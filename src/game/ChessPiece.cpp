#include "../include/cpp_starter/game/ChessPiece.hpp"
#include "../include/cpp_starter/game/ChessBoard.hpp"
#include "../include/cpp_starter/game/ChessExceptions.hpp"
#include "../include/cpp_starter/game/ChessPawn.hpp"
#include "extras/string_support.hpp"
#include <iostream>

using namespace std;

ostream& operator<<(ostream& out, const ChessPiece& obj) {
  out << obj._symbol << ' ';
  out << obj._col << ' ';
  out << obj._row << ' ';
  out << obj._position << ' ';
  for (string move : obj._moves)
    out << move << ' ';
  out << endl;
  return out;
}

istream& operator>>(istream& in, ChessPiece&) {
  // std::vector<std::string> moveHistory;
  // while (in.good())
  // {
  //     string move;
  //     getline(in, move);
  //     PGNFormatDetectedException::assertation(move);
  //     moveHistory.push_back(move);
  // }
  // obj._moveHistory = moveHistory;
  return in;
}

ChessPiece::ChessPiece(char symbol, char col, char row)
  : _symbol(symbol), _col(col), _row(row) {
  if (symbol == ' ')
    throw "Empty square given as a ChessPiece";
  OutOfBoundsException::assertation(col, row);
  string whitePieces = "prnbqk";
  _black_or_white = (whitePieces.find(symbol) != std::string::npos);
  _position += _col;
  _position += _row;
}

ChessPiece ChessPiece::invalidate(const ChessBoard* board) {
  _moves = allCalculatedMoves(board);
  return *this;
}

MovesTable ChessPiece::allLegalMoves(const MovesTable& moves,
  const ChessBoard* board) {
  MovesTable legalMoves;
  for (auto move : moves) {
    try {
      OutOfBoundsException::assertation(move);
      if (board->spaceOccupiable(this, move))
        legalMoves.push_back(move);
    }
    catch (OutOfBoundsException& ex) {
    }
  }
  return legalMoves;
}
