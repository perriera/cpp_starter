#include "../include/cpp_starter/game/ChessMoves.hpp"
#include "../include/cpp_starter/game/ChessBoard.hpp"
#include "../include/cpp_starter/game/ChessExceptions.hpp"
#include "../include/cpp_starter/game/ChessPosition.hpp"
#include "extras/string_support.hpp"
#include <iostream>

using namespace std;

void ChessMoveException::assertation(const std::string& pos) {
  if (pos.size() != 4) {
    throw ChessMoveException("Bad size: " + pos);
  }
  try {
    ChessPosition(pos.substr(0, 2));
    ChessPosition(pos.substr(2, 2));
  }
  catch (ChessPositionException& ex) {
    throw ChessMoveException(ex.what());
  }
}

std::ostream& operator<<(std::ostream& out, const ChessMove& obj) {
  out << obj._a << obj._b;
  return out;
}

std::istream& operator>>(std::istream& in, ChessMove& obj) {
  in >> obj._a >> obj._b;
  return in;
}

bool operator==(const ChessMove& a, const ChessMove& b) {
  auto t1 = (a._a == b._a);
  auto t2 = (a._b == b._b);
  return t1 && t2;
}

bool operator==(const ChessMove& a, const char* b) {
  stringstream ss;
  ss << a;
  return ss.str() == b;
}

// ChessMove &ChessMove::operator=(const ChessMove &b)
// {
//     stringstream ss;
//     ss << b;
//     ss >> *this;
//     return *this;
// }

ChessMove& ChessMove::operator=(const char* b) {
  ChessMoveException::assertation(b);
  string a;
  a = b;
  stringstream ss;
  ss << a;
  ss >> *this;
  return *this;
}

ChessMove::ChessMove(const std::string& text) {
  ChessMoveException::assertation(text);
  stringstream ss;
  ss << text;
  ss >> *this;
}

ChessMove::ChessMove(const ChessPosition& col, const ChessPosition& row) {
  _a = col;
  _b = row;
}

ChessMove::ChessMove(const std::string& a, const std::string& b) {
  _a = a;
  _b = b;
}

MovesTable selectColumns(const MovesTable moves, char column) {
  MovesTable filtered;
  for (auto move : moves) {
    if (move[0] == column)
      filtered.push_back(move);
  }
  return filtered;
}

MovesTable selectRows(const MovesTable moves, char row) {
  MovesTable filtered;
  for (auto move : moves) {
    if (move[1] == row)
      filtered.push_back(move);
  }
  return filtered;
}

ChessMoves selectColumns(const ChessMoves& moves, char column) {
  ChessMoves filtered;
  for (auto move : moves) {
    if (move.a().col() == column)
      filtered.push_back(move);
  }
  return filtered;
}

ChessMoves selectRows(const ChessMoves& moves, char row) {
  ChessMoves filtered;
  for (auto move : moves) {
    if (move.a().row() == row)
      filtered.push_back(move);
  }
  return filtered;
}

MovesTable selectPiece(const MovesTable moves, char symbol,
  const ChessBoard* board) {
  MovesTable filtered;
  for (auto move : moves) {
    ChessMove _move = move;
    auto symbolAt = board->symbolAt(_move.a());
    if (toupper(symbolAt) == toupper(symbol))
      filtered.push_back(move);
  }
  return filtered;
}

ChessMove columnPriority(const MovesTable moves) {
  ChessMove selected;
  for (ChessMove candidate : moves) {
    if (candidate.a().col() > selected.a().col())
      selected = candidate;
  }
  return selected;
}

ChessMove rowPriority(const MovesTable moves) {
  ChessMove selected = moves.front();
  for (ChessMove candidate : moves) {
    if (candidate.a().row() > selected.a().row())
      selected = candidate;
    else if (candidate.a().row() == selected.a().row())
      if (candidate.a().col() > selected.a().col())
        selected = candidate;
  }
  return selected;
}

ChessMove colPriority(const MovesTable moves) {
  ChessMove selected = moves.front();
  for (ChessMove candidate : moves) {
    if (candidate.a().col() < selected.a().col())
      selected = candidate;
    else if (candidate.a().col() == selected.a().col())
      if (candidate.a().row() < selected.a().row())
        selected = candidate;
  }
  return selected;
}

int ChessMove::toOctal() const {
  auto upper = _a.toOctal() * 100;
  auto lower = _b.toOctal();
  int value = upper + lower;
  return value;
}

void ChessMove::fromOctal(int octal) {
  int upper = octal / 100;
  int lower = octal % 100;
  ChessPosition a, b;
  a.fromOctal(upper);
  b.fromOctal(lower);
  _a = a;
  _b = b;
}