#include "../include/chessmind/game/ChessBoard.hpp"
#include "../include/chessmind/game/ChessBishop.hpp"
#include "../include/chessmind/game/ChessExceptions.hpp"
#include "../include/chessmind/game/ChessKing.hpp"
#include "../include/chessmind/game/ChessKnight.hpp"
#include "../include/chessmind/game/ChessPawn.hpp"
#include "../include/chessmind/game/ChessQueen.hpp"
#include "../include/chessmind/game/ChessRook.hpp"
#include "extras/ansi_colors.hpp"
#include "extras/string_support.hpp"
#include <ctype.h>
#include <iostream>
#include <sstream>
#include <stack>

using namespace std;
using namespace extras;

ostream& operator<<(ostream& out, const ChessBoard& obj) {
  ChessBoard dup = obj;
  out << dup.draw();
  return out;
}

istream& operator>>(istream& in, ChessBoard& obj) {
  std::vector<std::string> moveHistory;
  while (in.good()) {
    string move;
    getline(in, move);
    PGNFormatDetectedException::assertation(move);
    moveHistory.push_back(move);
  }
  obj._moveHistory = moveHistory;
  return in;
}

ChessBoard::ChessBoard() { invalidate(""); }

void ChessBoard::invalidate(const std::string&) {

  for (char row = '8'; row > '0'; row--) {
    for (char col = 'a'; col < 'i'; col++) {
      char symbol = symbolAt(col, row);
      if (symbol == ' ')
        continue;
      string position;
      position += col;
      position += row;
      chessTable[position] = selectChessPiece(symbol, col, row);
      auto piece = chessTable[position];
    }
  }
}

#define c3 blue
#define c2 green
#define c1 cyan

string ChessBoard::draw() {
  stringstream ss;
  string divider = "  -";
  for (char col = 'a'; col < 'i'; col++) {
    divider += "----";
  }
  ss << c3 << "    ";
  for (char col = 'a'; col < 'i'; col++) {
    ss << col << "   ";
  }
  ss << endl;
  ss << c2 << divider << endl;
  for (char row = '8'; row > '0'; row--) {
    ss << c3 << (row - '0') << c2 << " | ";
    for (char col = 'a'; col < 'i'; col++) {
      ss << c1 << symbolAt(col, row) << c2 << " | ";
    }
    ss << endl;
    ss << divider << endl;
  }
  return ss.str();
}

string ChessBoard::draw_inverted() {
  string normal = draw();
  deque<string> rows = split(normal, '\n');
  stack<string> stack;
  for (string row : rows)
    stack.push(row);
  stringstream inverted;
  while (!stack.empty()) {
    inverted << stack.top() << endl;
    stack.pop();
  }
  return inverted.str();
}

char ChessBoard::symbolAt(char col, char row) const {
  int y = ('8' - row);
  int x = (col - 'a');
  OutOfBoundsException::assertation(x, y);
  char piece = _pieces[y][x];
  return piece;
}

char ChessBoard::symbolAt(const ChessPosition& pos) const {
  return symbolAt(pos.col(), pos.row());
}

char ChessBoard::symbolAt(const std::string& col_row) const {
  char col = col_row[0];
  char row = col_row[1];
  return symbolAt(col, row);
}

char ChessBoard::move(char piece, string col_row) {
  char col = col_row[0];
  char row = col_row[1];
  int y = ('8' - row);
  int x = (col - 'a');
  OutOfBoundsException::assertation(x, y);
  char taken = _pieces[y][x];
  _pieces[y][x] = piece;
  return taken;
}

char ChessBoard::move(string from, string to) {
  char piece = symbolAt(from);
  char taken = move(piece, to);
  move(' ', from);
  return taken;
}

void ChessBoard::eraseEnPassantShadow(const std::string& from,
  const std::string& to) {
  char piece = symbolAt(to);
  if (!(piece == 'p' || piece == 'P'))
    return;
  char col1 = from[0];
  char row1 = from[1];
  char col2 = to[0];
  // char row2 = to[1];
  if (col1 == col2)
    return;
  string erase;
  erase += col2;
  erase += row1;
  move(' ', erase);
}

