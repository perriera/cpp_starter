#include <iostream>
#include "../include/chessmind/pgn/notation/Type4.hpp"
#include "../include/chessmind/game/ChessBoard.hpp"
#include "../include/chessmind/game/ChessExceptions.hpp"

using namespace std;

istream &operator>>(istream &in, PGNotationType4 &obj)
{
    in >> skipws >> obj._piece;
    char c;
    in >> c;
    if (c == 'x')
        throw "Not PGNotationType4 format: " + c;
    in >> obj._san;
    return in;
}

static string colNotation(const MovesTable &moves, const PGNotationInterface &san, const std::string &black_or_white_set)
{
    char lookingForCol = san.original()[1];
    for (auto move : moves)
    {
        string from = move.substr(0, 2);
        string to = move.substr(2, 2);
        char colAtCandidate = from[1];
        char colSoughtAfter = lookingForCol;
        if (colAtCandidate == colSoughtAfter)
            return move;
    }
    throw NoAvailableMovesException(san.san(), black_or_white_set);
}

static string rowNotation(const MovesTable &moves, const PGNotationInterface &san, const std::string &black_or_white_set)
{
    char lookingForRow = san.original()[1];
    for (auto move : moves)
    {
        string from = move.substr(0, 2);
        string to = move.substr(2, 2);
        char rowAtCandidate = from[0];
        char rowSoughtAfter = lookingForRow;
        if (rowAtCandidate == rowSoughtAfter)
            return move;
    }
    throw NoAvailableMovesException(san.san(), black_or_white_set);
}

string PGNotationType4::resolve(const MovesTable &intersections, const string &black_or_white_set, const ChessBoard *board) const
{
    auto _original = original();
    char lookingForRowOrCol = _original[1];
    if (isalpha(lookingForRowOrCol))
    {
        MovesTable selected = selectPiece(intersections,piece(),board);
        return rowNotation(selected, *this, black_or_white_set);
    }
    else
    {
        MovesTable selected = selectPiece(intersections,piece(),board);
        return colNotation(selected, *this, black_or_white_set);
    }
}
