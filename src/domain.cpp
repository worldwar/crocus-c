#include "domain.h"
#include <common.h>

namespace domain {
std::string RED_SYMBOLS[] = {"帥", "車", "馬", "砲", "相", "仕", "兵"};

std::string BLACK_SYMBOLS[] = {"將", "車", "馬", "炮", "象", "士", "卒"};

std::string EMPTY_SYMBOLS = "＋";

std::string symbol(const Piece *p) {
    if (p == nullptr) {
        return EMPTY_SYMBOLS;
    }
    Kind kind = p->kind();
    if (p->force() == Force::RED) {
        return RED_SYMBOLS[common::cast(kind) - 1];
    } else {
        return BLACK_SYMBOLS[common::cast(kind) - 1];
    }
}
} // namespace domain