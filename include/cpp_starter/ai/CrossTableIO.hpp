#ifndef _CROSSTABLEIO_HPP
#define _CROSSTABLEIO_HPP

#include "../include/cpp_starter/ai/CrossTableInterface.hpp"
#include "../include/cpp_starter/ai/CrossTableLine.hpp"
#include "../include/cpp_starter/csv/CSVInterface.hpp"
#include "../include/cpp_starter/stat/StatLine.hpp"
#include "extras/crc64_support.hpp"
#include <extras/interfaces.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>

/**
 * Sum numbers in a vector.
 *
 * @param values Container whose values are summed.
 * @return sum of `values`, or 0.0 if `values` is empty.
 */

typedef int CrossTableIOLocation;

class CrossTableIO implements CrossTableMapInterface {
  friend std::ostream& operator<<(std::ostream& out, const CrossTableIO& obj);
  friend std::istream& operator>>(std::istream& in, CrossTableIO& obj);

  std::istream* _in;
  CrossTableIOLocation _start;
  CrossTableIOLocation _location;
  CrossTableIOLocation _end;
  int _average_size = 63;
  bool _verbose = false;

public:
  virtual void train(const StatLines& statLines);
  virtual CrossTableLine predict(const FENLine& line);
  virtual int size() const;
  virtual void verbose(bool on_or_off) { _verbose = on_or_off; };
};

#endif // _CROSSTABLEIO_HPP
