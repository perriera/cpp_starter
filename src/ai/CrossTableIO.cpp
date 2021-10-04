#include "../include/chessmind/ai/CrossTableIO.hpp"
#include "../include/chessmind/ai/CrossTableInterface.hpp"
#include "extras/ansi_colors.hpp"
#include "extras/crc16_support.hpp"
#include "extras/crc64_support.hpp"
#include "extras/string_support.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;
using namespace extras;

ostream &operator<<(ostream &out, const CrossTableIO &) { return out; }

istream &operator>>(istream &in, CrossTableIO &obj)
{
  string header;
  getline(in, header);
  if (header.size() == 0)
    throw CrossTableException("no header, expected format");
  obj._start = 0;
  in.seekg(0, in.end);
  obj._end = in.tellg();
  obj._location = 0;
  obj._in = &in;
  return in;
}

void CrossTableIO::train(const StatLines &)
{
  throw CrossTableException("n/a");
}

int CrossTableIO::size() const { throw CrossTableException("n/a"); }

CrossTableLine CrossTableIO::predict(const FENLine &fenLine)
{

  auto start = this->_start;
  auto end = this->_end;
  auto offset = (this->_average_size / 2);
  auto fenLineKey = FENLine::makeKey(fenLine);
  int search_count = 0;
  while (!((end - start) < this->_average_size)) {
    auto loc = (end - start) / 2;
    loc += offset;
    this->_in->seekg(start + loc, this->_in->beg);
    string text;
    getline(*this->_in, text);
    if (this->_in->tellg() == -1)
      throw CrossTableException("the stream died");
    //
    CrossTableLine cursor;
    *this->_in >> cursor;
    //
    if (this->_verbose) {
      cout << blue << cursor << endl;
      cout << magenta << hex << fenLineKey << ' ' << yellow << hex
           << cursor.key();
      cout << red << ' ' << dec << start << ' ' << loc << ' ' << end;
      cout << green << ' ' << dec << this->_in->tellg() << endl;
    }
    if (cursor.key() < fenLineKey) {
      if (this->_verbose)
        cout << "up"
             << ": " << ++search_count << endl;
      start = start + loc;
    } else if (cursor.key() > fenLineKey) {
      if (this->_verbose)
        cout << "down"
             << ": " << ++search_count << endl;
      end = start + loc;
    } else {
      if (this->_verbose)
        cout << "locked"
             << ": " << ++search_count << endl;
      return cursor;
    }
  }
  stringstream ss;
  ss << "key not found: " << hex << fenLineKey << ": " << ++search_count;
  if (this->_verbose)
    cout << ss.str() << endl;
  throw CrossTableException(ss.str());
}
