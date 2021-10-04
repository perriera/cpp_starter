#ifndef _STATLINE_HPP
#define _STATLINE_HPP

#include <iostream>
#include <vector>
#include "../fen/FENPlacement.hpp"
#include "../include/cpp_starter/game/ChessMoves.hpp"
#include "../include/cpp_starter/fen/FENLine.hpp"

//
// StatLine
// Encapsulates all behaviour unique to a PGN parser
//

struct StatLine
{
    friend std::ostream& operator<<(std::ostream& out, const StatLine& obj);
    friend std::istream& operator>>(std::istream& in, StatLine& obj);
    friend bool operator==(const StatLine& a, const StatLine& b)
    {
        std::stringstream ss1;
        ss1 << a;
        std::stringstream ss2;
        ss2 << b;
        return ss1.str() == ss2.str();
    }
    friend inline bool operator!=(const StatLine& a, const StatLine& b)
    {
        return !(a == b);
    }

    FENLine fenLine;
    int moveNo = 0;
    char squares[8 * 8];
    char whoseMove;
    ChessMove lastMove;
    char pieceMoved = ' ';
    char pieceTaken = ' ';
    ChessMove nextMove;

    operator const FENLine& () const
    {
        return fenLine;
    }
};

typedef std::vector<StatLine> StatLines;

#endif // _STATLINE_HPP
