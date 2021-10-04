#include "../include/chessmind/pgn/PGNGame.hpp"
#include "../include/chessmind/game/ChessBoard.hpp"
#include "../include/chessmind/pgn/PGNReader.hpp"
#include "extras/ansi_colors.hpp"
#include "extras/string_support.hpp"
#include <iostream>
#include <fstream>
#include "../include/chessmind/fen/FENReader.hpp"

using namespace std;
using namespace extras;

#define c1 magenta
#define c2 white
#define c3 yellow

ostream& operator<<(ostream& out, const PGNGame& obj) {
  // out << obj._parameters << endl;
  // out << obj._moves << endl;
  for (auto line : obj._originalFile)
    out << line << endl;
  return out;
}

istream& operator>>(istream& in, PGNGame& obj) {
  PGNReader reader;
  in >> reader;
  PGNParameters parameters;
  string all_moves;
  bool reading_parameters = true;
  obj._originalFile.clear();
  for (string line : reader.lines()) {
    obj._originalFile.push_back(line);
    trim(line);
    // cout << line << endl;
    if (line.length() == 0)
      reading_parameters = false;
    else if (reading_parameters == true) {
      PGNParameter parameter;
      stringstream ss;
      ss << line;
      ss >> parameter;
      parameters[parameter.key()] = parameter;
    }
    else
      all_moves += line + ' ';
  }
  if (all_moves.size() == 0)
    throw EndOfChessGamesException(__INFO__);
  PGNMoves moves;
  stringstream ss;
  ss << all_moves;
  ss >> moves;
  obj._parameters = parameters;
  obj._moves = moves;
  obj._moves = obj.readFENLine(moves);
  obj.determineChessMoves();
  return in;
}

istream& operator>>(istream& in, PGNGames& obj) {
  int fails = 0;
  while (in.good()) {
    try {
      PGNGame game;
      in >> game;
      obj._games.push_back(game);
      // cout << game;
    }
    catch (EndOfChessGamesException& e) {
    }
    catch (PGNtoFENMistmatchException& e) {
      cout << e.what() << endl;
      fails++;
    }
  }
  if (fails > 0)
    cout << "There were " << fails << " out of " << obj._games.size() << " fails" << endl;
  return in;
}

ostream& operator<<(ostream& out, const PGNGames& obj) {
  for (PGNGame game : obj._games)
    out << game << endl;
  return out;
}

ChessBoard PGNGame::playGameUntil(const ChessBoard& board,
  const std::string& marker) {
  ChessBoard duplicate = board;
  int cnt = 0;
  for (auto move : pgnmoves()) {
    cnt++;
    if (move.whiteSAN() == marker)
      break;
    duplicate.moveWhiteSymbol(move.whiteSAN());
    cout << duplicate.draw();
    cout << c1 << cnt << c2 << ". " << c3 << move << endl << endl;
    if (move.blackSAN() == marker)
      break;
    duplicate.moveBlackSymbol(move.blackSAN());
    cout << duplicate.draw();
    cout << c1 << cnt << c2 << ". " << c3 << move << endl << endl;
  }
  return duplicate;
}

ChessBoard PGNGame::playGameEnd(const ChessBoard& board) {
  ChessBoard duplicate = board;
  int cnt = 0;
  for (auto move : pgnmoves()) {
    cnt++;
    duplicate.moveWhiteSymbol(move.whiteSAN());
    cout << duplicate.draw();
    cout << c1 << cnt << c2 << ". " << c3 << move << endl << endl;
    duplicate.moveBlackSymbol(move.blackSAN());
    cout << duplicate.draw();
    cout << c1 << cnt << c2 << ". " << c3 << move << endl << endl;
  }
  return duplicate;
}


