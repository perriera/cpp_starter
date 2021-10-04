#ifndef _DATAMASKING_HPP
#define _DATAMASKING_HPP

#include "../include/cpp_starter/stat/StatWriter.hpp"
#include "../masking/MaskedLine.hpp"
#include <extras/interfaces.hpp>
#include <iostream>
#include <vector>

//
// DataMaskInterface
// Encapsulates all behaviour unique to a PGN parser
//

interface DataMaskInterface {
  virtual void mask(const StatLines& statLines) = 0;
};

class DataMask implements DataMaskInterface {
  friend std::ostream& operator<<(std::ostream& out, const DataMask& obj);
  friend std::istream& operator>>(std::istream& in, DataMask& obj);

private:
  MaskedLines _maskedLines;

public:
  const MaskedLines& lines() { return _maskedLines; }
  virtual void mask(const StatLines& statLines);
};

#endif // _DATAMASKING_HPP
