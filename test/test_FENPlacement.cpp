#include <fstream>
#include <iostream> // std::cout
#include <sstream>  // std::stringstream
#include <string>   // std::string

#include "../include/cpp_starter/fen/FENPlacement.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO("Verify FENPlacement", "[FENPlacement]") {
  FENPlacement basic;
  cout << basic << endl;
  REQUIRE(basic.operator std::string().size() == 43);
}

SCENARIO("Verify FENPlacement (ii)", "[FENPlacement]") {
  FENPlacement before;
  stringstream ss;
  ss << before;
  string str = ss.str();
  str[12] = '1';
  cout << before << endl;
  cout << str << endl;
  stringstream ss2;
  ss2 << str << flush;
  FENPlacement after;
  ss2 >> after;
  cout << after << endl;
  REQUIRE(before != after);
}
