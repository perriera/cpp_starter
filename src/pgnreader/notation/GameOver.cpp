#include <iostream>
#include "../include/chessmind/pgn/notation/GameOver.hpp"

using namespace std;

istream &operator>>(istream &in, PGNotationTypeGameOver &obj)
{
    in >> obj._san;
    return in;
}

string PGNotationTypeGameOver::resolve(const MovesTable &, const string &, const ChessBoard *) const 
{
    // should throw an exception 
    return " ";
}
