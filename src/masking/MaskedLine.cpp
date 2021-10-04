#include "../include/chessmind/masking/MaskedLine.hpp"
#include "extras/crc16_support.hpp"
#include "extras/string_support.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;
using namespace extras;

string maskInt(int moveNo, int width) {
  stringstream ss;
  ss << setw(width) << moveNo << flush;
  string formatted = ss.str();
  return formatted;
}

string maskMove(string lastMove) {
  char masked_col = '1';
  for (char col = 'a'; col < 'i'; col++, masked_col++) {
    lastMove = replace_all(lastMove, col, masked_col);
  }
  return lastMove;
}

char maskWhoseMove(char whoseMove) {
  whoseMove = whoseMove == 'w' ? '1' : '2';
  return whoseMove;
}

string maskPiece(char piece) {
  string translation_table = " pPbBnNrRqQkK";
  size_t pos = translation_table.find(piece);
  if (pos == string::npos)
    throw "Bad Character";
  stringstream ss;
  ss << pos;
  string converted = ss.str();
  converted = maskInt(stoi(converted), 2);
  return converted;
}

string maskSan(string san) {
  crc16 crc;
  stringstream ss;
  ss << dec << crc.update(san);
  string converted = ss.str();
  converted = maskInt(stoi(converted), 7);
  return converted;
}

ostream &operator<<(ostream &out, const MaskedLine &obj) {
  out << maskInt(obj.statLine.moveNo, 3) << ", ";
  out << maskWhoseMove(obj.statLine.whoseMove) << ", ";
  out << maskMove(obj.statLine.lastMove) << ", ";
  out << maskPiece(obj.statLine.pieceMoved) << ", ";
  out << maskPiece(obj.statLine.pieceTaken) << ", ";
  out << maskSan(obj.statLine.lastMove.SAN()) << ", ";
  for (char squareContent : obj.statLine.squares)
    out << maskPiece(squareContent) << ", ";
  out << endl;
  return out;
}

istream &operator>>(istream &in, MaskedLine &) { return in; }
