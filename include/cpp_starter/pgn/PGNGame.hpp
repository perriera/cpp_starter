#ifndef _PGNGAME_HPP
#define _PGNGAME_HPP

#include <iostream>
#include <extras/exceptions.hpp>
#include "../include/cpp_starter/fen/FENLine.hpp"
#include "../include/cpp_starter/pgn/PGNParameters.hpp"
#include "../include/cpp_starter/pgn/PGNMoves.hpp"
#include "../include/cpp_starter/game/ChessPiece.hpp"
#include "../include/cpp_starter/game/ChessGame.hpp"
#include "../include/cpp_starter/game/ChessBoard.hpp"

/**
 * @brief interface PGNGameInterface
 */

interface PGNGameInterface extends ChessGameInterface {
    virtual const PGNParameters& parameters() const pure;
    virtual const std::string& FENparameters() const pure;
    virtual void FENparameters(const std::string& fenParameters) pure;
    virtual const std::string& FENreport() const pure;
    virtual void FENreport(const std::string& fenReport) pure;
    virtual PGNMoves pgnmoves() const pure;
    virtual ChessBoard playGameUntil(const ChessBoard& board, const std::string& move) pure;
    virtual ChessBoard playGameEnd(const ChessBoard& board) pure;
};

/**
 * @brief class PGNGame
 */

concrete class PGNGame implements PGNGameInterface
{
    friend std::ostream& operator<<(std::ostream& out, const PGNGame& obj);
    friend std::istream& operator>>(std::istream& in, PGNGame& obj);
    friend inline bool operator==(const PGNGame& a, const PGNGame& b)
    {
        auto test1 = a._parameters == b._parameters;
        auto test2 = a._moves == b._moves;
        return test1 && test2;
    }
    friend inline bool operator!=(const PGNGame& a, const PGNGame& b)
    {
        return !(a == b);
    }

    void determineChessMoves();
    FENLine couldntBreath();

private:
    PGNParameters _parameters;
    PGNMoves _moves;
    std::string _fenParameters;
    std::string _fenReport;
    std::vector<std::string> _originalFile;
    FENLineWithParameters _extraFENLine;
    FENLineListWithParameters _FENLineList;
    ChessMoves _chessMoves;
    int _nextMove = 0;
    int _totalMoves = 0;
    ChessBoard _board;

    PGNMoves readFENLine(const PGNMoves& _moves);
    const ChessBoard& updateBoard(const FENLine& fenLine);

public:
    PGNGame() {};
    PGNGame(PGNParameters parameters,
        PGNMoves moves) : _parameters(parameters), _moves(moves) {}
    inline const PGNParameters& parameters() const { return _parameters; }
    virtual const std::string& FENparameters() const { return _fenParameters; };
    virtual void FENparameters(const std::string& fenParameters) { _fenParameters = fenParameters; };
    virtual const std::string& FENreport() const { return _fenReport; };
    virtual void FENreport(const std::string& fenReport) { _fenReport = fenReport; };
    inline PGNMoves pgnmoves() const { return _moves; }
    virtual ChessBoard playGameUntil(const ChessBoard& board, const std::string& move);
    virtual ChessBoard playGameEnd(const ChessBoard& board);
    virtual const ChessMoves& moves() const { return _chessMoves; };
    virtual const ChessBoard& board() const { return _board; };
    virtual const ChessBoard& next();
    virtual const ChessBoard& previous();

};

/**
 * @brief PGNGameMismatchException
 *
 */

concrete class PGNGameMismatchException extends extras::AbstractCustomException {
public:
    PGNGameMismatchException(const extras::WhereAmI& whereAmI)
        : AbstractCustomException("Moves do not match", whereAmI._file.c_str(),
            whereAmI._func.c_str(), whereAmI._line) {}
    static void assertion(const PGNGame& a, const PGNGame& b, const extras::WhereAmI& ref);
};

/**
 * @brief class PGNGames
 */

class PGNGames
{

    friend std::ostream& operator<<(std::ostream& out, const PGNGames& obj);
    friend std::istream& operator>>(std::istream& in, PGNGames& obj);

    std::vector<PGNGame> _games;

public:
    inline std::vector<PGNGame>& games() { return _games; };
    inline int size() { return _games.size(); };
};

/**
 * @brief EndOfChessGamesException
 *
 */

concrete class EndOfChessGamesException extends extras::AbstractCustomException {
public:
    EndOfChessGamesException(const extras::WhereAmI& whereAmI)
        : AbstractCustomException("No more ChessGames in PNG file", whereAmI._file.c_str(),
            whereAmI._func.c_str(), whereAmI._line) {}
    static void assertion(const std::string& filename, const extras::WhereAmI& ref);
};

/**
 * @brief PGNtoFENMistmatchException
 *
 */

concrete class PGNtoFENMistmatchException extends extras::AbstractCustomException {
public:
    PGNtoFENMistmatchException(const std::string& msg, const extras::WhereAmI& whereAmI)
        : AbstractCustomException(msg.c_str(), whereAmI._file.c_str(),
            whereAmI._func.c_str(), whereAmI._line) {}
    static void assertion(int sizePGN, int sizeFEN, const std::string& msg, const extras::WhereAmI& ref);
};


#endif // _PGNGAME_HPP
