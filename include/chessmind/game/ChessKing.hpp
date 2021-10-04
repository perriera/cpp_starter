#ifndef _CHESSKING_HPP
#define _CHESSKING_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "../include/chessmind/game/ChessBoard.hpp"
#include "../include/chessmind/game/ChessPiece.hpp"

//
// ChessKing
// Encapsulates all behaviour unique to a chess king piece
//

abstract class ChessKing implements ChessPiece
{
protected:
    ChessKing(char symbol, char col, char row)
        : ChessPiece(symbol, col, row) {}
    ChessKing() : ChessPiece(){};

public:
    virtual MovesTable allCalculatedMoves(const ChessBoard *board);
};

//
// BlackKing
// Encapsulates all behaviour unique to a black king piece
//

concrete class BlackKing implements ChessKing
{

public:
    BlackKing() {}
    BlackKing(char col, char row)
        : ChessKing('K', col, row) {}
};

//
// WhiteKing
// Encapsulates all behaviour unique to a black king piece
//

concrete class WhiteKing implements ChessKing
{

public:
    WhiteKing() {}
    WhiteKing(char col, char row)
        : ChessKing('k', col, row) {}
};

#endif // _CHESSKING_HPP
