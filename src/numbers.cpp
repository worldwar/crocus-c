#include <list>
#include <numeric>
#include "numbers.h"

std::list<int> Numbers::range(int from, int to) {
    if (from == to) {
        return std::list<int>();
    }
    if (from > to) {
        return range(to, from);
    }
    std::list<int> result(to - from - 1);
    std::iota(result.begin(), result.end(), from + 1);
    return result;
}
