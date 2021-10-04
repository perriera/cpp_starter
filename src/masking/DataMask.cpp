#include "../include/cpp_starter/masking/DataMask.hpp"
#include "../include/cpp_starter/masking/MaskedLine.hpp"
#include "extras/string_support.hpp"
#include <iostream>

using namespace std;

ostream& operator<<(ostream& out, const DataMask& obj) {
  MaskedLines dup = obj._maskedLines;
  for (auto line : dup)
    out << line;
  return out;
}

istream& operator>>(istream& in, DataMask&) { return in; }

void DataMask::mask(const StatLines& statLines) {
  MaskedLines maskedLines;
  for (auto statLine : statLines) {
    MaskedLine maskedLine;
    maskedLine.statLine = statLine;
    maskedLines.push_back(maskedLine);
  }
  this->_maskedLines = maskedLines;
}
