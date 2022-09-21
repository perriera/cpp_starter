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
#include <extras/docking/DockIt.hpp>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace extras::cpp;
using namespace fakeit;

/**
 *    Mold<cpp::ChessGameInterface> dock;
 *
 *    (aka. mold the cpp::ChessGame interface to this dock)
 *
 *    this is a very simple dock/mold for the purpose
 *    of showing how parameters can be passed to methods
 *    and how dock/molds can be used in their simplist
 *    form and execution.
 *
 *    for a more complete examples of dock/molds see
 *    the (perrier) extras framework
 *
 */
SCENARIO("Mold ChessGameInterface", "[JIRA-1440]") {

    /**
     *    Steps 1. Mold the Interface to a dock
     *          2. dock methods of interest
     *          3. supply a reference to that dock
     *
     */

    Mold<cpp::game::Interface> dock;
    When(Method(dock, moves)).Return();
    When(Method(dock, exists)).AlwaysDo([]() { return true; });
    When(Method(dock, piece)).AlwaysDo([](int, int) { return true; });
    int _x = 0, _y = 0;
    When(Method(dock, zone)).AlwaysDo([&_x, &_y](int row, int col) {
        return row == _x && col == _y;
        });
    cpp::game::Interface& i = dock.get();

    /**
     *    Steps 4. in this step carry out at least one typical
     *             scenario that the methods would be engaged in
     *             to accomplish a given purpose (of the interface)
     *
     *             in this way you can make refinements to
     *             the interface's methods until you are
     *             satisfied with each method signature
     *
     *             remember, the primary benefit of dock/molds
     *             are that you were able to determine just what
     *             each method was needed and what parameters
     *             that were *actually* required *without*
     *             writing any implementation code.
     *
     *             your appreciation for doing things this way
     *             comes with practice, (aka. practice makes
     *             perfect). the appreciation for this method
     *             really can only be realized in production
     *             environments, (aka. doing thing this way
     *             really can't be passed from teacher to
     *             student in school/university settings)
     *             that is, short of a thesis.
     *
     *               " When the student is ready,
     *                   the teacher will appear. "
     *                       -- The Buddha
     *
     *             in the beginning programmers write code,
     *             but in the end architects write designs.
     *
     */

    i.moves();
    REQUIRE(i.exists() == true);
    REQUIRE(i.piece(1, 2) == true);
    REQUIRE(i.zone(0, 0) == true);
    REQUIRE(i.zone(1, 0) == false);
    REQUIRE(i.zone(0, 1) == false);

    /**
     *     Steps 5. Verify all methods intended to be called
     *              were 'docked' (at least once)
     *
     */
    Verify(Method(dock, exists));
    Verify(Method(dock, moves));
    Verify(Method(dock, piece));
    Verify(Method(dock, zone));

}

