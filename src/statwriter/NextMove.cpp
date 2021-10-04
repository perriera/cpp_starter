#include "../include/chessmind/stat/NextMove.hpp"
#include "extras/string_support.hpp"
#include <iomanip>
#include <iostream>

using namespace std;

ChessMoves NextMove::determine(const StatLines &statLines) {
  ChessMoves nextMoves;
  ChessMove nextMove;
  for (auto statLine : statLines) {
    if (nextMove.assigned())
      nextMoves.push_back(nextMove);
    nextMove = statLine.lastMove;
  }
  return nextMoves;
}

StatLines NextMove::apply(const StatLines &statLines,
                          const ChessMoves &nextMoves) {
  StatLines updated;
  int index = 0;
  ChessMoves bumpedNextMoves = nextMoves;
  bumpedNextMoves.erase(bumpedNextMoves.begin());
  for (auto nextMove : bumpedNextMoves) {
    auto statLine = statLines[index++];
    statLine.nextMove = nextMove;
    updated.push_back(statLine);
  }
  return updated;
}
