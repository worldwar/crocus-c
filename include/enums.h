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

enum class GameState { NOT_STARTED = 1, STARTED = 2, ENDED = 3 };

enum class GameResult { RED_WIN = 1, BLACK_WIN = 2, DRAW = 3 };

#endif // CROCUS_ENUMS_H
