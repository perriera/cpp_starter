#ifndef _PGTYPEFOUR_HPP
#define _PGTYPEFOUR_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include "../PGNotation.hpp"

class PGNotationType4 implements PGNotationInterface
{
    friend std::ostream &operator<<(std::ostream &out, const PGNotationType4 &obj);
    friend std::istream &operator>>(std::istream &in, PGNotationType4 &obj);

    char _piece;
    const std::string _original;
    std::string _san;

public:
    PGNotationType4(){};
    PGNotationType4(const std::string &san) : _original(san)
    {
        std::stringstream ss;
        ss << san;
        ss >> *this;
    };
    virtual bool equals(const PGNotationInterface &a)
    {
        return (san() == a.san() && piece() == a.piece());
    };
    virtual bool equals(const std::string &a)
    {
        return san() == a;
    };

    inline char piece() const { return _piece; }
    inline const std::string &san() const { return _san; }
    virtual bool castle() const { return false; }
    virtual bool kingCastle() const { return false; }
    virtual bool queenCastle() const { return false; }
    virtual bool gameover() const { return false; }
    virtual int type() const { return 4; }
    virtual const std::string &original() const { return _original; }
    virtual std::string resolve(const MovesTable &intersections, const std::string &black_or_white_set, const ChessBoard *board) const;
    virtual bool promotion() const { return false; }
};

#endif // _PGTYPEFOUR_HPP
