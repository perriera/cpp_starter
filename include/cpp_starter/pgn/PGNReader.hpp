#ifndef _PGNREADER_HPP
#define _PGNREADER_HPP

#include <iostream>
#include <vector>
#include <string>

//
// PGNReader
// Encapsulates all behaviour unique to a PGN parser 
//

typedef std::string PGNLine;
typedef std::vector<PGNLine> PGNLines;

class PGNReader
{
    friend std::ostream &operator<<(std::ostream &out, const PGNReader &obj);
    friend std::istream &operator>>(std::istream &in, PGNReader &obj);

private:
    PGNLines _lines;
public:
    const PGNLines& lines() { return _lines; }
};

#endif // _PGNREADER_HPP
