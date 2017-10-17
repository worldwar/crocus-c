#include <algorithm>
#include <functional>
#include <list>
#include <cassert>
#include "numbers.h"
#include "common.h"
#include "position.h"
#include "positions.h"

std::list<Position> Positions::range(const Position &from, const Position &to, bool include_endpoints) {
    assert(from.in_line(to));
    if (from.x() == to.x()) {
        int x = from.x();
        std::function<Position(int)> op = [x](int y) { return Position(x, y); };
        return map(Numbers::range(from.y(), to.y(), include_endpoints), op);
    } else {
        int y = from.y();
        std::function<Position(int)> op = [y](int x) { return Position(x, y); };
        return map(Numbers::range(from.x(), to.x(), include_endpoints), op);
    }
}

bool Positions::inForceArea(const Position &position, Force force) {
    if (force == Force::RED) {
        return position.y() <= 5;
    } else {
        return position.y() >= 6;
    }
}

bool Positions::inKingArea(const Position &position, Force force) {
    if (force == Force::RED) {
        return position.xin(4, 6) && position.yin(1, 3);
    } else {
        return position.xin(4, 6) && position.yin(8, 10);
    }
}

int Positions::xd(const Position &from, const Position &to) {
    return abs(from.x() - to.x());
}

int Positions::yd(const Position &from, const Position &to) {
    return abs(from.y() - to.y());
}

int Positions::md(const Position &from, const Position &to) {
    return xd(from, to) + yd(from, to);
}

std::list<Position> Positions::row(const Position &position) {
    return row(position.y());
}

std::list<Position> Positions::row(int y) {
    return range(Position(1,y), Position(9, y), true);
}

std::list<Position> Positions::column(const Position &position) {
    return column(position.x());
}

std::list<Position> Positions::column(int x) {
    return range(Position(x, 1), Position(x, 10), true);
}


