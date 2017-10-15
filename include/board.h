#ifndef CROCUS_BOARD_H
#define CROCUS_BOARD_H

#include "position.h"
#include "common.h"

class Piece;

class Board {
private:
    Piece* _positions[10][11];


public:
    bool empty(const Position& position) const {
        const Piece*  p = piece(position);
        return  p == nullptr;
    }

    bool empty(const std::list<Position>& range) const {
        return all_match(range, [this](const Position& position){ return empty(position);});
    }

    Piece* piece(const Position&  position) const {
        return _positions[position.x()][position.y()];
    }
};

#endif //CROCUS_BOARD_H
