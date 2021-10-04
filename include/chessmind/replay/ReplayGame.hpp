#ifndef _REPLAYGAME_HPP
#define _REPLAYGAME_HPP

//
// GIVEN we might want to replay a game
// WHEN we combine ChessBoard with a replay interface
// THEN we can replay a ChessGame instance
//

#include <extras/interfaces.hpp>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

interface ReplayGameInterface {
  virtual void play() pure;
  virtual void forward() pure;
  virtual void reverse() pure;
};

class ReplayGame implements ReplayGameInterface {
public:
  virtual void play();
  virtual void forward();
  virtual void reverse();
};

#endif // _REPLAYGAME_HPP