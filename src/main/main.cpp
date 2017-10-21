#include "numbers.h"
#include "positions.h"
#include <list>
#include <stdio.h>

#include "position.h"

int main() {

    const std::list<int> &r = Numbers::range(1, 6);

    printf("size: %d\n", (int)r.size());

    for (auto p : r) {
        printf("x %d\n", p);
    }

    const std::list<int> &t = Numbers::range(6, 1, true);

    printf("size: %d\n", (int)t.size());

    for (auto p : t) {
        printf("x %d\n", p);
    }

    const std::list<Position> &list =
        Positions::range(Position(5, 3), Position(1, 3));
    for (auto p : list) {
        printf("position %d %d\n", p.x(), p.y());
    }
}
