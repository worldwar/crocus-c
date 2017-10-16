#include <stdio.h>
#include "common.h"

#include "position.h"

int main() {

    const std::list<int> &r = range(1, 6);

    printf("size: %d\n", (int)r.size());

    for (auto p : r) {
        printf("x %d\n", p);
    }
    
    const std::list<Position> &list = range(Position(1, 3), Position(5, 3));
    for (auto p : list) {
        printf("position %d %d\n", p.x(), p.y());
    }
}
