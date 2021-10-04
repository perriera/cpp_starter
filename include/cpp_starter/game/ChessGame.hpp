#ifndef _CHESSGAME_HPP
#define _CHESSGAME_HPP

#include <iostream>
#include <extras/interfaces.hpp>
#include <extras/exceptions.hpp>
#include "../include/cpp_starter/game/ChessMoves.hpp"
#include "../include/cpp_starter/game/ChessBoard.hpp"

/**
 * @brief ChessGameInterface
 *
 */
interface ChessGameInterface
{

    /**
     * @brief moves()
     * @return all the chess moves of the given chess game
     */
    virtual const ChessMoves& moves() const pure;
    virtual const ChessBoard& board() const pure;
    virtual const ChessBoard& next() pure;
    virtual const ChessBoard& previous() pure;

};

/**
 * @brief EndOfGameReachedException
 *
 */

concrete class EndOfGameReachedException
extends extras::AbstractCustomException {
public:
    EndOfGameReachedException(
        const std::string& msg,
        const extras::WhereAmI& whereAmI)
        : AbstractCustomException(msg.c_str(),
            whereAmI._file.c_str(),
            whereAmI._func.c_str(), whereAmI._line) {}
    static void assertion(
        int sizePGN, int sizeFEN,
        const std::string& msg,
        const extras::WhereAmI& ref);
};

/**
 * @brief EndOfGameReachedException
 *
 */

concrete class StartOfGameReachedException
extends extras::AbstractCustomException {
public:
    StartOfGameReachedException(
        const std::string& msg,
        const extras::WhereAmI& whereAmI)
        : AbstractCustomException(msg.c_str(),
            whereAmI._file.c_str(),
            whereAmI._func.c_str(), whereAmI._line) {}
    static void assertion(
        int sizePGN, int sizeFEN,
        const std::string& msg,
        const extras::WhereAmI& ref);
};

#endif // _CHESSGAME_HPP
