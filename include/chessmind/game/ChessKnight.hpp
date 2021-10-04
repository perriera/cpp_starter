#ifndef _CHESSKNIGHT_HPP
#define _CHESSKNIGHT_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "../include/chessmind/game/ChessBoard.hpp"
#include "../include/chessmind/game/ChessPiece.hpp"

//
// ChessKnight
// Encapsulates all behaviour unique to a chess knight piece
//

abstract class ChessKnight implements ChessPiece
{
protected:
    ChessKnight(char symbol, char col, char row)
        : ChessPiece(symbol, col, row) {}
    ChessKnight() : ChessPiece(){};

public:
    virtual MovesTable allCalculatedMoves(const ChessBoard *board);
};

//
// BlackKnight
// Encapsulates all behaviour unique to a black knight piece
//

concrete class BlackKnight implements ChessKnight
{

public:
    BlackKnight() {}
    BlackKnight(char col, char row)
        : ChessKnight('N', col, row) {}
};

//
// WhiteKnight
// Encapsulates all behaviour unique to a black knight piece
//

concrete class WhiteKnight implements ChessKnight
{

public:
    WhiteKnight() {}
    WhiteKnight(char col, char row)
        : ChessKnight('n', col, row) {}
};

#endif // _CHESSKNIGHT_HPP
