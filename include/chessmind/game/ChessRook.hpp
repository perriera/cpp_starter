#ifndef _CHESSROOK_HPP
#define _CHESSROOK_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "../include/chessmind/game/ChessBoard.hpp"
#include "../include/chessmind/game/ChessPiece.hpp"

//
// ChessRook
// Encapsulates all behaviour unique to a chess rook piece
//

abstract class ChessRook implements ChessPiece
{
protected:
    ChessRook(char symbol, char col, char row)
        : ChessPiece(symbol, col, row) {}
    ChessRook() : ChessPiece(){};

public:
    virtual MovesTable allCalculatedMoves(const ChessBoard *board);
    static MovesTable addDirection(char col, char row, int up, int right, const ChessBoard *board, const ChessPiece *piece);
};

//
// BlackRook
// Encapsulates all behaviour unique to a black rook piece
//

concrete class BlackRook implements ChessRook
{

public:
    BlackRook() {}
    BlackRook(char col, char row)
        : ChessRook('R', col, row) {}
};

//
// WhiteRook
// Encapsulates all behaviour unique to a black rook piece
//

concrete class WhiteRook implements ChessRook
{

public:
    WhiteRook() {}
    WhiteRook(char col, char row)
        : ChessRook('r', col, row) {}
};

#endif // _CHESSROOK_HPP
