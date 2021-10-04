#include "../include/chessmind/stat/StatHeader.hpp"
#include "extras/string_support.hpp"
#include <iostream>

using namespace std;
using namespace extras;

ostream &operator<<(ostream &out, const StatHeader &) {
  out << "nnn, c, last, next, x1, x2,     san, ";
  for (char row = '8'; row > '0'; row--) {
    for (char col = 'a'; col < 'i'; col++) {
      out << col << row << ", ";
    }
  }
  return out;
}

istream &operator>>(istream &in, StatHeader &) {
  in >> skipws;
  return in;
}

std::string StatHeader::stripped() const {
  stringstream ss;
  ss << *this;
  string text = ss.str();
  text = remove_all(text, ' ');
  text = replace_all(text, ",h1,", ",h1");
  return text;
}