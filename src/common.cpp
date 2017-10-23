#include "common.h"

Force opposed(Force force) {
    if (force == Force::RED) {
        return Force::BLACK;
    } else {
        return Force::RED;
    }
};

namespace common {
Duration duration(const TimePoint &from, const TimePoint &to) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(to - from);
}
}
