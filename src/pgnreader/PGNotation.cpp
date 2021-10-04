#include "../include/cpp_starter/pgn/PGNotation.hpp"
#include "../include/cpp_starter/pgn/notation/Draw.hpp"
#include "../include/cpp_starter/pgn/notation/GameOver.hpp"
#include "../include/cpp_starter/pgn/notation/Type1.hpp"
#include "../include/cpp_starter/pgn/notation/Type2.hpp"
#include "../include/cpp_starter/pgn/notation/Type3.hpp"
#include "../include/cpp_starter/pgn/notation/Type4.hpp"
#include "../include/cpp_starter/pgn/notation/Type5.hpp"
#include "../include/cpp_starter/pgn/notation/Type6.hpp"
#include "../include/cpp_starter/pgn/notation/TypeCastle.hpp"
#include "../include/cpp_starter/pgn/notation/TypePromote.hpp"
#include "extras/string_support.hpp"
#include <ctype.h>
#include <iostream>

using namespace std;

ostream& operator<<(ostream& out, const PGNotation&) {
  // if (obj._piece!=-1)
  //     out << obj._piece;
  // out << obj._san;
  return out;
}

istream& operator>>(istream& in, PGNotation& obj) {
  string word;
  in >> word;
  bool kingCheck = (word.find_last_of('+') != string::npos);
  if (kingCheck) {
    word = word.substr(0, word.length() - 1);
    // cout << "King check ignored (for now)" << endl;
  }
  bool checkMake = (word.find_last_of('#') != string::npos);
  if (checkMake) {
    word = word.substr(0, word.length() - 1);
    cout << "Check mate" << endl;
  }
  bool exclamation_Mark = (word.find_last_of('!') != string::npos);
  if (exclamation_Mark) {
    word = word.substr(0, word.length() - 1);
    cout << "Check mate" << endl;
  }
  if (word == "1/2-1/2")
    obj._proxy = new PGNotationTypeDraw(word);
  else if (word == "1-0" || word == "0-1")
    obj._proxy = new PGNotationTypeGameOver(word);
  else if (word == "O-O" || word == "O-O-O")
    obj._proxy = new PGNotationTypeCastle(word);
  else
    switch (word.size()) {
    case 2:
      obj._proxy = new PGNotationType1(word);
      break;
    case 3:
      obj._proxy = new PGNotationType2(word);
      break;
    case 4: {
      if (word[2] == '=')
        obj._proxy = new PGNotationTypePromote(word);
      else if (word[1] == 'x')
        obj._proxy = new PGNotationType3(word);
      else
        obj._proxy = new PGNotationType4(word);
    } break;
    case 5: {
      switch (word[2]) {
      case 'x':
        obj._proxy = new PGNotationType5(word);
        break;
      case '=':
        obj._proxy = new PGNotationTypePromote(word);
        break;
      default:
        obj._proxy = new PGNotationType6(word);
        break;
      }
    } break;
    default:
      break;
    }
  return in;
}
