#ifndef _CHESSPAWN_HPP
#define _CHESSPAWN_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "../include/cpp_starter/game/ChessBoard.hpp"
#include "../include/cpp_starter/game/ChessPiece.hpp"

//
// ChessPawn
// Encapsulates all behaviour unique to a chess pawn piece
//

abstract class ChessPawn implements ChessPiece
{
protected:
    ChessPawn(char symbol, char col, char row)
        : ChessPiece(symbol, col, row) {}
    ChessPawn() : ChessPiece() {};

public:
    virtual MovesTable allCalculatedMoves(const ChessBoard* board);
    static std::string addPosition(char col, char row);
    bool pawnAtStart() const;
};

//
// BlackPawn
// Encapsulates all behaviour unique to a black pawn piece
//

concrete class BlackPawn implements ChessPawn
{

public:
    BlackPawn() {}
    BlackPawn(char col, char row)
        : ChessPawn('P', col, row) {}
};

//
// WhitePawn
// Encapsulates all behaviour unique to a white pawn piece
//

concrete class WhitePawn implements ChessPawn
{

public:
    WhitePawn() {}
    WhitePawn(char col, char row)
        : ChessPawn('p', col, row) {}
};

#endif // _CHESSPAWN_HPP
