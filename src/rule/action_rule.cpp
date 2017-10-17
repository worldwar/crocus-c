#include "rule/action_rule.h"
#include "board.h"
#include "action.h"
#include "positions.h"

bool RookActionRule::legal(const Board &board, const Action &action) const {
    Position from = action.piece().position();
    Position to = action.target();
    return from.in_line(to) &&
           board.empty(Positions::range(from, to));
}



