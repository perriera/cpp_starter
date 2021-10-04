#ifndef _FENLINE_HPP
#define _FENLINE_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/chessmind/fen/FENPlacement.hpp"
#include "extras/crcs.hpp"
#include "extras/interfaces.hpp"

/**
 * @brief interface FENLineInterface
 *
 */

interface FENLineInterface {
  virtual const FENPlacement& placement() const pure;
  virtual char activeColor() const pure;
  virtual char isWhite() const pure;
  virtual char isBlack() const pure;
  virtual const std::string& castling() const pure;
  virtual const std::string& enPassant() const pure;
  virtual char halfMove() const pure;
  virtual char fullMove() const pure;
  virtual std::string layout() const pure;
};

typedef uint64_t FENLineKey;

/**
 * @brief class FENLine
 *
 */

concrete class FENLine implements FENLineInterface {
  friend std::ostream& operator<<(std::ostream& out, const FENLine& obj);
  friend std::istream& operator>>(std::istream& in, FENLine& obj);
  friend inline bool operator==(const FENLine& a, const FENLine& b) {
    std::stringstream ss1;
    ss1 << a;
    std::stringstream ss2;
    ss2 << b;
    return ss1.str() == ss2.str();
  }
  friend inline bool operator!=(const FENLine& a, const FENLine& b) {
    return !(a == b);
  }

private:
  FENPlacement _placement;
  char _activeColor;
  std::string _castling;
  std::string _enPassant;
  char _halfMove;
  char _fullMove;

public:
  static FENLineKey makeKey(const FENLine& fenLine) {
    extras::crc64 _crc;
    return _crc.update(fenLine);
  }

  FENLine() = default;
  FENLine(const std::string& text);

  virtual const FENPlacement& placement() const { return _placement; };
  virtual char activeColor() const { return _activeColor; };
  virtual char isWhite() const { return _activeColor == 'w'; };
  virtual char isBlack() const { return !isWhite(); };
  virtual const std::string& castling() const { return _castling; };
  virtual const std::string& enPassant() const { return _enPassant; };
  virtual char halfMove() const { return _halfMove; };
  virtual char fullMove() const { return _fullMove; };
  virtual std::string layout() const;

  operator const FENPlacement& () const { return _placement; }

  operator std::string() const {
    std::stringstream ss1;
    ss1 << *this;
    return ss1.str();
  }
};

/**
 * @brief FENLineList
 */
using FENLineList = std::vector<FENLine>;

/**
 * @brief FENLineWithParameters
 */

class FENLineWithParameters extends FENLine {
  friend std::ostream& operator<<(std::ostream& out,
    const FENLineWithParameters& obj);
  friend std::istream& operator>>(std::istream& in,
    FENLineWithParameters& obj);
  friend inline bool operator==(const FENLineWithParameters& a,
    const FENLineWithParameters& b) {
    std::stringstream ss1;
    ss1 << a;
    std::stringstream ss2;
    ss2 << b;
    return ss1.str() == ss2.str();
  }
  friend inline bool operator!=(const FENLineWithParameters& a,
    const FENLineWithParameters& b) {
    return !(a == b);
  }
private:
  std::string _parameters;
public:
  const std::string& parameters() {
    return _parameters;
  }

};

typedef std::vector<FENLineWithParameters> FENLineListWithParameters;

#endif  // _FENLINE_HPP
