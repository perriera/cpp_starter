/**
 * @file ChessGame.hpp
 * @author Perry Anderson, (perry@exparx.ca)
 * @brief Sample Header file
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXTRAS_CPP_CHESSGAME_INTERFACE_HPP
#define _EXTRAS_CPP_CHESSGAME_INTERFACE_HPP

 /**
  * @brief The MIT License (MIT)
  * @copyright © 2023 Perry Anderson, (perry@exparx.ca)
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
#include <extras/interfaces.hpp>

namespace extras {
    namespace cpp {
        namespace game {

            /**
             * @brief game::Interface
             *
             */
            interface Interface
            {

                /**
                 * @brief moves()
                 * @return all the chess moves of the given chess game
                 */
                virtual void moves() const pure;
                virtual bool exists() const pure;
                virtual bool piece(int row, int col) const pure;
                virtual bool zone(int row, int col) const pure;

            };

            /**
             * @brief EndOfGameReachedException
             *
             */
            abstract class Exception
                extends extras::AbstractCustomException {
            public:
                Exception(
                    const std::string& msg,
                    const extras::WhereAmI& whereAmI)
                    : AbstractCustomException(msg.c_str(),
                        whereAmI._file.c_str(),
                        whereAmI._func.c_str(), whereAmI._line) {}
            };

            /**
             * @brief EndOfGameReachedException
             *
             */
            concrete class EndOfGameReachedException
                extends Exception {
            public:
                EndOfGameReachedException(
                    const std::string& msg,
                    const extras::WhereAmI& whereAmI)
                    : Exception(msg.c_str(), whereAmI) {}
                static void assertion(
                    int sizePGN, int sizeFEN,
                    const std::string& msg,
                    const extras::WhereAmI& ref);
            };

        }
    } // end namespace 
}

#endif // _EXTRAS_CPP_CHESSGAME_INTERFACE_HPP
