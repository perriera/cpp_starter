#include "../include/cpp_starter/ai/CrossTableMap.hpp"
#include "extras/ansi_colors.hpp"
#include "extras/crc16_support.hpp"
#include "extras/crc64_support.hpp"
#include "extras/string_support.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;
using namespace extras;

ostream& operator<<(ostream& out, const CrossTableMap& obj) {
  out << "key (crc64), FEN Line, moveno, color moved, last move, ";
  out << "last san, next move, next san, piece moved, piece taken, ";
  out << "optional moves" << endl;
  for (auto ctl : obj._map)
    out << ctl.second << endl;
  return out;
}

istream& operator>>(istream& in, CrossTableMap& obj) {
  string header;
  getline(in, header);
  while (in.good()) {
    string line;
    getline(in, line);
    stringstream ss;
    ss << line;
    CrossTableLine ctl;
    ss >> ctl;
    obj._map[ctl] = ctl;
  }
  return in;
}

void CrossTableMap::insert(const StatLine& line) {
  CrossTableLine ctl(line);
  auto it = _map.find(ctl);
  if (it == _map.end())
    _map[ctl] = ctl;
  else {
    auto ctl = it->second;
    ChessMoves chessMoves = ctl.operator ChessMoves();
    ChessMove nextMove = line.nextMove;
    for (auto chessMove : chessMoves)
      if (chessMove == nextMove)
        return;
    chessMoves.push_back(nextMove);
    ctl.append(nextMove);
    _map[ctl] = ctl;
  }
}

void CrossTableMap::train(const StatLines& statLines) {
  for (auto line : statLines) {
    insert(line);
    predict(line.fenLine);
  }
}

int CrossTableMap::size() const { return _map.size(); }

CrossTableLine CrossTableMap::predict(const FENLine& fenLine) {
  crc64 _crc;
  auto key = _crc.update(fenLine);
  auto it = _map.find(key);
  CrossTableMapException::assertation(_map, key, fenLine);
  return it->second;
}

void CrossTableMapException::assertation(const CrossTableLineMap& map,
  const CrossTableLineKey& key,
  const FENLine& fenLine) {
  if (map.find(key) == map.end())
    throw CrossTableMapException(fenLine);
}
