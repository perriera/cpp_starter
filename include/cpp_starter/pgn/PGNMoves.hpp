#ifndef _PGNMOVES_HPP
#define _PGNMOVES_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "../include/cpp_starter/game/ChessPiece.hpp"
#include "../include/cpp_starter/fen/FENLine.hpp"
#include "../include/cpp_starter/san/SANInterface.hpp"


/**
 * @brief interface PGNGameInterface
 */

interface PGNMoveInterface {
    virtual const std::string& blackSAN() const pure;
    virtual const std::string& whiteSAN() const pure;
    virtual const FENLine& blackFEN() const pure;
    virtual const FENLine& whiteFEN() const pure;
    virtual void blackFEN(const FENLine& fenLine)  pure;
    virtual void whiteFEN(const FENLine& fenLine)  pure;
};

//
// ChessMove
// Encapsulates all behaviour unique to a chess move
//

concrete class PGNMove implements PGNMoveInterface
{

    friend std::istream& operator>>(std::istream& in, PGNMove& obj);
    friend std::ostream& operator<<(std::ostream& out, const PGNMove& obj);
    friend inline bool operator==(const PGNMove& a, const PGNMove& b)
    {
        return a._white == b._white && a._black == b._black;
    }
    friend inline bool operator!=(const PGNMove& a, const PGNMove& b)
    {
        return !(a == b);
    }

private:
    std::string _white;
    std::string _black;
    FENLine _whiteFEN;
    FENLine _blackFEN;

public:
    PGNMove() {};
    PGNMove(const std::string& white, const std::string& black)
        : _white(white), _black(black) {}
    virtual const std::string& blackSAN() const override { return _black; };
    virtual const std::string& whiteSAN() const override { return _white; };
    virtual const FENLine& blackFEN() const override { return _blackFEN; };
    virtual const FENLine& whiteFEN() const override { return _whiteFEN; };
    virtual void blackFEN(const FENLine& fenLine)  override { _blackFEN = fenLine; };
    virtual void whiteFEN(const FENLine& fenLine)  override { _whiteFEN = fenLine; };
};

typedef std::vector<PGNMove> PGNMoves;

std::ostream& operator<<(std::ostream& out, const PGNMoves& obj);
std::istream& operator>>(std::istream& in, PGNMoves& obj);

/**
 * @brief PGNMovesMismatchException
 *
 */

concrete class PGNMovesMismatchException extends extras::AbstractCustomException {
public:
    PGNMovesMismatchException(const extras::WhereAmI& whereAmI)
        : AbstractCustomException("Moves do not match", whereAmI._file.c_str(),
            whereAmI._func.c_str(), whereAmI._line) {}
    static void assertion(const PGNMoves& a, const PGNMoves& b, const extras::WhereAmI& ref);
};


#endif // _PGNMOVES_HPP
