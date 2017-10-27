#include <common.h>
#include <position.h>

namespace common {
    Position view(const Position &position, Force viewer) {
        if (viewer == Force::RED) {
            return position;
        } else {
            return Position({10 - position.x(), 11 - position.y()});
        }
    }
} // namespace common