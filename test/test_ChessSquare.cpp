#include <fstream>
#include <iostream> // std::cout
#include <sstream>  // std::stringstream
#include <string>   // std::string

#include "../include/chessmind/game/ChessExceptions.hpp"
#include "../include/chessmind/game/ChessSquare.hpp"
#include "catch.hpp"
#include "extras/string_support.hpp"

using namespace std;

SCENARIO("Verify ChessSquare can do (PGN Type1) 'e2'", "[ChessSquare]") {

  GIVEN("ChessCol constructor") {
    ChessCol pos("e1");
    REQUIRE(pos == 'e');
    cout << pos << endl;
    REQUIRE_THROWS_AS(ChessCol("?1"), ChessCoordinateException);
    REQUIRE_THROWS_AS(ChessCol("i0"), ChessCoordinateException);
    ++pos;
    cout << pos << endl;
    REQUIRE(pos == 'f');
    --pos;
    cout << pos << endl;
    REQUIRE(pos == 'e');
    pos += 2;
    cout << pos << endl;
    REQUIRE(pos == 'g');
    pos -= 2;
    cout << pos << endl;
    REQUIRE(pos == 'e');
    auto addition = pos + 2;
    REQUIRE(addition == 'g');
    REQUIRE(addition != pos);
    REQUIRE(addition > pos);
    auto subtraction = pos - 2;
    REQUIRE(subtraction < pos);
    REQUIRE(subtraction == 'c');
    try {
      ChessCol sample("a1");
      --sample;
      FAIL('failed');
    } catch (ChessCoordinateException &ex) {
      SUCCEED('passed');
    }
    try {
      ChessCol sample("a1");
      sample -= 2;
      FAIL('failed');
    } catch (ChessCoordinateException &ex) {
      SUCCEED('passed');
    }
    try {
      ChessCol sample("h1");
      ++sample;
      FAIL('failed');
    } catch (ChessCoordinateException &ex) {
      SUCCEED('passed');
    }
    try {
      ChessCol sample("h1");
      sample += 2;
      FAIL('failed');
    } catch (ChessCoordinateException &ex) {
      SUCCEED('passed');
    }
  }
  GIVEN("ChessCol range testing") {
    for (ChessCol col = 'a'; col < col.end(); ++col)
      cout << col << flush;
    cout << endl;
    for (ChessCol col = 'h'; col > col.begin(); --col)
      cout << col << flush;
    cout << endl;
  }
  GIVEN("ChessCol stream testing") {
    string columns = "abcdabcdabcdabcd";
    stringstream ss;
    ss << columns;
    int cnt = 0;
    while (true) {
      ChessCol cc;
      ss >> cc;
      if (!ss.good())
        break;
      cout << cc << flush;
      cnt++;
    }
    REQUIRE(cnt == columns.size());
  }
  GIVEN("ChessRow stream testing") {
    string columns = "133564535242432";
    stringstream ss;
    ss << columns;
    int cnt = 0;
    while (true) {
      ChessRow cc;
      ss >> cc;
      if (!ss.good())
        break;
      cout << cc << flush;
      cnt++;
    }
    REQUIRE(cnt == columns.size());
  }
  GIVEN("WhiteRow constructor") {
    WhiteRow pos("e1");
    REQUIRE(pos == '1');
    cout << pos << endl;
    REQUIRE_THROWS_AS(BlackRow("e9"), ChessCoordinateException);
    REQUIRE_THROWS_AS(BlackRow("e0"), ChessCoordinateException);
    ++pos;
    cout << pos << endl;
    REQUIRE(pos == '2');
    --pos;
    cout << pos << endl;
    REQUIRE(pos == '1');
    pos += 2;
    cout << pos << endl;
    REQUIRE(pos == '3');
    pos -= 2;
    cout << pos << endl;
    REQUIRE(pos == '1');
    auto addition = pos + 2;
    REQUIRE(addition == '3');
    REQUIRE(addition != pos);
    REQUIRE(addition > pos);
    auto subtraction = addition - 2;
    REQUIRE(subtraction < addition);
    REQUIRE(subtraction == '1');
    try {
      WhiteRow sample("a1");
      --sample;
      FAIL('failed');
    } catch (ChessCoordinateException &ex) {
      SUCCEED('passed');
    }
    try {
      WhiteRow sample("a1");
      sample -= 2;
      FAIL('failed');
    } catch (ChessCoordinateException &ex) {
      SUCCEED('passed');
    }
    try {
      WhiteRow sample("a8");
      ++sample;
      FAIL('failed');
    } catch (ChessCoordinateException &ex) {
      SUCCEED('passed');
    }
    try {
      WhiteRow sample("a8");
      sample += 2;
      FAIL('failed');
    } catch (ChessCoordinateException &ex) {
      SUCCEED('passed');
    }
  }
  GIVEN("WhiteRow range testing") {
    for (WhiteRow row = row.lbegin(); row < row.end(); ++row)
      cout << row << flush;
    cout << endl;
    for (WhiteRow row = '8'; row > row.begin(); --row)
      cout << row << flush;
    cout << endl;
  }
  GIVEN("BlackRow constructor") {
    BlackRow pos("e8");
    REQUIRE(pos == '8');
    cout << pos << endl;
    REQUIRE_THROWS_AS(BlackRow("e9"), ChessCoordinateException);
    REQUIRE_THROWS_AS(BlackRow("e0"), ChessCoordinateException);
    ++pos;
    cout << pos << endl;
    REQUIRE(pos == '7');
    --pos;
    cout << pos << endl;
    REQUIRE(pos == '8');
    pos += 2;
    cout << pos << endl;
    REQUIRE(pos == '6');
    pos -= 2;
    cout << pos << endl;
    REQUIRE(pos == '8');
    auto addition = pos + 2;
    REQUIRE(addition == '6');
    REQUIRE(addition != pos);
    REQUIRE(addition > pos);
    auto subtraction = addition - 2;
    REQUIRE(subtraction < addition);
    REQUIRE(subtraction == '8');
    try {
      BlackRow sample("a8");
      --sample;
      FAIL('failed');
    } catch (ChessCoordinateException &ex) {
      SUCCEED('passed');
    }
    try {
      BlackRow sample("a8");
      sample -= 2;
      FAIL('failed');
    } catch (ChessCoordinateException &ex) {
      SUCCEED('passed');
    }
    try {
      BlackRow sample("a1");
      ++sample;
      FAIL('failed');
    } catch (ChessCoordinateException &ex) {
      SUCCEED('passed');
    }
    try {
      BlackRow sample("a1");
      sample += 2;
      FAIL('failed');
    } catch (ChessCoordinateException &ex) {
      SUCCEED('passed');
    }
  }
  GIVEN("BlackRow range testing") {
    for (BlackRow row = '8'; row > row.begin(); ++row)
      cout << row << flush;
    cout << endl;
    for (BlackRow row = '1'; row < row.end(); --row)
      cout << row << flush;
    cout << endl;
  }
}
