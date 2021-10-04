#include <fstream>
#include <iostream> // std::cout
#include <sstream>  // std::stringstream
#include <string>   // std::string

#include "../include/chessmind/fen/FENLine.hpp"
#include "../include/chessmind/fen/FENPlacement.hpp"
#include "../include/chessmind/fen/FENReader.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO("Verify FENLine read (on line)", "[FENLine]") {
  ifstream myfile("data/fen/kasparov_muratkuliev_1973.fen");
  REQUIRE(myfile.good());
  FENLine line1;
  myfile >> line1;
  cout << line1 << endl;
  stringstream ss;
  ss << line1;
  FENLine line2;
  ss >> line2;
  REQUIRE(line1 == line2);
}

SCENARIO("Verify FENLineWithParameters read (on line)", "[FENLine]") {
  ifstream myfile("data/fen/kasparov_muratkuliev_1973.fen");
  REQUIRE(myfile.good());
  FENLineWithParameters line1;
  myfile >> line1;
  cout << line1 << endl;
  stringstream ss;
  ss << line1;
  FENLineWithParameters line2;
  ss >> line2;
  REQUIRE(line1 == line2);
}

string makeFENLineFile() {
  ifstream myfile("data/fen/kasparov_muratkuliev_1973.fen");
  stringstream ss;
  while (myfile.good()) {
    FENLine line1;
    myfile >> line1;
    string skip;
    getline(myfile, skip);
    if (!myfile.good())
      break;
    ss << line1 << endl;
  }
  return ss.str();
}

SCENARIO("Verify FENLine read", "[FENLine]") {
  string stripped = makeFENLineFile();
  stringstream myfile;
  myfile << stripped;
  REQUIRE(myfile.good());
  int cnt = 0;
  while (myfile.good()) {
    FENLine line1;
    myfile >> line1;
    if (!myfile.good())
      break;
    cout << ++cnt << ' ' << line1 << endl;
    stringstream ss;
    ss << line1;
    FENLine line2;
    ss >> line2;
    REQUIRE(line1 == line2);
    stringstream ss2;
    ss2 << line2;
    FENLine line3;
    ss2 >> line3;
    stringstream ss3;
    ss3 << line3;
    FENLine line4;
    ss3 >> line4;
    REQUIRE(line3 == line4);
  }
}

SCENARIO("Verify FENLineWithParameters read", "[FENLine]") {
  ifstream myfile("data/fen/kasparov_muratkuliev_1973.fen");
  REQUIRE(myfile.good());
  int cnt = 0;
  while (myfile.good()) {
    FENLineWithParameters line1;
    myfile >> line1;
    if (!myfile.good())
      break;
    cout << ++cnt << ' ' << line1 << endl;
    stringstream ss;
    ss << line1;
    FENLineWithParameters line2;
    ss >> line2;
    REQUIRE(line1 == line2);
    stringstream ss2;
    ss2 << line2;
    FENLine line3;
    ss2 >> line3;
    stringstream ss3;
    ss3 << line3;
    FENLine line4;
    ss3 >> line4;
    REQUIRE(line3 == line4);
  }
}
