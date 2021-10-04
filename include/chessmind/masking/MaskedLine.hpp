#ifndef _MASKEDLINE_HPP
#define _MASKEDLINE_HPP

#include <iostream>
#include <vector>
#include <string>
#include "../stat/StatLine.hpp"

//
// FENReader
// Encapsulates all behaviour unique to a PGN parser
//

struct MaskedLine
{
    friend std::ostream &operator<<(std::ostream &out, const MaskedLine &obj);
    friend std::istream &operator>>(std::istream &in, MaskedLine &obj);

    StatLine statLine;

public:
};

typedef std::vector<MaskedLine> MaskedLines;

#endif // _MASKEDLINE_HPP
