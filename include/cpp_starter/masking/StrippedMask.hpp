#ifndef _STRIPPEDMASK_HPP
#define _STRIPPEDMASK_HPP

#include "../masking/MaskedLine.hpp"
#include <extras/interfaces.hpp>
#include <iostream>
#include <vector>

//
// StrippedInterface
// Encapsulates all behaviour unique to a PGN parser
//

interface StrippedInterface {
  virtual void strip(const MaskedLines &maskedLines) = 0;
};

typedef std::string StrippedLine;
typedef std::vector<std::string> StrippedLines;

class StrippedMask implements StrippedInterface {
  friend std::ostream &operator<<(std::ostream &out, const StrippedMask &obj);
  friend std::istream &operator>>(std::istream &in, StrippedMask &obj);

private:
  StrippedLines _strippedLines;

public:
  virtual void strip(const MaskedLines &maskedLines);
};

#endif // _STRIPPEDMASK_HPP
