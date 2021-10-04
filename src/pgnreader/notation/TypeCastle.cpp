#include <iostream>
#include "../include/cpp_starter/pgn/notation/TypeCastle.hpp"
#include "../include/cpp_starter/game/ChessBoard.hpp"

using namespace std;

istream& operator>>(istream& in, PGNotationTypeCastle& obj)
{
    in >> obj._san;
    return in;
}

string PGNotationTypeCastle::resolve(const MovesTable&, const string& black_or_white_set, const ChessBoard* board) const
{
    bool white_or_black = islower(black_or_white_set[0]);
    if (kingCastle())
    {
        ChessBoard& b = const_cast<ChessBoard&>(*board);
        b.move(white_or_black ? "e1g1" : "e8g8");
        return white_or_black ? "h1f1" : "h8f8";
    }
    if (queenCastle())
    {
        ChessBoard& b = const_cast<ChessBoard&>(*board);
        b.move(white_or_black ? "e1c1" : "e8c8");
        return white_or_black ? "a1d1" : "a8d8";
    }
    throw "Not a castle code";
}
