#include "../include/cpp_starter/game/ChessSquare.hpp"
#include "../include/cpp_starter/game/ChessExceptions.hpp"
#include "../include/cpp_starter/game/ChessPosition.hpp"
#include "extras/string_support.hpp"
#include <iostream>

using namespace std;

void ChessCoordinateException::assertation(const ChessCoordinate& coordinate) {
  char value = coordinate._value;
  int offset = coordinate._assertions_off ? 1 : 0;
  if (value < coordinate._from - offset || value > coordinate._to + offset) {
    throw ChessCoordinateException("OutOfBounds: " + value);
  }
}

ChessCoordinate::ChessCoordinate(char from, char to, char value, int direction)
  : _from(from), _to(to), _value(value), _direction(direction) {
  ChessCoordinateException::assertation(*this);
}

ChessCoordinate ChessCoordinate::operator++() {
  _value += _direction;
  ChessCoordinateException::assertation(*this);
  return *this;
}

ChessCoordinate ChessCoordinate::operator--() {
  _value -= _direction;
  ChessCoordinateException::assertation(*this);
  return *this;
}

ChessCoordinate ChessCoordinate::operator+=(int value) {
  _value += value * _direction;
  ChessCoordinateException::assertation(*this);
  return *this;
}

ChessCoordinate ChessCoordinate::operator-=(int value) {
  _value -= value * _direction;
  ChessCoordinateException::assertation(*this);
  return *this;
}

ChessCoordinate ChessCoordinate::operator+(int value) {
  ChessCoordinate res;
  res = *this;
  res += value;
  ChessCoordinateException::assertation(*this);
  return res;
}

ChessCoordinate ChessCoordinate::operator-(int value) {
  ChessCoordinate res;
  res = *this;
  res -= value;
  ChessCoordinateException::assertation(*this);
  return res;
}