PGNMoves PGNGame::readFENLine(const PGNMoves& _moves) {

  string pgnFilename = "/tmp/tmpfile.pgn";
  string fenFilename = "/tmp/tmpfile.fen";
  string fenFilename2 = "/tmp/tmpfile2.fen";
  string logfile = "/tmp/tmpfile.log";
  ofstream out(pgnFilename);
  out << *this;
  //
  // for f in pgn/*; do ./pgn-extract -Wepd "$f" "pgn/$(basename "${f%.*}").pgn" -o"fen/$(basename "${f%.*}").fen"; done
  //
  string cmd = "pgn-extract -Wepd " + pgnFilename + " -o " + fenFilename + " -l" + logfile;
  system(cmd.c_str());
  system("ls /tmp -la");

  ifstream report(logfile);
  string log;
  stringstream reportIn;
  while (report.good()) {
    getline(report, log);
    reportIn << log << endl;;
  }
  this->FENreport(reportIn.str());

  ifstream myfile(fenFilename);
  FENReader parser;
  myfile >> parser;
  cout << parser.lines().size() << endl;
  ofstream myfile2(fenFilename2);
  myfile2 << parser;
  PGNtoFENMistmatchException::assertion(
    _moves.size(), parser.lines().size(), reportIn.str(), __INFO__);
  PGNMoves _updatedMoves = _moves;
  size_t i = 0;
  string fenParameters;
  _FENLineList = parser.lines();

  for (auto line : parser.lines()) {
    cout << line << endl;
    if (fenParameters != line.parameters())
      fenParameters = line.parameters();
    if (i == _moves.size()) {
      _extraFENLine = line;
      break;
    }
    if (line.isWhite())
      _updatedMoves[i].whiteFEN(line);
    else
      _updatedMoves[i++].blackFEN(line);
  }
  _totalMoves = parser.lines().size();
  this->FENparameters(fenParameters);

  return _updatedMoves;

}

ChessMoves compare(const FENLine& white, const FENLine& black, std::string value) {

  // white.placement();
  SAN san(value);
  ChessMoves _moves = FENPlacement().compare(white.placement(), black.placement(), san);
  return _moves;

}

void PGNGame::determineChessMoves() {

  for (size_t i = 0; i < this->_moves.size(); i++) {
    auto whiteMove = this->_moves[i];
    auto whiteSAN = whiteMove.whiteSAN();
    ChessMoves _whiteMoves = compare(whiteMove.whiteFEN(), whiteMove.blackFEN(), whiteSAN);
    auto lastFEN = whiteMove.blackFEN();
    auto nextFEN = whiteMove.whiteFEN();
    if (i + 1 < this->_moves.size())
      nextFEN = this->_moves[i + 1].whiteFEN();
    else
      nextFEN = this->_extraFENLine;
    auto blackSAN = whiteMove.blackSAN();
    ChessMoves _blackMoves = compare(lastFEN, nextFEN, blackSAN);
  }
  cout << "determineChessMoves" << endl;

}

void PGNGameMismatchException::assertion(const PGNGame& a,
  const PGNGame& b, const extras::WhereAmI& ref) {
  if (a != b)
    throw PGNGameMismatchException(ref);
}

void PGNtoFENMistmatchException::assertion(int sizePGN, int sizeFEN,
  const std::string& msg, const extras::WhereAmI& ref) {
  if (sizePGN * 2 != sizeFEN && (sizePGN * 2) + 1 != sizeFEN)
    throw PGNtoFENMistmatchException(msg, ref);
}

const ChessBoard& PGNGame::updateBoard(const FENLine& fenLine) {
  auto _placements = fenLine.placement();
  for (char row = '1'; row < '9'; row++)
    for (char col = 'a'; col < 'i'; col++) {
      char synbol = _placements.symbolAt(col, row);
      ChessPosition pos(col, row);
      _board.move(synbol, pos);
    }
  return _board;
}

const ChessBoard& PGNGame::next() {
  if (_nextMove == _FENLineList.size())
    throw EndOfGameReachedException("1-0", __INFO__);
  return updateBoard(_FENLineList[_nextMove++]);
}

const ChessBoard& PGNGame::previous() {
  if (_nextMove == 0)
    throw StartOfGameReachedException("---", __INFO__);
  return updateBoard(_FENLineList[--_nextMove]);
}
