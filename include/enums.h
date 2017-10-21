#ifndef CROCUS_ENUMS_H
#define CROCUS_ENUMS_H

enum class Force { RED = 1, BLACK = 2 };

enum class Kind {
    KING = 1,
    ROOK = 2,
    KNIGHT = 3,
    GUN = 4,
    BISHOP = 5,
    GUARD = 6,
    PAWN = 7
};

enum class ActionType { MOVE = 1, CAPTURE = 2 };

#endif // CROCUS_ENUMS_H
