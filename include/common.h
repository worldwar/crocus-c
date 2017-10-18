#ifndef CROCUS_COMMON_H
#define CROCUS_COMMON_H

#include <list>
#include <functional>
#include <algorithm>

class Position;

template<typename R, typename C>
std::list<R> map(std::list<C> col, std::function<R(C)> op) {
    std::list<R> r;
    std::transform(col.begin(), col.end(), std::back_inserter(r), op);
    return r;
}

template<typename C, typename F>
bool all_match(C col, F op) {
    return std::all_of(col.begin(), col.end(), op);
}

#endif //CROCUS_COMMON_H
