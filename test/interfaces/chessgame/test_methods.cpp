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

#include <iostream>
#include <extras_cpp/game/clazz.hpp>

#include "../../vendor/catch.hpp"

using namespace std;
using namespace extras::cpp;

SCENARIO("test game::methods", "[JIRA-1440]")
{
    /**
     *    construct an object
     */

    game::ChessGame game(1, 2);
    game::Interface& i = game;

    /**
     *    repeat same tests from mold
     */

    i.moves();
    REQUIRE(i.exists() == true);
    REQUIRE(i.piece(1, 2) == true);
    REQUIRE_THROWS_AS(
        i.zone(0, 0), game::EndOfGameReachedException);
    REQUIRE(i.zone(1, 0) == false);
    REQUIRE(i.zone(0, 1) == false);

}

