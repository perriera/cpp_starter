#ifndef _STATWRITER_HPP
#define _STATWRITER_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include "StatLine.hpp"
#include "../fen/FENReader.hpp"
#include "../pgn/PGNGame.hpp"
#include "../include/cpp_starter/csv/CSVInterface.hpp"

//
// StatWriter
// Encapsulates all behaviour unique to a PGN parser
//

interface StatWriterInterface
{
    virtual void convert(const FENReaderInterface& femLines, const PGNGameInterface& pgnMoves) pure;
};

class StatWriter implements StatWriterInterface, CSVInterface
{
    friend std::ostream& operator<<(std::ostream& out, const StatWriter& obj);
    friend std::istream& operator>>(std::istream& in, StatWriter& obj);
    friend bool operator==(const StatWriter& a, const StatWriter& b)
    {
        std::stringstream ss1;
        ss1 << a;
        std::stringstream ss2;
        ss2 << b;
        return ss1.str() == ss2.str();
    }
    friend inline bool operator!=(const StatWriter& a, const StatWriter& b)
    {
        return !(a == b);
    }

private:
    StatLines _lines;

public:
    const StatLines& lines() { return _lines; }
    virtual void convert(const FENReaderInterface& femLines, const PGNGameInterface& pgnMoves);
    virtual std::string csv_out() const;
    virtual void csv_in(const std::string& csv);
};

#endif // _STATWRITER_HPP
