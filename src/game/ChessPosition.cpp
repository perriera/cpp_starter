#include "../include/chessmind/game/ChessPosition.hpp"
#include "../include/chessmind/game/ChessBoard.hpp"
#include "../include/chessmind/game/ChessExceptions.hpp"
#include "../include/chessmind/game/ChessKing.hpp"
#include "../include/chessmind/game/ChessPawn.hpp"
#include "extras/string_support.hpp"
#include <iostream>

using namespace std;

void ChessPositionException::assertation(const std::string &pos) {
  if (pos.size() != 2) {
    throw ChessPositionException("Bad size: " + pos);
  }
  try {
    ChessCol a(pos[0]);
    ChessRow b(pos[1]);
  } catch (ChessCoordinateException &ex) {
    throw ChessPositionException(ex.what());
  }
}

std::ostream &operator<<(std::ostream &out, const ChessPosition &obj) {
  out << obj._col;
  out << obj._row;
  return out;
}

std::istream &operator>>(std::istream &in, ChessPosition &obj) {
  in >> obj._col;
  in >> obj._row;
  ChessPositionException::assertation(obj);
  obj._assigned = true;
  return in;
}

// ChessPosition ChessPosition::operator=(const ChessPosition &b)
// {
//     stringstream ss;
//     ss << b;
//     ss >> *this;
//     return *this;
// }

ChessPosition &ChessPosition::operator=(const std::string &b) {
  ChessPositionException::assertation(b);
  stringstream ss;
  ss << b;
  ss >> *this;
  return *this;
}

ChessPosition::ChessPosition(const std::string &text) : _assigned(true) {
  ChessPositionException::assertation(text);
  stringstream ss;
  ss << text;
  ss >> *this;
}

ChessPosition::ChessPosition(char col, char row) : _assigned(true) {
  stringstream ss;
  ss << col << row;
  ss >> *this;
  // ChessPositionException::assertation(_position);
}

int ChessPosition::toOctal() const {
  int octCol = _col - 'a';
  int octRow = _row - '1';
  int value = octCol * 10 + octRow;
  return value;
}

void ChessPosition::fromOctal(int octal) {
  int upper = octal / 10;
  int lower = octal % 10;
  _col = upper + 'a';
  _row = lower + '1';
}

// ChessPosition operator ++();
// ChessPosition operator --();

// ChessPosition ChessPosition::operator++()
// {
//     Check temp;
//     ++i;
//     temp.i = i;

//     return temp;
// }

// ChessPosition ChessPosition::operator--()
// {
//     Check temp;
//     ++i;
//     temp.i = i;

//     return temp;
// }
