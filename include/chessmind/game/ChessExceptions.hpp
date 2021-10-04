#ifndef _CHESSEXCEPTIONS_HPP
#define _CHESSEXCEPTIONS_HPP

#include <iostream>
#include <string>
#include <map>
#include "../include/chessmind/game/ChessBoard.hpp"

//
// Custom exceptions
//

struct OutOfBoundsException : public std::exception
{
    std::string _msg = "Can't move to ";

public:
    OutOfBoundsException(char col, char row)
    {
        _msg += col;
        _msg += row;
    };
    OutOfBoundsException(const std::string &from_to)
    {
        _msg += from_to;
    };
    const char *what() const throw() { return _msg.c_str(); };
    static void assertation(const std::string &from_to)
    {
        if (from_to.size() != 2)
            throw OutOfBoundsException(from_to);
        char col = from_to[0];
        char row = from_to[1];
        return assertation(col, row);
    }
    static void assertation(char x, char y)
    {
        if (x < 8 || y < 8)
        {
            if (y < 0 || y > 7 || x < 0 || x > 7)
                throw OutOfBoundsException(x + 'a', '8' - y);
        }
        else
        {
            if (x < 'a' || x > 'h' || y < '1' || y > '8')
                throw OutOfBoundsException(x, y);
        }
    }
};

struct ImpossibleMoveException : public std::exception
{
    std::string _msg;

public:
    ImpossibleMoveException(char piece, char col, char row, const std::string &to)
    {
        _msg += piece;
        _msg += " can't do a ";
        _msg += col;
        _msg += row;
        _msg += to;
    };
    const char *what() const throw() { return _msg.c_str(); };
};

struct InvalidPGNFileException : public std::exception
{
    std::string _msg;

public:
    InvalidPGNFileException(const PGNotation &notation)
    {
        _msg += "ChessBoard has more then one piece that can occupy: ";
        _msg += notation.san();
    };
    InvalidPGNFileException(const std::string &to)
    {
        _msg += "ChessBoard has more then one piece that can occupy: ";
        _msg += to;
    };
    const char *what() const throw() { return _msg.c_str(); };
};

struct InvalidSANFileException : public std::exception
{
    std::string _msg;

public:
    InvalidSANFileException(const std::string &to)
    {
        _msg += "Unsupported SAN format: ";
        _msg += to;
    };
    const char *what() const throw() { return _msg.c_str(); };
};

struct NoAvailableMovesException : public std::exception
{
    std::string _msg;

public:
    NoAvailableMovesException(std::string san, std::string set)
    {
        _msg += "No pieces available to move to ";
        _msg += san;
        _msg += " (";
        _msg += set;
        _msg += ") ";
    };
    const char *what() const throw() { return _msg.c_str(); };
};

struct PGNFormatDetectedException : public std::exception
{
    std::string _msg;

public:
    PGNFormatDetectedException(const std::string &line)
    {
        _msg += "PGN (SAN) format detected: ";
        _msg += line;
    };
    const char *what() const throw() { return _msg.c_str(); };
    static void assertation(const std::string &line)
    {
        if (line != "" && line.at(0) == '[')
            throw PGNFormatDetectedException(line);
    }
};

#endif // _CHESSEXCEPTIONS_HPP
