#ifndef _FENPLACEMENT_HPP
#define _FENPLACEMENT_HPP

#include <iostream>
#include <vector>
#include <string>
#include "../include/chessmind/san/SANInterface.hpp"
#include "../include/chessmind/game/ChessMoves.hpp"
#include "../include/chessmind/pgn/PGNSymbolsInterface.hpp"

/**
 * @brief FENPlacementInterface
 */

using FENArray = char[8][8];

interface FENPlacementInterface extends SymbolAtInterface {

    virtual const FENArray& placements() const pure;
    virtual ChessMoves compare(
        const FENPlacementInterface& white,
        const FENPlacementInterface& black,
        const SANInterface& san) const pure;

};

//
// FENReader
// Encapsulates all behaviour unique to a PGN parser
//

class FENPlacement implements FENPlacementInterface
{
    friend std::ostream& operator<<(std::ostream& out, const FENPlacement& obj);
    friend std::istream& operator>>(std::istream& in, FENPlacement& obj);
    friend inline bool operator==(const FENPlacement& a, const FENPlacement& b)
    {
        for (char row = '1'; row < '9'; row++)
            for (char col = 'a'; col < 'i'; col++)
                if (a.symbolAt(col, row) != b.symbolAt(col, row))
                    return false;
        return true;
    }
    friend inline bool operator!=(const FENPlacement& a, const FENPlacement& b)
    {
        return !(a == b);
    }
    FENPlacement& operator=(const std::string& other)
    {
        int index = 0;
        for (char row = '1'; row < '9'; row++)
            for (char col = 'a'; col < 'i'; col++)
                this->_placements[row - '1'][col - 'a'] = other[index++];
        return *this;
    }

private:
    FENArray _placements = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'} };

public:
    char placement(int col, int row) const
    {
        return _placements[col][row];
    }

    virtual char symbolAt(char col, char row) const;
    virtual char symbolAt(const ChessPosition& pos) const;
    operator std::string() const;
    static std::string expanded(const FENPlacement& ref);

    virtual const FENArray& placements() const override { return _placements; }

    virtual ChessMoves compare(
        const FENPlacementInterface& white,
        const FENPlacementInterface& black,
        const SANInterface& san) const override;


};

#endif // _FENPLACEMENT_HPP
