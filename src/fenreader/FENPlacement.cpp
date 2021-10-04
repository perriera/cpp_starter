#include "../include/cpp_starter/fen/FENPlacement.hpp"
#include "../include/cpp_starter/game/ChessBoard.hpp"
#include "../include/cpp_starter/game/ChessExceptions.hpp"
#include "extras/string_support.hpp"
#include <ctype.h>
#include <iostream>

using namespace std;

std::string FENPlacement::expanded(const FENPlacement& ref) {
  stringstream ss1;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      ss1 << ref._placements[i][j];
    }
    if (i < 7)
      ss1 << '/';
  }
  string x = ss1.str();
  return x;
}

ostream& operator<<(ostream& out, const FENPlacement& obj) {
  stringstream ss2;
  int cnt = 0;
  for (char c : FENPlacement::expanded(obj)) {
    if (c != ' ') {
      if (cnt > 0) {
        ss2 << dec << cnt;
        cnt = 0;
      }
      ss2 << c;
    }
    else
      cnt++;
  }
  if (cnt > 0)
    ss2 << dec << cnt;
  string y = ss2.str();
  out << y;
  return out;
}

istream& operator>>(istream& in, FENPlacement& obj) {
  string word;
  in >> word;
  if (word.size() == 0 && !in.good())
    return in;
  stringstream ss;
  ss << word;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      char code;
      ss >> code;
      if (isalpha(code))
        obj._placements[i][j] = code;
      else if (isdigit(code)) {
        int number_of_spaces_required = code - '0';
        for (int k = 0; k < number_of_spaces_required; k++)
          obj._placements[i][j++] = ' ';
        if (j < 8)
          j--;
      }
      else {
        throw "Invalid character: " + code;
      }
    }
    if (i < 7) {
      char slash;
      ss >> slash;
      if (slash != '/')
        throw "Invalid format";
    }
  }
  return in;
}

char FENPlacement::symbolAt(char col, char row) const {
  int y = ('8' - row);
  int x = (col - 'a');
  OutOfBoundsException::assertation(x, y);
  char _symbolAt = _placements[y][x];
  return _symbolAt;
}

char FENPlacement::symbolAt(const ChessPosition& pos) const {
  return symbolAt(pos.col(), pos.row());
}

FENPlacement::operator std::string() const {
  stringstream ss;
  ss << *this;
  return ss.str();
}

ChessMoves FENPlacement::compare(const FENPlacementInterface& white,
  const FENPlacementInterface& black, const SANInterface&) const {

  ChessPositionList list;
  for (char row = '1'; row < '9'; row++)
    for (char col = 'a'; col < 'i'; col++) {
      ChessPosition a(col, row);
      auto whiteSymbol = white.symbolAt(a);
      auto blackSymbol = black.symbolAt(a);
      if (whiteSymbol != blackSymbol)
        list.push_back(a);
    }

  ChessMoves results;
  for (size_t i = 0; i < list.size(); i += 2) {
    ChessMove b(list[i], list[i + 1]);
    // cout << b << endl;
    results.push_back(b);
  }

  return results;
}
