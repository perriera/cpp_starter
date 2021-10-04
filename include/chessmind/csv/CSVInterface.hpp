#ifndef _CSVINTERFACE_HPP
#define _CSVINTERFACE_HPP

#include <extras/interfaces.hpp>
#include <iostream>

//
// CSVInterface
// Define the interface to CSV formatted files
//

interface CSVInterface {
  virtual std::string csv_out() const pure;
  virtual void csv_in(const std::string &csv) pure;
};

#endif // _CSVINTERFACE_HPP
