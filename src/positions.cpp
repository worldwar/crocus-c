#include <algorithm>
#include <functional>
#include <list>
#include "numbers.h"
#include "common.h"
#include "position.h"
#include "positions.h"

std::list<Position> Positions::range(const Position &from, const Position &to) {
    if (from.x() == to.x()) {
        int x = from.x();
        std::function<Position(int)> op = [x](int y) { return Position(x, y); };
        return map(Numbers::range(from.y(), to.y()), op);
    } else {
        int y = from.y();
        std::function<Position(int)> op = [y](int x) { return Position(x, y); };
        return map(Numbers::range(from.x(), to.x()), op);
    }
}