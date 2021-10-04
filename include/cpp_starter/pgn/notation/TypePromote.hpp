#ifndef _PGTYPEPROMOTE_HPP
#define _PGTYPEPROMOTE_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include "../PGNotation.hpp"
#include "../include/cpp_starter/game/ChessPosition.hpp"

class PGNotationTypePromote implements PGNotationInterface
{
    friend std::ostream& operator<<(std::ostream& out, const PGNotationTypePromote& obj);
    friend std::istream& operator>>(std::istream& in, PGNotationTypePromote& obj);

private:

    const std::string _original;
    std::string _san;
    ChessPosition _position;
    char _promotion;

public:
    PGNotationTypePromote() {};
    PGNotationTypePromote(const std::string& san) : _original(san)
    {
        std::stringstream ss;
        ss << san;
        ss >> *this;
    };
    virtual bool equals(const PGNotationInterface& a)
    {
        return san() == a.san();
    };
    virtual bool equals(const std::string& a)
    {
        return san() == a;
    };

    inline char piece() const { throw "PGNotationTypePromote"; }
    inline const std::string& san() const { return _san; }
    virtual bool castle() const { return kingCastle() || queenCastle(); }
    virtual bool kingCastle() const { return san() == "O-O"; }
    virtual bool queenCastle() const { return san() == "O-O-O"; }
    virtual bool gameover() const { return false; }
    virtual int type() const { return -1; }
    virtual const std::string& original() const { return _original; }
    virtual std::string resolve(const MovesTable& intersections, const std::string& black_or_white_set, const ChessBoard* board) const;
    virtual bool promotion() const { return true; }
};

struct TypePromoteException : public std::exception
{
    std::string _msg;

public:
    TypePromoteException(const std::string& to)
    {
        _msg += "Unsupported SAN format: ";
        _msg += to;
    };
    const char* what() const throw() { return _msg.c_str(); };
    static void assertation(char c);
};

#endif // _PGTYPEPROMOTE_HPP
