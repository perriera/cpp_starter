#include <iostream>
#include "../include/cpp_starter/pgn/notation/TypePromote.hpp"
#include "../include/cpp_starter/game/ChessBoard.hpp"
#include "../include/cpp_starter/game/ChessPosition.hpp"
#include "../include/cpp_starter/game/ChessSquare.hpp"

using namespace std;

istream& operator>>(istream& in, PGNotationTypePromote& obj)
{
    in >> obj._position;
    char check;
    in >> check;
    TypePromoteException::assertation(check);
    in >> obj._promotion;
    obj._san = obj._position;
    return in;
}

void TypePromoteException::assertation(char check)
{
    if (check != '=')
    {
        throw TypePromoteException("Not TypePromote format: " + check);
    }
}

string PGNotationTypePromote::resolve(const MovesTable& moves, const string& black_or_white_set, const ChessBoard* board) const
{
    // int rank1 = -1;
    string _foundMove;
    ChessMove _move;
    for (auto move : moves)
    {
        _move = move;
        char symbol = board->symbolAt(_move.a());
        if (black_or_white_set.find(symbol) != std::string::npos)
            if (toupper(symbol) == 'P')
                _foundMove = move;
    }
    if (_foundMove.size() == 0)
        throw TypePromoteException("No moves found: " + original());
    ChessBoard& b = const_cast<ChessBoard&>(*board);
    _move = _foundMove;
    bool is_black = isupper(black_or_white_set[0]);
    char _black_or_white = is_black ? toupper(_promotion) : tolower(_promotion);
    b.setPiece(_move.a(), _black_or_white);
    return _foundMove;
}
