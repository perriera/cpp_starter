#ifndef _CHESSSAN_HPP
#define _CHESSSAN_HPP

#include <extras/interfaces.hpp>
#include <iostream>
#include <string>

//
// ChessRook
// Encapsulates all behaviour unique to a chess rook piece
//

interface ChessSANInterface {
  virtual std::string SAN() const pure;
  virtual void setSAN(const std::string &san) pure;
};

#endif // _CHESSSAN_HPP
