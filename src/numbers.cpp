#include "numbers.h"
#include <cstdlib>
#include <numeric>

std::list<int> Numbers::range(int from, int to, bool include_endpoints) {
    int size = include_endpoints ? abs(from - to) + 1 : abs(from - to) - 1;
    if (size <= 0) {
        return std::list<int>();
    }
    int delta = from < to ? 1 : -1;
    int n = include_endpoints ? from - 1 : from;

    std::list<int> result(size);
    std::iota(result.begin(), result.end(), from + 1);
    std::generate(result.begin(), result.end(),
                  [&n, &delta] { return n += delta; });
    return result;
}
