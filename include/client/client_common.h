#ifndef CROCUS_CLIENT_COMMON_H
#define CROCUS_CLIENT_COMMON_H

#include <enums.h>
#include <position.h>

namespace common {
    Position view(const Position &position, Force viewer);
} // namespace common

#endif // CROCUS_CLIENT_COMMON_H
