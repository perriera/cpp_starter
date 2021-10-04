#include <iostream>
#include <ctype.h>
#include "../include/cpp_starter/pgn/notation/Type1.hpp"
#include "../include/cpp_starter/game/ChessBoard.hpp"
#include "../include/cpp_starter/game/ChessExceptions.hpp"

using namespace std;

istream& operator>>(istream& in, PGNotationType1& obj)
{
    in >> obj._san;
    return in;
}

string PGNotationType1::lowestValue(const MovesTable& moves, const ChessBoard* board, const std::string& black_or_white_set)
{
    int rank1 = -1;
    string bestMove;
    for (auto move : moves)
    {
        char value = board->symbolAt(move);
        int pos = black_or_white_set.find(value);
        if (pos < rank1 || rank1 == -1)
        {
            rank1 = pos;
            bestMove = move;
        }
        else if (pos == rank1)
        {
            char col1 = bestMove[0];
            char col2 = move[0];
            if (col2 > col1) {
                bestMove = move;
            }
        }
    }
    if (rank1 == -1)
        throw NoAvailableMovesException("lowestValue", black_or_white_set);

    return bestMove;
}

string PGNotationType1::resolve(const MovesTable& intersections, const string& black_or_white_set, const ChessBoard* board) const
{

    if (intersections.size() == 1)
        return intersections.front();
    else
        return lowestValue(intersections, board, black_or_white_set);
}
