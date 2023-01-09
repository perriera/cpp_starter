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
#include <extras_cpp/game/interface.hpp>

#include "../../vendor/catch.hpp"

using namespace std;
using namespace extras;
using namespace extras::cpp;

SCENARIO("test game::Interface assertions", "[JIRA-1440]") {

    /**
     *    test all the assertions
     */
    REQUIRE_THROWS_AS(
        game::EndOfGameReachedException::assertion(
            0, 0, "sample", __INFO__), game::EndOfGameReachedException);

}
