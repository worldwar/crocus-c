#ifndef CROCUS_COMMON_H
#define CROCUS_COMMON_H

#include "enums.h"
#include <algorithm>
#include <chrono>
#include <functional>
#include <list>

using Clock = std::chrono::system_clock;
using TimePoint = std::chrono::system_clock::time_point;
using Duration = std::chrono::microseconds;

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

template <typename C, typename F>
bool none_match(C col, F op) {
    return std::none_of(col.begin(), col.end(), op);
}

template <typename T>
bool contains(std::list<T> col, T v) {
    return (std::find(col.begin(), col.end(), v)) != col.end();
}

Force opposed(Force force);

namespace common {
    template <typename R, typename C>
    std::list<R> map(std::list<C> col, std::function<R(C)> op) {
        std::list<R> r;
        std::transform(col.begin(), col.end(), std::back_inserter(r), op);
        return r;
    }

    template <typename T>
    int cast(T t) {
        return static_cast<int>(t);
    }

    Duration duration(const TimePoint &from, const TimePoint &to);

} // namespace common
#endif // CROCUS_COMMON_H
