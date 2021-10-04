#ifndef _CHESSBISHOP_HPP
#define _CHESSBISHOP_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "../include/cpp_starter/game/ChessBoard.hpp"
#include "../include/cpp_starter/game/ChessPiece.hpp"

//
// ChessBishop
// Encapsulates all behaviour unique to a chess bishop piece
//

abstract class ChessBishop implements ChessPiece
{
protected:
    ChessBishop(char symbol, char col, char row)
        : ChessPiece(symbol, col, row) {}
    ChessBishop() : ChessPiece() {};

public:
    virtual MovesTable allCalculatedMoves(const ChessBoard* board);
    static MovesTable addDirection(char col, char row, bool up, bool right, const ChessBoard* board, const ChessPiece* piece);

};

//
// BlackBishop
// Encapsulates all behaviour unique to a black bishop piece
//

concrete class BlackBishop implements ChessBishop
{

public:
    BlackBishop() {}
    BlackBishop(char col, char row)
        : ChessBishop('B', col, row) {}
};

//
// WhiteBishop
// Encapsulates all behaviour unique to a black bishop piece
//

concrete class WhiteBishop implements ChessBishop
{

public:
    WhiteBishop() {}
    WhiteBishop(char col, char row)
        : ChessBishop('b', col, row) {}
};

#endif // _CHESSBISHOP_HPP
