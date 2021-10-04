#ifndef _BLOCK_HPP
#define _BLOCK_HPP

#include <extras/interfaces.hpp>
#include <iostream>

//
// CSVInterface
// Define the interface to CSV formatted files
//

interface BlockInterface {
  virtual std::string csv_out() const pure;
  virtual void csv_in(const std::string &csv) pure;
};

#endif // _BLOCK_HPP
