#ifndef CROCUS_ACTION_H
#define CROCUS_ACTION_H

#include "enums.h"
#include "piece.h"

class Position;

class Action {
private:
    Piece  _piece;
    Position _target;
    ActionType _type;

public:
    Action(Piece piece, Position target, ActionType type) :
            _piece(piece),
            _target(target),
            _type(type) {
    }

    inline Piece piece() const {
        return _piece;
    }

    inline Position target() const {
        return _target;
    }

    inline ActionType actionType() const {
        return _type;
    }
};

#endif //CROCUS_ACTION_H
