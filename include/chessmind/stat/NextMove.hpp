#ifndef _NEXTMOVE_HPP
#define _NEXTMOVE_HPP

#include <iostream>
#include <vector>
#include "StatLine.hpp"
#include "../game/ChessMoves.hpp"

//
// StatWriter
// Encapsulates all behaviour unique to a PGN parser 
//

interface NextMoveInterface
{
    virtual ChessMoves determine(const StatLines& statLines) pure;
    virtual StatLines apply(const StatLines& statLines, const ChessMoves& nextMoves) pure;
};

class NextMove implements NextMoveInterface
{
public:
    virtual ChessMoves determine(const StatLines& statLines);
    virtual StatLines apply(const StatLines& statLines, const ChessMoves& nextMoves);
};

#endif // _NEXTMOVE_HPP