char ChessBoard::move(string from_to) {
  string from;
  from += from_to[0];
  from += from_to[1];
  string to;
  to += from_to[2];
  to += from_to[3];
  auto previous = move(from, to);
  if (previous == ' ')
    eraseEnPassantShadow(from, to);
  _moveHistory.push_back(from_to);
  return previous;
}

ChessPiece ChessBoard::pieceAt(char col, char row) const {
  char symbol = this->symbolAt(col, row);
  return selectChessPiece(symbol, col, row);
}

bool ChessBoard::spaceOccupied(const ChessPiece*,
  const std::string& move) const {
  auto squareContents = symbolAt(move);
  return squareContents != ' ';
}

bool ChessBoard::spaceOccupiable(const ChessPiece* piece,
  const std::string& move) const {
  if (!spaceOccupied(piece, move))
    return true;
  auto a = symbolAt(move);
  auto b = piece->symbol();
  if (islower(a) && islower(b))
    return false;
  if (isupper(a) && isupper(b))
    return false;
  return true;
}

bool ChessBoard::spaceTakeable(const ChessPiece* piece,
  const std::string& move) const {
  if (!spaceOccupied(piece, move))
    return false;
  auto a = symbolAt(move);
  auto b = piece->symbol();
  if (islower(a) && islower(b))
    return false;
  if (isupper(a) && isupper(b))
    return false;
  return true;
}

bool ChessBoard::squarePawnAttackable(const ChessPiece* piece,
  const std::string& move) const {
  if (!spaceOccupied(piece, move))
    return false;
  auto a = symbolAt(move);
  auto b = piece->symbol();
  if (islower(a) && islower(b))
    return false;
  if (isupper(a) && isupper(b))
    return false;
  return true;
}

ChessPiece ChessBoard::selectChessPiece(char symbol, char col, char row) const {
  switch (symbol) {
  case 'p':
    return WhitePawn(col, row).invalidate(this);
  case 'P':
    return BlackPawn(col, row).invalidate(this);
  case 'r':
    return WhiteRook(col, row).invalidate(this);
  case 'R':
    return BlackRook(col, row).invalidate(this);
  case 'n':
    return WhiteKnight(col, row).invalidate(this);
  case 'N':
    return BlackKnight(col, row).invalidate(this);
  case 'b':
    return WhiteBishop(col, row).invalidate(this);
  case 'B':
    return BlackBishop(col, row).invalidate(this);
  case 'q':
    return WhiteQueen(col, row).invalidate(this);
  case 'Q':
    return BlackQueen(col, row).invalidate(this);
  case 'k':
    return WhiteKing(col, row).invalidate(this);
  case 'K':
    return BlackKing(col, row).invalidate(this);
  default:
    throw "undefined piece: " + symbol;
  }
}

char ChessBoard::moveSymbol(const std::string& san,
  const std::string& black_or_white_set) {
  MovesTable intersections;
  PGNotation notation(san);

  for (char row = '8'; row > '0'; row--) {
    for (char col = 'a'; col < 'i'; col++) {
      char piece = symbolAt(col, row);
      if (piece == ' ')
        continue;
      if (black_or_white_set.find(piece) == std::string::npos)
        continue;
      ChessPiece chessPiece = pieceAt(col, row);
      MovesTable moves = chessPiece.moves();
      if (moves.size() == 0)
        continue;
      for (string square : moves) {
        if (square == notation.san()) {
          string from;
          from += col;
          from += row;
          intersections.push_back(from + notation.san());
        }
      }
    }
  }
  if (notation.gameover())
    return ' ';
  if (notation.castle() || notation.promotion())
    return move(notation.resolve(intersections, black_or_white_set, this));
  if (intersections.size() == 0)
    throw NoAvailableMovesException(san, black_or_white_set);
  return move(notation.resolve(intersections, black_or_white_set, this));
}
