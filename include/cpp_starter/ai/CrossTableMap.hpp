#ifndef _CROSSTABLEMAP_HPP
#define _CROSSTABLEMAP_HPP

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

//
// CrossTable
// CrossTableInterface implementation
//

/**
 * Sum numbers in a vector.
 *
 * @param values Container whose values are summed.
 * @return sum of `values`, or 0.0 if `values` is empty.
 */

class CrossTableMap implements CrossTableMapInterface {
  friend std::ostream& operator<<(std::ostream& out, const CrossTableMap& obj);
  friend std::istream& operator>>(std::istream& in, CrossTableMap& obj);
  friend inline bool operator==(const CrossTableMap& a,
    const CrossTableMap& b) {
    return a._map == b._map;
  }
  friend inline bool operator!=(const CrossTableMap& a,
    const CrossTableMap& b) {
    return !(a == b);
  }

  CrossTableLineMap _map;
  bool _verbose = false;

  void insert(const StatLine& line);

public:
  virtual void train(const StatLines& statLines);
  virtual CrossTableLine predict(const FENLine& line);
  virtual int size() const;
  virtual void verbose(bool on_or_off) { _verbose = on_or_off; };
};

/**
 * @brief throws when a FENLine pattern isn't recognized
 *
 */
class CrossTableMapException : public std::exception {
  std::string _msg;

public:
  CrossTableMapException(const FENLine& fenLine) {
    _msg = fenLine.operator std::string();
  }
  virtual char const* what() const noexcept { return _msg.c_str(); }
  static void assertation(const CrossTableLineMap& map,
    const CrossTableLineKey& key, const FENLine& fenLine);
};

#endif // _CROSSTABLEMAP_HPP
