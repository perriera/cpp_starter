/**
 * @brief The MIT License (MIT)
 * @copyright © 2023 Perry Anderson, (perry@exparx.ca)
 * @ref https://github.com/perriera
 *
 * Permission  is  hereby  granted, free  of  charge, to  any person  obtaining
 * a copy of this software and associated documentation files (the “Software”),
 * to deal in the Software  without restriction,  including  without limitation
 * the rights to  use,  copy,  modify,  merge, publish, distribute, sublicense,
 * and/or sell  copies of the  Software,  and  to  permit  persons  to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice  and this permission  notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS  PROVIDED “AS IS”,  WITHOUT WARRANTY  OF ANY  KIND,  EXPRESS
 * OR IMPLIED,  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR  PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR  COPYRIGHT HOLDERS BE  LIABLE FOR ANY  CLAIM,  DAMAGES  OR  OTHER
 * LIABILITY,  WHETHER IN  AN ACTION  OF CONTRACT,  TORT OR  OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#include <iostream>
#include <extras_cpp/game/interface.hpp>
#include <extras/docking/DockIt.hpp>

#include "../../test/vendor/catch.hpp"
#include "../../test/vendor/fakeit.hpp"

using namespace extras;
using namespace extras::cpp;
using namespace fakeit;

/**
 *    Mold<cpp::cpp::game::Interface> dock;
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
SCENARIO("Mold cpp::game::Interface", "[cpp::game::Interface]") {

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
        return false;
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

     /**
      * @brief mold the interface
      *
      */
    test(i);

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

