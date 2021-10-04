#ifndef _PGNOTATION_HPP
#define _PGNOTATION_HPP

#include "../include/cpp_starter/game/ChessPiece.hpp"
#include <extras/interfaces.hpp>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

class ChessBoard;

//
// PGNotation
// Encapsulates all behaviour unique to a PGN notation
//
interface PGNotationWinnerInterface {
  virtual bool gameover() const = 0;
  virtual ~PGNotationWinnerInterface() {};
};

interface PGNotationCastleInterface {
  virtual bool castle() const = 0;
  virtual bool queenCastle() const = 0;
  virtual bool kingCastle() const = 0;
};

interface PGNotationPromoteInterface {
  virtual bool promotion() const = 0;
};

interface PGNotationInterface extends PGNotationCastleInterface,
  PGNotationPromoteInterface, PGNotationWinnerInterface {
  virtual bool equals(const PGNotationInterface& a) = 0;
  virtual bool equals(const std::string& a) = 0;
  virtual char piece() const = 0;
  virtual const std::string& san() const = 0;
  virtual int type() const = 0;
  virtual const std::string& original() const = 0;
  virtual std::string resolve(const MovesTable& intersections,
    const std::string& black_or_white_set,
    const ChessBoard*) const = 0;
};

class PGNotation implements PGNotationInterface {
  friend std::ostream& operator<<(std::ostream& out, const PGNotation& obj);
  friend std::istream& operator>>(std::istream& in, PGNotation& obj);
  friend inline bool operator==(const PGNotation& a, const PGNotation& b) {
    return a._proxy->equals(b);
  }
  friend inline bool operator==(const PGNotation& a, const std::string& b) {
    return a._proxy->equals(b);
  }
  PGNotationInterface* _proxy = nullptr;
  std::string _original;

public:
  PGNotation() {};
  PGNotation(const std::string& san) : _original(san) {
    std::stringstream ss;
    ss << san;
    ss >> *this;
  };
  virtual ~PGNotation() {
    delete _proxy;
    _proxy = nullptr;
  }
  virtual bool equals(const PGNotationInterface& a) {
    return _proxy->equals(a);
  }
  virtual bool equals(const std::string& a) { return _proxy->equals(a); }

  virtual char piece() const { return _proxy->piece(); }
  virtual const std::string& san() const { return _proxy->san(); }
  virtual bool castle() const { return _proxy->castle(); }
  virtual bool kingCastle() const { return _proxy->kingCastle(); }
  virtual bool queenCastle() const { return _proxy->queenCastle(); }
  virtual bool gameover() const { return _proxy->gameover(); }
  virtual int type() const { return _proxy->type(); }
  virtual const std::string& original() const { return _original; }
  virtual std::string resolve(const MovesTable& intersections,
    const std::string& black_or_white_set,
    const ChessBoard* board) const {
    return _proxy->resolve(intersections, black_or_white_set, board);
  }
  virtual bool promotion() const { return _proxy->promotion(); }
};

#endif // _PGNOTATION_HPP
