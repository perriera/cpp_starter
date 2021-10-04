#include "../include/chessmind/pgn/PGNMoves.hpp"
#include "extras/string_support.hpp"
#include <iostream>

using namespace std;
using namespace extras;

ostream& operator<<(ostream& out, const PGNMove& obj) {
  out << obj._white << ' ' << obj._black;
  return out;
}

string removeDots(const string& line) {
  string result;
  auto parts = split(line, ' ');
  for (auto part : parts) {
    if (part.find("...") == string::npos)
      result += part + ' ';
    else {
      auto end = split(part, '.');
      auto move = end[end.size() - 1];
      result += move + ' ';
    }
  }
  return result;
}

string filter(const string& line) {
  string dup = line;
  string filtered;
  bool paraOpen = false;
  for (char& c : dup) {
    if (c == '{' || c == '}') {
      paraOpen = (c == '{');
      continue;
    }
    if (paraOpen == false)
      filtered += c;
  }
  return removeDots(filtered);
}

ostream& operator<<(ostream& out, const PGNMoves& obj) {
  int cnt = 0;
  for (PGNMove move : obj)
    out << ++cnt << ". " << move << endl;
  return out;
}

istream& operator>>(istream& in, PGNMove& obj) {
  string white;
  string black;
  in >> skipws >> white;
  in >> skipws >> black;
  obj._white = white;
  obj._black = black;
  return in;
}

istream& operator>>(istream& in, PGNMoves& obj) {
  string line;
  getline(in, line);
  line = filter(line);
  deque<string> bunch = split(line, '.');
  bunch.pop_front();
  for (string move : bunch) {
    stringstream ss;
    ss << move << flush;
    PGNMove chessMove;
    ss >> chessMove;
    obj.push_back(chessMove);
  }
  return in;
}

void PGNMovesMismatchException::assertion(const PGNMoves& a,
  const PGNMoves& b, const extras::WhereAmI& ref) {
  if (a != b)
    throw PGNMovesMismatchException(ref);
}
