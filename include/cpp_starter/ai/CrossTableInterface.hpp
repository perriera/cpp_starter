#ifndef _CROSSTABLEINTERFACE_HPP
#define _CROSSTABLEINTERFACE_HPP

#include "../include/cpp_starter/ai/CrossTableLine.hpp"
#include <extras/interfaces.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>

//
// CrossTableInterface
// Encapsulates all behaviour CrossTableInterface
//

interface CrossTableMapInterface {
  virtual void train(const StatLines& statLines) pure;
  virtual CrossTableLine predict(const FENLine& line) pure;
  virtual int size() const pure;
  virtual void verbose(bool on_or_off) pure;
};

/**
 * @brief throws when a FENLine pattern isn't recognized
 *
 */
class CrossTableException : public std::exception {
  std::string _msg;

public:
  CrossTableException(const std::string& msg) : _msg(msg) {};
  virtual char const* what() const noexcept { return _msg.c_str(); }
};

#endif // _CROSSTABLEINTERFACE_HPP
