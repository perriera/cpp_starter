/**
 * @brief the "MIT/X Consortium License", (adapted for EXPARX.COM)
 *
 * Copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 * Permission is hereby  granted,  free of charge,  to  any  person
 * obtaining a copy of this software and  associated  documentation
 * files   (the  "Software"),  to deal  in   the  Software  without
 * restriction, including  without  limitation the rights  to  use,
 * copy,  modify, merge,  publish,  distribute,  sublicense, and/or
 * sell copies of the  Software, and to permit persons  to whom the
 * Software  is  furnished to  do  so,  subject  to  the  following
 * conditions:
 *
 * (See LICENSE.md for complete details)
 *
 */

#include <extras_cpp/game/clazz.hpp>
#include <extras/interfaces.hpp>
#include <iostream>

using namespace std;
using namespace extras;

namespace extras {
  namespace cpp {
    namespace game {

      void ChessGame::moves() const {}

      bool ChessGame::exists() const
      {
        return true;
      }

      bool ChessGame::piece(int, int) const
      {
        return true;
      }

      bool ChessGame::zone(int row, int col) const
      {
        game::EndOfGameReachedException::assertion(
          row, col, "sample", __INFO__);
        return row == _x && col == _y;
      }

    }
  }
}