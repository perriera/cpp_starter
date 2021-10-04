#ifndef _PGTYPECASTLE_HPP
#define _PGTYPECASTLE_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include "../PGNotation.hpp"

class PGNotationTypeCastle implements PGNotationInterface
{
    friend std::ostream &operator<<(std::ostream &out, const PGNotationTypeCastle &obj);
    friend std::istream &operator>>(std::istream &in, PGNotationTypeCastle &obj);

    const std::string _original;
    std::string _san;

public:
    PGNotationTypeCastle(){};
    PGNotationTypeCastle(const std::string &san) : _original(san)
    {
        std::stringstream ss;
        ss << san;
        ss >> *this;
    };
    virtual bool equals(const PGNotationInterface &a)
    {
        return san() == a.san();
    };
    virtual bool equals(const std::string &a)
    {
        return san() == a;
    };

    inline char piece() const { throw "PGNotationTypeCastle"; }
    inline const std::string &san() const { return _san; }
    virtual bool castle() const { return kingCastle() || queenCastle(); }
    virtual bool kingCastle() const { return san() == "O-O"; }
    virtual bool queenCastle() const { return san() == "O-O-O"; }
    virtual bool gameover() const { return false; }
    virtual int type() const { return -1; }
    virtual const std::string &original() const { return _original; }
    virtual std::string resolve(const MovesTable &intersections, const std::string &black_or_white_set, const ChessBoard *board) const;
    virtual bool promotion() const { return false; }
};

#endif // _PGTYPECASTLE_HPP
