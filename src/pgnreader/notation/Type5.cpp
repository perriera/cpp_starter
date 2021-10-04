#include <iostream>
#include "../include/cpp_starter/pgn/notation/Type5.hpp"
#include "../include/cpp_starter/game/ChessBoard.hpp"
#include "../include/cpp_starter/game/ChessExceptions.hpp"
#include "../include/cpp_starter/game/ChessExceptions.hpp"

using namespace std;

ostream& operator<<(ostream& out, const PGNotationType5& obj)
{
    out << obj._piece;
    out << 'x';
    out << obj._san;
    return out;
}

istream& operator>>(istream& in, PGNotationType5& obj)
{
    in >> skipws >> obj._piece;
    in >> skipws >> obj._row_or_column;
    char x;
    in >> x;
    if (x != 'x')
        throw "Not PGNotationType5 format: " + x;
    in >> obj._san;
    return in;
}

// static string typeNotation(const MovesTable &moves, const std::string &black_or_white_set, const PGNotationInterface &notation, const ChessBoard *board)
// {
//     for (auto move : moves)
//     {
//         string from = move.substr(0, 2);
//         string to = move.substr(2, 2);
//         char symbolAtCandidate = board->symbolAt(from);
//         char symbolSoughtAfter = notation.piece();
//         if (toupper(symbolAtCandidate) == symbolSoughtAfter)
//             return move;
//     }
//     throw NoAvailableMovesException(notation.san(), black_or_white_set);
// }

static string rowNotation(const MovesTable& moves, const PGNotationInterface& notation, const std::string& black_or_white_set)
{
    for (auto move : moves)
    {
        string from = move.substr(0, 2);
        string to = move.substr(2, 2);
        char rowAtCandidate = from[0];
        char rowSoughtAfter = notation.piece();
        if (rowAtCandidate == rowSoughtAfter)
            return move;
    }
    throw NoAvailableMovesException(notation.san(), black_or_white_set);
}

string PGNotationType5::resolve(const MovesTable& intersections, const std::string& black_or_white_set, const ChessBoard* board) const
{
    bool usingTypeNotation = isupper(piece());
    if (usingTypeNotation)
    {
        char columnToSelect = original()[1];
        MovesTable selected;
        if (isalpha(columnToSelect))
            selected = selectColumns(intersections, columnToSelect);
        else
            selected = selectRows(intersections, columnToSelect);

        if (selected.size() == 0)
            throw NoAvailableMovesException(san(), black_or_white_set);
        MovesTable filtered = selectPiece(selected, piece(), board);
        if (filtered.size() == 0)
            throw NoAvailableMovesException(san(), black_or_white_set);
        if (filtered.size() == 1)
            return filtered.front();
        ChessMove selected_piece = rowPriority(filtered);

        return selected_piece;

        //        return typeNotation(selected, black_or_white_set, *this, board);
    }
    else
        return rowNotation(intersections, *this, black_or_white_set);
}
