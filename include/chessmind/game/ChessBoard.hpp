#ifndef _CHESSBOARD_HPP
#define _CHESSBOARD_HPP

#include <iostream>
#include <string>
#include <map>
#include "../include/chessmind/game/ChessPiece.hpp"
#include "../include/chessmind/pgn/PGNotation.hpp"
#include "../include/chessmind/game/ChessPosition.hpp"
#include "../include/chessmind/pgn/PGNSymbolsInterface.hpp"

//
// ChessBoardInterface
// Encapsulates all behaviour unique to a chess board
//

interface ChessBoardInterface
{
    virtual char move(char piece, std::string col_row) = 0;
    virtual char move(std::string from, std::string to) = 0;
    virtual char move(std::string from_to) = 0;
    virtual std::string lastMove() const = 0;

    virtual bool spaceOccupied(const ChessPiece *piece, const std::string &move) const = 0;
    virtual bool spaceOccupiable(const ChessPiece *piece, const std::string &move) const = 0;
    virtual bool spaceTakeable(const ChessPiece *piece, const std::string &move) const = 0;
    virtual bool squarePawnAttackable(const ChessPiece *piece, const std::string &move) const = 0;

    virtual char moveSymbol(const std::string &san, const std::string &black_or_white_set) = 0;
    virtual char moveWhiteSymbol(std::string san) = 0;
    virtual char moveBlackSymbol(std::string san) = 0;
};

//
// ChessBoard class
//

typedef std::map<std::string, ChessPiece> ChessTable;

class ChessBoard implements ChessBoardInterface, SymbolAtInterface
{
    friend std::ostream &operator<<(std::ostream &out, const ChessBoard &obj);
    friend std::istream &operator>>(std::istream &in, ChessBoard &obj);

    MovesTable _moveHistory = MovesTable();
    ChessTable chessTable = ChessTable();

    char _pieces[8][8] = {
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};

    ChessPiece selectChessPiece(char piece, char col, char row) const;
    void compileChessTable();
    void eraseEnPassantShadow(const std::string &from, const std::string &to);

public:
    ChessBoard();
    void invalidate(const std::string &lastMove);

    inline MovesTable &moveHistory() { return _moveHistory; }

    std::string draw();
    std::string draw_inverted();

    virtual char symbolAt(char col, char row) const;
    virtual char symbolAt(const ChessPosition &pos) const;
    char symbolAt(const std::string &col_row) const;
    ChessPiece pieceAt(char col, char row) const;
    inline ChessPiece pieceAt(const std::string &col_row) const
    {
        if (col_row.size() != 2)
            throw "wrong size: " + col_row;
        return pieceAt(col_row[0], col_row[1]);
    }
    inline char setPiece(ChessPosition pos, char symbol)
    {
        return move(symbol, pos);
    }
    char move(char piece, std::string col_row);
    char move(std::string from, std::string to);
    char move(std::string from_to);
    inline std::string lastMove() const { return _moveHistory.size() == 0 ? "" : _moveHistory.back(); }

    bool spaceOccupied(const ChessPiece *piece, const std::string &move) const;
    bool spaceOccupiable(const ChessPiece *piece, const std::string &move) const;
    bool spaceTakeable(const ChessPiece *piece, const std::string &move) const;
    bool squarePawnAttackable(const ChessPiece *piece, const std::string &move) const;

    char moveSymbol(const std::string &san, const std::string &black_or_white_set);
    inline char moveWhiteSymbol(std::string san) { return moveSymbol(san, "pbnrqk"); }
    inline char moveBlackSymbol(std::string san) { return moveSymbol(san, "PBNRQK"); }
};

#endif // _CHESSBOARD_HPP
