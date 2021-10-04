#include "../include/cpp_starter/fen/FENReader.hpp"
#include "../include/cpp_starter/fen/FENLine.hpp"
#include "extras/string_support.hpp"
#include <iostream>

using namespace std;

ostream& operator<<(ostream& out, const FENReader& obj) {
  FENLineListWithParameters dup = obj._lines;
  for (auto line : dup)
    out << line << endl;
  return out;
}

istream& operator>>(istream& in, FENReader& obj) {
  while (!in.eof()) {
    string text;
    getline(in, text);
    if (text.size() == 0)
      break;
    stringstream ss;
    ss << text;
    FENLineWithParameters line;
    ss >> line;
    obj._lines.push_back(line);
  }
  return in;
}
