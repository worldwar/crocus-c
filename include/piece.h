#ifndef CROCUS_PIECE_H
#define CROCUS_PIECE_H

#include "enums.h"
#include "position.h"

class Piece {
private:
    Force _force;
    Kind _kind;
    Position _position;

public:
    Piece(Force force, Kind kind, Position position)
        : _force(force), _kind(kind), _position(position) {}

    Force force() const {
        return _force;
    }

    Kind kind() const {
        return _kind;
    }

    Position position() const {
        return _position;
    }

    void setPosition(const Position &position) {
        _position = position;
    }

    bool red() const {
        return _force == Force::RED;
    }

    bool black() const {
        return !red();
    }

    Piece *duplicate() const {
        return new Piece{_force, _kind, _position};
    }
};

#endif // CROCUS_PIECE_H
