#ifndef _CHESSSQUARE_HPP
#define _CHESSSQUARE_HPP

#include <extras/interfaces.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>

abstract class ChessCoordinate {
  friend class ChessCoordinateException;
  friend inline std::ostream &operator<<(std::ostream &out,
                                         const ChessCoordinate &obj) {
    out << obj._value;
    return out;
  }
  friend inline std::istream &operator>>(std::istream &in,
                                         ChessCoordinate &obj) {
    in >> obj._value;
    return in;
  }
  friend inline bool operator==(const ChessCoordinate &a,
                                const ChessCoordinate &b) {
    return a._value == b._value;
  }
  friend inline bool operator==(const ChessCoordinate &a, char b) {
    return a._value == b;
  }
  friend inline bool operator>(const ChessCoordinate &a,
                               const ChessCoordinate &b) {
    return a._value * a._direction > b._value * a._direction;
  }
  friend inline bool operator>=(const ChessCoordinate &a, char b) {
    return a._value * a._direction >= b * a._direction;
  }
  friend inline bool operator<(const ChessCoordinate &a,
                               const ChessCoordinate &b) {
    return a._value * a._direction < b._value * a._direction;
  }
  friend inline bool operator<=(const ChessCoordinate &a, char b) {
    return a._value * a._direction <= b * a._direction;
  }
  friend inline bool operator!=(const ChessCoordinate &a,
                                const ChessCoordinate &b) {
    return !(a == b);
  }
  friend inline bool operator!=(const ChessCoordinate &a, char b) {
    return !(a == b);
  }

private:
  char _from;
  char _to;
  char _value;
  int _direction;
  bool _assertions_off = false;

public:
  ChessCoordinate(){};
  ChessCoordinate(char from, char to, char value, int direction);
  ChessCoordinate operator++();
  ChessCoordinate operator--();
  ChessCoordinate operator+=(int value);
  ChessCoordinate operator-=(int value);
  ChessCoordinate operator+(int value);
  ChessCoordinate operator-(int value);
  virtual operator char() const { return _value; }
  void assertions_off(bool true_or_false) { _assertions_off = true_or_false; }
  char end() {
    assertions_off(true);
    return _to + 1;
  }
  char begin() {
    assertions_off(true);
    return _from - 1;
  }
};

concrete struct ChessCol extends ChessCoordinate {
  ChessCol(const std::string &position)
      : ChessCoordinate('a', 'h', position[0], 1) {}
  ChessCol(char value) : ChessCoordinate('a', 'h', value, 1) {}
  ChessCol() : ChessCoordinate('a', 'h', 'a', 1) {}
  char lbegin() { return 'a'; }
  char lend() { return 'h'; }
};

abstract struct ChessRow extends ChessCoordinate {
  ChessRow(const std::string &position, int direction)
      : ChessCoordinate('1', '8', position[1], direction) {}
  ChessRow(char value, int direction = 1)
      : ChessCoordinate('1', '8', value, direction) {}
  ChessRow() : ChessCoordinate('1', '8', '1', 1) {}
};

concrete struct BlackRow extends ChessRow {
  BlackRow(const std::string &position) : ChessRow(position, -1) {}
  BlackRow(char value) : ChessRow(value, -1) {}
  char lbegin() { return '8'; }
  char lend() { return '1'; }
};

concrete struct WhiteRow extends ChessRow {
  WhiteRow(const std::string &position) : ChessRow(position, 1) {}
  WhiteRow(char value) : ChessRow(value, 1) {}
  char lbegin() { return '1'; }
  char lend() { return '8'; }
};

//
// ChessPositionException
// Governs all rules on ChessPosition
//

struct ChessCoordinateException : public std::exception {
  std::string _msg;

public:
  ChessCoordinateException(const std::string &msg) : _msg(msg){};
  const char *what() const throw() { return _msg.c_str(); };
  static void assertation(const ChessCoordinate &coordinate);
  inline operator const std::string &() const { return _msg; }
};

#endif // _CHESSSQUARE_HPP
