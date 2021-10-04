#include <iostream>
#include "../include/chessmind/pgn/notation/Type2.hpp"
#include "../include/chessmind/game/ChessBoard.hpp"
#include "../include/chessmind/game/ChessExceptions.hpp"

using namespace std;

istream &operator>>(istream &in, PGNotationType2 &obj)
{
    in >> skipws >> obj._piece;
    in >> obj._san;
    return in;
}

string PGNotationType2::resolve(const MovesTable &intersections, const string &black_or_white_set, const ChessBoard *board) const
{
    if (intersections.size() == 0)
        throw NoAvailableMovesException(san(), black_or_white_set);
    MovesTable filtered = selectPiece(intersections, piece(), board);
    if (filtered.size() == 0)
        throw NoAvailableMovesException(san(), black_or_white_set);
    if (filtered.size() == 1)
        return filtered.front();
    ChessMove selected = rowPriority(filtered);
    return selected;
}
