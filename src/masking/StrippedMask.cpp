#include "../include/chessmind/masking/StrippedMask.hpp"
#include "extras/string_support.hpp"
#include <iostream>

using namespace std;
using namespace extras;

ostream &operator<<(ostream &out, const StrippedMask &obj) {
  auto dup = obj._strippedLines;
  for (auto line : dup)
    out << line << endl;
  return out;
}

istream &operator>>(istream &in, StrippedMask &) { return in; }

void StrippedMask::strip(const MaskedLines &maskedLines) {
  StrippedLines strippedLines;
  for (auto maskedLine : maskedLines) {
    stringstream ss;
    ss << maskedLine;
    StrippedLine strippedLine = ss.str();
    strippedLine = remove_all(strippedLine, ' ');
    strippedLine = replace_all(strippedLine, ",\n", "");
    strippedLines.push_back(strippedLine);
  }
  this->_strippedLines = strippedLines;
}
