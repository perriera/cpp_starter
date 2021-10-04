#include "../include/cpp_starter/pgn/PGNReader.hpp"
#include "extras/string_support.hpp"
#include <iostream>

using namespace std;
using namespace extras;

ostream& operator<<(ostream& out, const PGNReader& obj) {
  vector<string> dup = obj._lines;
  for (string line : dup)
    out << line << endl;
  return out;
}

istream& operator>>(istream& in, PGNReader& obj) {
  vector<string> lines;
  int breakCnt = 0;
  while (!in.eof() && breakCnt < 2) {
    string line;
    getline(in, line);
    trim(line);
    if (line.size() == 0)
      breakCnt++;
    lines.push_back(line);
  }
  if (breakCnt == 2) {
    string line;
    getline(in, line);
  }
  obj._lines = lines;
  return in;
}
