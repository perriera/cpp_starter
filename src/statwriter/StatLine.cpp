#include "../include/chessmind/stat/StatLine.hpp"
#include "extras/string_support.hpp"
#include <iomanip>
#include <iostream>

using namespace std;

ostream &operator<<(ostream &out, const StatLine &line) {
  string comma = ",";
  out << line.fenLine << comma;
  out << dec << line.moveNo << comma;
  out << line.whoseMove << comma;
  out << line.lastMove << comma;
  out << line.lastMove.SAN() << comma;
  out << line.nextMove << comma;
  out << line.nextMove.SAN() << comma;
  out << line.pieceMoved << comma;
  out << line.pieceTaken << comma;
  return out;
}

istream &operator>>(istream &in, StatLine &line) {
  char comma = ' ';
  in >> line.fenLine >> comma;
  in >> dec >> line.moveNo >> comma;
  in >> line.whoseMove >> comma;
  in >> line.lastMove >> comma;
  string san;
  getline(in, san, ',');
  line.lastMove.setSAN(san);
  in >> line.nextMove >> comma;
  getline(in, san, ',');
  line.nextMove.setSAN(san);
  in >> noskipws;
  in >> line.pieceMoved >> comma;
  in >> line.pieceTaken >> comma;
  return in;
}
