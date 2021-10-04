#ifndef _PGNSYMBOLS_HPP
#define _PGNSYMBOLS_HPP

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../include/chessmind/game/ChessPosition.hpp"
#include <extras/interfaces.hpp>

//
// SymbolAtInterface
// Encapsulates all behaviour unique to a chess symbols
//

interface SymbolAtInterface {
  virtual char symbolAt(char col, char row) const = 0;
  virtual char symbolAt(const ChessPosition &pos) const = 0;
};

#endif // _PGNSYMBOLS_HPP
