#ifndef _CHESSPIECE_HPP
#define _CHESSPIECE_HPP

#include "../include/chessmind/game/ChessMoves.hpp"
#include <extras/interfaces.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class ChessBoard;

//
// ChessPiece
// Encapsulates all behaviour unique to a chess piece
//

abstract class ChessPiece {

  friend std::ostream &operator<<(std::ostream &out, const ChessPiece &obj);
  friend std::istream &operator>>(std::istream &in, ChessPiece &obj);

private:
  char _symbol = -1;
  char _col = -1;
  char _row = -1;
  std::string _position;
  bool _black_or_white = false;
  MovesTable _moves;

protected:
  virtual MovesTable allLegalMoves(const MovesTable &moves,
                                   const ChessBoard *board);
  virtual MovesTable allCalculatedMoves(const ChessBoard *) {
    throw "This method should not be called (directly)";
  }

  ChessPiece(char symbol, char col, char row);

public:
  ChessPiece(){};
  ChessPiece invalidate(const ChessBoard *board);
  virtual int direction() { return _black_or_white ? 1 : -1; }
  char col() const { return _col; }
  char row() const { return _row; }
  char symbol() const { return _symbol; }
  inline const MovesTable &moves() { return _moves; };
};

#endif // _CHESSPIECE_HPP
