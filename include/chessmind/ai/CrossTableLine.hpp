#ifndef _CROSSTABLELINE_HPP
#define _CROSSTABLELINE_HPP

#include "../include/chessmind/stat/StatLine.hpp"
#include "extras/crc64_support.hpp"
#include <extras/interfaces.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>

//
// CrossTable
// CrossTableInterface implementation
//

typedef uint64_t CrossTableLineKey;

interface CrossTableLineInterface
{
  virtual const CrossTableLineKey &key() const pure;
  virtual void append(const ChessMove &chessMove) pure;
  virtual ChessMoves moves() const pure;
  virtual int moves_size() const pure;
};

class CrossTableLine implements CrossTableLineInterface
{
  friend std::ostream &operator<<(std::ostream &out, const CrossTableLine &obj);
  friend std::istream &operator>>(std::istream &in, CrossTableLine &obj);
  friend inline bool operator==(const CrossTableLine &a,
    const CrossTableLine &b)
  {
    return a._key == b._key;
  }
  friend inline bool operator!=(const CrossTableLine &a,
    const CrossTableLine &b)
  {
    return !(a == b);
  }

  CrossTableLineKey _key;
  StatLine _statLine;
  ChessMoves _chessMoves;

public:
  CrossTableLine(){};
  CrossTableLine(const StatLine &statLine) : _statLine(statLine)
  {
    _key = FENLine::makeKey(_statLine.fenLine);
  };

  virtual const CrossTableLineKey &key() const { return _key; };

  operator uint64_t() const { return _key; }

  operator const StatLine &() const { return _statLine; }

  operator ChessMoves() const { return _chessMoves; }

  virtual void append(const ChessMove &chessMove)
  {
    for (auto move : _chessMoves)
      if (move == chessMove)
        return;
    _chessMoves.push_back(chessMove);
  }

  virtual ChessMoves moves() const
  {
    ChessMoves allMoves;
    allMoves.push_back(_statLine.nextMove);
    allMoves.insert(allMoves.end(), _chessMoves.begin(), _chessMoves.end());
    return allMoves;
  }

  virtual int moves_size() const { return _chessMoves.size() + 1; };
};

typedef std::map<CrossTableLineKey, CrossTableLine> CrossTableLineMap;

#endif// _CROSSTABLELINE_HPP
