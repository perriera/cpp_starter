#ifndef _PGTYPEONE_HPP
#define _PGTYPEONE_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include "../PGNotation.hpp"

class PGNotationType1 implements PGNotationInterface
{
    friend std::ostream &operator<<(std::ostream &out, const PGNotationType1 &obj);
    friend std::istream &operator>>(std::istream &in, PGNotationType1 &obj);

    const std::string _original;
    std::string _san;

public:
    PGNotationType1(){};
    PGNotationType1(const std::string &san) : _original(san)
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

    inline char piece() const { throw "Unknown"; }
    inline const std::string &san() const { return _san; }
    virtual bool castle() const { return false; }
    virtual bool kingCastle() const { return false; }
    virtual bool queenCastle() const { return false; }
    virtual bool gameover() const { return false; }
    virtual int type() const { return 1; }
    virtual const std::string &original() const { return _original; }
    virtual std::string resolve(const MovesTable &intersections, const std::string &black_or_white_set, const ChessBoard *board) const;
    static std::string lowestValue(const MovesTable &moves, const ChessBoard *board, const std::string &black_or_white_set);
    virtual bool promotion() const { return false; }
};

#endif // _PGTYPEONE_HPP
