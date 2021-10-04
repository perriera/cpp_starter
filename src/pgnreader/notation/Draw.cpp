#include <iostream>
#include "../include/cpp_starter/pgn/notation/Draw.hpp"

using namespace std;

istream& operator>>(istream& in, PGNotationTypeDraw& obj)
{
    in >> obj._san;
    return in;
}

string PGNotationTypeDraw::resolve(const MovesTable&, const string&, const ChessBoard*) const
{
    // should throw an exception 
    return " ";
}
