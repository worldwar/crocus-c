#include <algorithm>
#include <functional>
#include "position.h"
#include "common.h"

std::list<Position> range(const Position &from, const Position &to) {
    if (from.x() == to.x()) {
        int x = from.x();
        std::function<Position(int)> op = [x](int y) { return Position(x, y); };
        return map(range(from.y(), to.y()), op);
    } else {
        int y = from.y();
        std::function<Position(int)> op = [y](int x) { return Position(x, y); };
        return map(range(from.x(), to.x()), op);
    }
}