#ifndef CROCUS_COMMON_H
#define CROCUS_COMMON_H

#include <list>
#include <functional>

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

std::list<int> range(int from, int to);

std::list<Position> range(const Position &from, const Position &to);


#endif //CROCUS_COMMON_H
