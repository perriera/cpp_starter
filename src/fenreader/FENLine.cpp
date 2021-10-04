#include "../include/chessmind/fen/FENLine.hpp"
#include "../include/chessmind/game/ChessBoard.hpp"
#include "extras/string_support.hpp"
#include <iostream>

using namespace std;

ostream& operator<<(ostream& out, const FENLine& obj)
{
  out << obj._placement << ' ';
  out << obj._activeColor << ' ';
  out << obj._castling << ' ';
  out << obj._enPassant << ' ';
  out << obj._halfMove << ' ';
  out << obj._fullMove;
  return out;
}

ostream& operator<<(ostream& out, const FENLineWithParameters& obj)
{
  out << (FENLine&)obj;
  out << obj._parameters;
  return out;
}

istream& operator>>(istream& in, FENLine& obj)
{
  in >> skipws;
  in >> obj._placement;
  in >> obj._activeColor;
  in >> obj._castling;
  in >> obj._enPassant;
  in >> obj._halfMove;
  in >> obj._fullMove;
  obj._halfMove = '0';
  obj._fullMove = '0';
  return in;
}

istream& operator>>(istream& in, FENLineWithParameters& obj)
{
  in >> (FENLine&)obj;
  getline(in, obj._parameters);
  return in;
}

FENLine::FENLine(const std::string& text)
{
  stringstream ss;
  ss << text;
  ss >> *this;
}

std::string FENLine::layout() const {

  ChessBoard board;

  for (char row = '1'; row < '9'; row++) {
    for (char col = 'a'; col < 'i'; col++) {
      auto symbol = this->placement().symbolAt(col, row);
      string at;
      at += col;
      at += row;
      board.move(symbol, at);
    }
  }
  stringstream ss;
  ss << board.draw();
  string output = ss.str();
  cout << output;
  return output;
}
