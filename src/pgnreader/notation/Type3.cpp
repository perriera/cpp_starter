#include <iostream>
#include "../include/chessmind/pgn/notation/Type3.hpp"
#include "../include/chessmind/pgn/notation/Type1.hpp"
#include "../include/chessmind/game/ChessBoard.hpp"
#include "../include/chessmind/game/ChessExceptions.hpp"

using namespace std;

ostream &operator<<(ostream &out, const PGNotationType3 &obj)
{
    out << obj._piece;
    out << 'x';
    out << obj._san;
    return out;
}

istream &operator>>(istream &in, PGNotationType3 &obj)
{
    in >> skipws >> obj._piece;
    char x;
    in >> x;
    if (x != 'x')
        throw "Not PGNotationType3 format: " + x;
    in >> obj._san;
    return in;
}

static string typeNotation(const MovesTable &moves, const std::string &black_or_white_set, const PGNotationInterface &notation, const ChessBoard *board)
{
    for (auto move : moves)
    {
        string from = move.substr(0, 2);
        string to = move.substr(2, 2);
        char symbolAtCandidate = board->symbolAt(from);
        char symbolSoughtAfter = notation.piece();
        if (toupper(symbolAtCandidate) == symbolSoughtAfter)
            return move;
    }
    throw NoAvailableMovesException(notation.san(), black_or_white_set);
}

// static string rowNotation(const MovesTable &moves, const PGNotationInterface &san, const std::string &black_or_white_set)
// {
//     char lookingForRow = san.original()[1];
//     for (auto move : moves)
//     {
//         string from = move.substr(0, 2);
//         string to = move.substr(2, 2);
//         char rowAtCandidate = from[0];
//         char rowSoughtAfter = lookingForRow;
//         if (rowAtCandidate == rowSoughtAfter)
//             return move;
//     }
//     throw NoAvailableMovesException(san.san(), black_or_white_set);
// }

string PGNotationType3::resolve(const MovesTable &intersections, const std::string &black_or_white_set, const ChessBoard *board) const
{
    bool usingTypeNotation = isupper(piece());
    if (usingTypeNotation)
        return typeNotation(intersections, black_or_white_set, *this, board);
    else
    {
        auto selected = selectColumns(intersections, piece());
        return PGNotationType1::lowestValue(selected, board, black_or_white_set);
    }
}
