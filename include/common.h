#ifndef CROCUS_COMMON_H
#define CROCUS_COMMON_H

#include "enums.h"
#include <algorithm>
#include <functional>
#include <list>

class Position;

template <typename R, typename C>
std::list<R> map(std::list<C> col, std::function<R(C)> op) {
    std::list<R> r;
    std::transform(col.begin(), col.end(), std::back_inserter(r), op);
    return r;
}

template <typename C>
void each(std::list<C> col, std::function<void(C)> op) {
    std::for_each(col.begin(), col.end(), op);
}

template <typename C, typename F>
bool all_match(C col, F op) {
    return std::all_of(col.begin(), col.end(), op);
}

template <typename C, typename F>
bool any_match(C col, F op) {
    return std::any_of(col.begin(), col.end(), op);
}

template <typename T>
bool contains(std::list<T> col, T v) {
    return (std::find(col.begin(), col.end(), v)) != col.end();
}

Force opposed(Force force);
#endif // CROCUS_COMMON_H
