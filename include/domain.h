#ifndef CROCUS_DOMAIN_H
#define CROCUS_DOMAIN_H

#include "piece.h"
#include <string>

namespace domain {
enum class BorderType {
    INNER = 1,
    LEFT_TOP = 2,
    TOP = 3,
    RIGHT_TOP = 4,
    RIGHT = 5,
    RIGHT_BOTTOM = 6,
    BOTTOM = 7,
    LEFT_BOTTOM = 8,
    LEFT = 9
};
std::string symbol(const Piece *piece);
std::string border(const Position &position);
BorderType borderType(const Position &position);

} // namespace domain
#endif // CROCUS_DOMAIN_H
