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

    int toInt(uint8_t buffer[4]) {
        return int((unsigned char)(buffer[0]) << 24 |
                   (unsigned char)(buffer[1]) << 16 |
                   (unsigned char)(buffer[2]) << 8 |
                   (unsigned char)(buffer[3]));
    }
} // namespace common
