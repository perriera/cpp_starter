#ifndef _CHESSPOSITION_HPP
#define _CHESSPOSITION_HPP

#include "../include/cpp_starter/game/Assigned.hpp"
#include "../include/cpp_starter/game/ChessSquare.hpp"
#include <extras/octal_support.hpp>
#include <extras/interfaces.hpp>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

//
// ChessPositionInterface
// Encapsulates all behaviour unique to a chess piece
//

interface ChessPositionInterface extends AssignedInterface
{
  virtual const ChessCol& col() const pure;
  virtual const ChessRow& row() const pure;
};

//
// ChessPositionInterface
// Encapsulates all behaviour unique to a chess piece
//

class ChessBoard;

concrete class ChessPosition implements ChessPositionInterface,
extras::OctalInterface
{
  friend std::ostream& operator<<(std::ostream& out, const ChessPosition& obj);
  friend std::istream& operator>>(std::istream& in, ChessPosition& obj);
  friend inline bool operator==(const ChessPosition& a,
    const ChessPosition& b)
  {
    return a._col == b._col && a._row == b._row;
  }
  friend inline bool operator==(const ChessPosition& a, const std::string& b)
  {
    std::string ss = a;
    return ss == b;
  }
  friend inline bool operator!=(const ChessPosition& a,
    const ChessPosition& b)
  {
    return !(a == b);
  }
  friend inline bool operator!=(const ChessPosition& a, const std::string& b)
  {
    return !(a == b);
  }

private:
  ChessCol _col;
  ChessRow _row;
  bool _assigned = false;

public:
  ChessPosition() : _assigned(false) {};
  ChessPosition(const std::string& text);
  ChessPosition(char col, char row);
  inline operator const std::string() const
  {
    std::stringstream ss;
    ss << *this;
    return ss.str();
  }
  // ChessPosition operator=(const ChessPosition &b);
  ChessPosition& operator=(const std::string& b);
  inline const ChessCol& col() const { return _col; }
  inline const ChessRow& row() const { return _row; }
  inline bool assigned() const { return _assigned; }
  virtual int toOctal() const;
  virtual void fromOctal(int octal);
};

using ChessPositionList = std::vector<ChessPosition>;

//
// ChessPositionException
// Governs all rules on ChessPosition
//

struct ChessPositionException : public std::exception
{
  std::string _msg;

public:
  ChessPositionException(const std::string& msg) : _msg(msg) {};
  const char* what() const throw() { return _msg.c_str(); };
  static void assertation(const std::string& pos);
  inline operator const std::string& () const { return _msg; }
};

#endif// _CHESSPOSITION_HPP
