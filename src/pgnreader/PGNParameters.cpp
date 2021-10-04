#include "../include/cpp_starter/pgn/PGNParameters.hpp"
#include "../include/cpp_starter/pgn/PGNMoves.hpp"
#include "../include/cpp_starter/pgn/PGNReader.hpp"
#include "extras/string_support.hpp"
#include <iostream>

using namespace std;
using namespace extras;

ostream& operator<<(ostream& out, const PGNParameter& obj) {
  out << '[' << obj.name << " \"" << obj.value << " \"" << ']';
  return out;
}

istream& operator>>(istream& in, PGNParameter& obj) {
  string line;
  getline(in, line);
  string new_line = remove_all(line, '[');
  new_line = remove_all(new_line, ']');
  new_line = remove_all(new_line, '\"');
  deque<string> v = split(new_line, ' ');
  string name = v.front();
  v.pop_front();
  string property;
  for (string item : v) {
    property = property + item;
    property = property + ' ';
  }
  trim(property);
  obj.name = name;
  obj.value = property;
  return in;
}

ostream& operator<<(ostream& out, const PGNParameters& obj) {
  for (auto const& x : obj)
    out << x.second << endl;
  return out;
}

void PGNParametersMismatchException::assertion(const PGNParameters& a,
  const PGNParameters& b, const extras::WhereAmI& ref) {
  if (a != b)
    throw PGNParametersMismatchException(ref);
}
