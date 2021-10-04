#ifndef _FENREADER_HPP
#define _FENREADER_HPP

#include <iostream>
#include <vector>
#include "FENLine.hpp"

/**
 *
 *
 */


 //
 // https://www.cs.kent.ac.uk/people/staff/djb/pgn-extract/
 // for f in pgn/*; do ./pgn-extract -Wepd "$f" "pgn/$(basename "${f%.*}").PGN" -o"fen/$(basename "${f%.*}").FEN"; done
 // for f in pgn/*; do ./pgn-extract -Wepd "$f" "pgn/$(basename "${f%.*}").pgn" -o"fen/$(basename "${f%.*}").fen"; done
 //
 //

 //
 // FENReader
 // Encapsulates all behaviour unique to a PGN parser
 //

interface FENReaderInterface
{
  virtual const FENLineListWithParameters& lines() const pure;
};

concrete class FENReader implements FENReaderInterface
{
  friend std::ostream& operator<<(std::ostream& out, const FENReader& obj);
  friend std::istream& operator>>(std::istream& in, FENReader& obj);

private:
  FENLineListWithParameters _lines;

public:
  const FENLineListWithParameters& lines() const { return _lines; }
};

#endif// _FENREADER_HPP
