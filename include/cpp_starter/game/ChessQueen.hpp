#ifndef _CHESSQUEEN_HPP
#define _CHESSQUEEN_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "../include/cpp_starter/game/ChessBoard.hpp"
#include "../include/cpp_starter/game/ChessPiece.hpp"

//
// ChessQueen
// Encapsulates all behaviour unique to a chess queen piece
//

abstract class ChessQueen implements ChessPiece
{
protected:
    ChessQueen(char symbol, char col, char row)
        : ChessPiece(symbol, col, row) {}
    ChessQueen() : ChessPiece() {};

public:
    virtual MovesTable allCalculatedMoves(const ChessBoard* board);
};

//
// BlackQueen
// Encapsulates all behaviour unique to a black queen piece
//

concrete class BlackQueen implements ChessQueen
{

public:
    BlackQueen() {}
    BlackQueen(char col, char row)
        : ChessQueen('Q', col, row) {}
};

//
// WhiteQueen
// Encapsulates all behaviour unique to a black queen piece
//

concrete class WhiteQueen implements ChessQueen
{

public:
    WhiteQueen() {}
    WhiteQueen(char col, char row)
        : ChessQueen('q', col, row) {}
};

#endif // _CHESSQUEEN_HPP
