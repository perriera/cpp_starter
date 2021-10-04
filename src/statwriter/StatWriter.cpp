#include "../include/chessmind/stat/StatWriter.hpp"
#include "../include/chessmind/fen/FENReader.hpp"
#include "../include/chessmind/pgn/PGNGame.hpp"
#include "../include/chessmind/stat/NextMove.hpp"
#include "../include/chessmind/stat/StatHeader.hpp"
#include "extras/string_support.hpp"
#include <iomanip>
#include <iostream>

using namespace std;

string StatWriter::csv_out() const
{
  stringstream out;
  out << StatHeader() << endl;
  for (auto line : this->_lines)
    out << line << endl;
  string csv = out.str();
  return csv;
}

void StatWriter::csv_in(const std::string&)
{
  stringstream in;
  StatLines lines;
  while (!in.eof()) {
    string text;
    getline(in, text);
    if (text.size() == 0)
      break;
    stringstream ss;
    ss << text;
    StatLine line;
    ss >> line;
    lines.push_back(line);
  }
  this->_lines = lines;
}

ostream& operator<<(ostream& out, const StatWriter& obj)
{
  StatLines dup = obj._lines;
  for (auto line : dup)
    out << line << endl;
  return out;
}

istream& operator>>(istream& in, StatWriter& obj)
{
  StatLines lines;
  while (!in.eof()) {
    string text;
    getline(in, text);
    cout << text << endl;
    if (text.size() == 0)
      break;
    stringstream ss;
    ss << text;
    StatLine line;
    ss >> line;
    lines.push_back(line);
  }
  obj._lines = lines;
  return in;
}

struct LastMoveReport
{
  ChessMove lastMove;
  char pieceMoved = ' ';
  char pieceTaken = ' ';
};

LastMoveReport determineLastMove(const FENLine& femLine,
  const FENLine& previousLine)
{
  ChessPosition p1;
  ChessPosition p2;
  LastMoveReport lastMoveReport;

  char c = '?';
  for (char row = '1'; row < '9'; row++) {
    for (char col = 'a'; col < 'i'; col++) {
      auto a = femLine.placement().symbolAt(col, row);
      auto b = previousLine.placement().symbolAt(col, row);
      if (a != b) {
        c = a;
        if (!p1.assigned())
          p1 = ChessPosition(col, row);
        else if (!p2.assigned()) {
          p2 = ChessPosition(col, row);
          break;
        }
      }
    }
  }
  if (c != '?') {
    if (c != ' ')
      lastMoveReport.lastMove = ChessMove(p1, p2);
    else
      lastMoveReport.lastMove = ChessMove(p2, p1);
    auto a = femLine.placement().symbolAt(lastMoveReport.lastMove.b());
    auto b = previousLine.placement().symbolAt(lastMoveReport.lastMove.b());
    lastMoveReport.pieceMoved = a;
    lastMoveReport.pieceTaken = b;
  }

  return lastMoveReport;
}

string determineSAN(const LastMoveReport&) { return " ?? "; }

StatLines compileStatLines(const FENLineListWithParameters& femLines)
{

  StatLines statLines;
  FENLine previousLine;
  int moveNo = 0;
  bool bumpMoveNo = true;
  bool skipFirstLine = true;
  for (FENLine femLine : femLines) {
    auto placements = femLine.placement();
    StatLine statLine;
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        statLine.squares[row + col * 8] = placements.placement(col, row);
      }
    }
    statLine.whoseMove = femLine.activeColor() == 'w' ? 'b' : 'w';
    LastMoveReport lastMoveReport = determineLastMove(femLine, previousLine);
    statLine.fenLine = femLine;
    statLine.moveNo = moveNo;
    statLine.lastMove = lastMoveReport.lastMove;
    statLine.pieceMoved = lastMoveReport.pieceMoved;
    statLine.pieceTaken = lastMoveReport.pieceTaken;
    statLine.lastMove.setSAN(determineSAN(lastMoveReport));
    if (!skipFirstLine)
      statLines.push_back(statLine);
    else
      skipFirstLine = false;
    previousLine = femLine;
    if (bumpMoveNo)
      moveNo++;
    bumpMoveNo = !bumpMoveNo;
  }
  // statLines = shiftLastMove(statLines);
  return statLines;
}

StatLines merge(const StatLines& before, const PGNMoves& pgnMoves)
{
  size_t index = 0;
  StatLines updated;
  try {
    for (auto moves : pgnMoves) {
      auto whiteSan = moves.whiteSAN();
      auto blackSan = moves.blackSAN();
      if (index < before.size()) {
        StatLine whiteLine = before[index];
        whiteLine.lastMove.setSAN(whiteSan);
        updated.push_back(whiteLine);
      }
      if (index < before.size() - 1) {
        StatLine blackLine = before[index + 1];
        blackLine.lastMove.setSAN(blackSan);
        updated.push_back(blackLine);
      }
      index += 2;
    }
  }
  catch (std::exception& ex) {
    cout << ex.what() << endl;
  }
  return updated;
}

void StatWriter::convert(const FENReaderInterface& femLines,
  const PGNGameInterface& pgnMoves)
{
  auto a1 = pgnMoves.pgnmoves().size();
  auto a2 = femLines.lines().size();
  if (a1 * 2 > a2) {
    cout << femLines.lines()[0] << endl;
    auto key = pgnMoves.parameters().find("ChessgamesGameID");
    cout << key->second << endl;
    cout << "wtf" << endl;
  }
  StatLines statLines;
  statLines = compileStatLines(femLines.lines());
  statLines = merge(statLines, pgnMoves.pgnmoves());
  NextMove nextMove;
  ChessMoves nextMoves = nextMove.determine(statLines);
  statLines = nextMove.apply(statLines, nextMoves);
  this->_lines = statLines;
}
