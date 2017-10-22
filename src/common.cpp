#include "common.h"

Force opposed(Force force) {
    if (force == Force::RED) {
        return Force::BLACK;
    } else {
        return Force::RED;
    }
};
