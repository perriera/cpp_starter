#include "../include/chessmind/ai/CrossTableLine.hpp"
#include "extras/ansi_colors.hpp"
#include "extras/crc16_support.hpp"
#include "extras/crc64_support.hpp"
#include "extras/string_support.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;
using namespace extras;

ostream &operator<<(ostream &out, const CrossTableLine &obj) {
  char comma = ',';
  out << setfill('0') << setw(16) << std::hex;
  out << obj._key << comma;
  out << obj._statLine;
  auto extra_moves = obj._chessMoves;
  if (extra_moves.size() == 0)
    out << ' ';
  else
    for (auto move : extra_moves)
      out << move << ' ' << move.SAN() << ' ';
  return out;
}

istream &operator>>(istream &in, CrossTableLine &obj) {
  char comma = ' ';
  in >> hex >> obj._key >> comma;
  in >> obj._statLine;
  string remainder;
  getline(in, remainder);
  trim(remainder);
  if (remainder.size() == 0)
    return in;
  stringstream ss;
  ss << remainder;
  while (ss.good()) {
    ChessMove chessMove;
    ss >> chessMove;
    string san;
    ss >> skipws >> san;
    chessMove.setSAN(san);
    obj._chessMoves.push_back(chessMove);
  }
  return in;
}
