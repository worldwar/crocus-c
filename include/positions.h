#ifndef CROCUS_POSITIONS_H
#define CROCUS_POSITIONS_H

#include <list>
#include <cstdlib>
#include "enums.h"

class Position;

class Positions {
public:
    static std::list<Position> range(const Position &from, const Position &to, bool include_endpoints = false);

    static bool inForceArea(const Position &position, Force force);

    static bool inKingArea(const Position &position, Force force);

    static int xd(const Position &from, const Position &to);

    static int yd(const Position &from, const Position &to);

    static int md(const Position &from, const Position &to);

    static std::list<Position> row(const Position &position);

    static std::list<Position> row(int y);

    static std::list<Position> column(const Position &position);

    static std::list<Position> column(int x);

    static Position knightObstacle(const Position &from, const Position &to);

    static Position bishopObstacle(const Position &from, const Position &to);
};

#endif //CROCUS_POSITIONS_H
