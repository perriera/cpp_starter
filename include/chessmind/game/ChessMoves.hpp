#ifndef _CHESSMOVE_HPP
#define _CHESSMOVE_HPP

#include "../include/chessmind/game/Assigned.hpp"
#include "../include/chessmind/game/ChessPosition.hpp"
#include "../include/chessmind/game/ChessSAN.hpp"
#include "extras/octal_support.hpp"
#include <extras/interfaces.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>

//
// ChessMoveInterface
// Encapsulates all behaviour unique to a chess piece
//

interface ChessMoveInterface extends AssignedInterface, ChessSANInterface {
  virtual const ChessPosition& a() const pure;
  virtual const ChessPosition& b() const pure;
};

//
// ChessMove class
//

typedef std::vector<std::string> MovesTable;

class ChessBoard;

concrete class ChessMove implements ChessMoveInterface, extras::OctalInterface {
  friend std::ostream& operator<<(std::ostream& out, const ChessMove& obj);
  friend std::istream& operator>>(std::istream& in, ChessMove& obj);
  friend bool operator==(const ChessMove& a, const ChessMove& b);
  friend bool operator==(const ChessMove& a, const char*);
  friend inline bool operator!=(const ChessMove& a, const ChessMove& b) {
    return !(a == b);
  }
  friend inline bool operator!=(const ChessMove& a, const char* b) {
    return !(a == b);
  }

private:
  std::string _san;
  ChessPosition _a;
  ChessPosition _b;

public:
  ChessMove() {};
  ChessMove(const std::string& text);
  ChessMove(const char* text) : ChessMove(std::string(text)) {}
  ChessMove(const ChessPosition& col, const ChessPosition& row);
  ChessMove(const std::string& col, const std::string& row);
  inline operator const std::string() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
  }
  // ChessMove &operator=(const ChessMove &b);
  ChessMove& operator=(const char* b);
  inline const ChessPosition& a() const { return _a; }
  inline const ChessPosition& b() const { return _b; }
  virtual int toOctal() const;
  virtual void fromOctal(int octal);
  virtual bool assigned() const { return _a.assigned() && _b.assigned(); };
  virtual std::string SAN() const { return _san; };
  virtual void setSAN(const std::string& san) { _san = san; };
};

using ChessMoves = std::vector<ChessMove>;

MovesTable selectPiece(const MovesTable moves, char symbol,
  const ChessBoard* board);
ChessMove columnPriority(const MovesTable moves);
ChessMove rowPriority(const MovesTable moves);
ChessMove colPriority(const MovesTable moves);

MovesTable selectColumns(const MovesTable moves, char column);
MovesTable selectRows(const MovesTable moves, char row);
ChessMoves selectColumns(const ChessMoves& moves, char column);
ChessMoves selectRows(const ChessMoves& moves, char row);

//
// ChessMoveException
// Governs all rules on ChessMove
//

struct ChessMoveException : public std::exception {
  std::string _msg;

public:
  ChessMoveException(const std::string& msg) : _msg(msg) {};
  const char* what() const throw() { return _msg.c_str(); };
  static void assertation(const std::string& pos);
  inline operator const std::string& () const { return _msg; }
};

#endif // _CHESSMOVE_HPP
