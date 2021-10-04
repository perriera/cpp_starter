#ifndef _STATHEADER_HPP
#define _STATHEADER_HPP

#include <iostream>
#include <vector>

//
// StatLine
// Encapsulates all behaviour unique to a PGN parser
//

struct StatHeader
{
    friend std::ostream &operator<<(std::ostream &out, const StatHeader &obj);
    friend std::istream &operator>>(std::istream &in, StatHeader &obj);

    std::string stripped() const;
};

#endif // _STATLINE_HPP
