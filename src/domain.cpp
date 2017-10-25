#include "domain.h"
#include <common.h>

namespace domain {
    std::string RED_SYMBOLS[] = {"帥", "車", "馬", "砲", "相", "仕", "兵"};

    std::string BLACK_SYMBOLS[] = {"將", "車", "馬", "炮", "象", "士", "卒"};

    std::string BORDER_SYMBOLS[] = {"┼", "┌", "┬", "┐", "┤",
                                    "┘", "┴", "└", "├"};

    std::string symbol(const Piece *p) {
        Kind kind = p->kind();
        if (p->force() == Force::RED) {
            return RED_SYMBOLS[common::cast(kind) - 1];
        } else {
            return BLACK_SYMBOLS[common::cast(kind) - 1];
        }
    }

    std::string border(const Position &position) {
        BorderType type = borderType(position);
        return BORDER_SYMBOLS[common::cast(type) - 1];
    }

    BorderType borderType(const Position &position) {
        int x = position.x();
        int y = position.y();
        if (x == 9 && y == 10) {
            return BorderType::LEFT_TOP;
        }
        if (x == 1 && y == 10) {
            return BorderType::RIGHT_TOP;
        }
        if (x == 1 && y == 1) {
            return BorderType::RIGHT_BOTTOM;
        }
        if (x == 9 && y == 1) {
            return BorderType::LEFT_BOTTOM;
        }
        if (y == 10) {
            return BorderType::TOP;
        }
        if (x == 1) {
            return BorderType::RIGHT;
        }
        if (y == 1) {
            return BorderType::BOTTOM;
        }
        if (x == 9) {
            return BorderType::LEFT;
        }
        return BorderType::INNER;
    }
} // namespace domain