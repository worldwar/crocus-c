#include "rule/action_rule.h"
#include "action.h"
#include "board.h"
#include "positions.h"

bool RookActionRule::legal(const Board &board, const Action &action) const {
    Position from = action.piece().position();
    Position to = action.target();
    return from.in_line(to) && board.empty(Positions::range(from, to));
}

bool PieceActionRule<Kind::KING>::legal(const Board &board,
                                        const Action &action) const {
    const Position &to = action.target();
    const Piece &piece = action.piece();
    const Position &from = piece.position();
    return Positions::inKingArea(to, piece.force()) &&
           Positions::md(from, to) == 1;
}

bool PieceActionRule<Kind::ROOK>::legal(const Board &board,
                                        const Action &action) const {
    const Position &from = action.piece().position();
    const Position &to = action.target();
    return from.in_line(to) && board.empty(Positions::range(from, to));
}

bool PieceActionRule<Kind::KNIGHT>::legal(const Board &board,
                                          const Action &action) const {
    const Position &from = action.piece().position();
    const Position &to = action.target();

    return Positions::md(from, to) == 3 &&
           (Positions::xd(from, to) == 1 || Positions::yd(from, to) == 1) &&
           board.empty(Positions::knightObstacle(from, to));
}

bool PieceActionRule<Kind::GUN>::legal(const Board &board,
                                       const Action &action) const {
    Piece piece = action.piece();
    Position to = action.target();
    if (action.actionType() == ActionType::MOVE) {
        const ActionRule &rule = PieceActionRule<Kind::ROOK>();
        return rule.legal(board, action);
    } else {
        bool in_line = piece.position().in_line(to);
        if (!in_line)
            return false;
        std::list<Position> range = Positions::range(piece.position(), to);
        return board.count(range) == 1;
    }
}

bool PieceActionRule<Kind::BISHOP>::legal(const Board &board,
                                          const Action &action) const {
    Piece piece = action.piece();
    Position from = piece.position();
    Position to = action.target();

    return Positions::xd(from, to) == 2 && Positions::yd(from, to) == 2 &&
           Positions::inForceArea(to, piece.force()) &&
           board.empty(Positions::bishopObstacle(from, to));
}

bool PieceActionRule<Kind::GUARD>::legal(const Board &board,
                                         const Action &action) const {
    Piece piece = action.piece();
    Position to = action.target();
    return Positions::xd(piece.position(), to) == 1 &&
           Positions::yd(piece.position(), to) == 1 &&
           Positions::inKingArea(to, piece.force());
}

bool PieceActionRule<Kind::PAWN>::legal(const Board &board,
                                        const Action &action) const {
    Piece piece = action.piece();
    Position to = action.target();
    Position from = piece.position();

    return Positions::md(from, to) == 1 &&
           ((piece.red() && to.y() >= from.y()) ||
            (piece.black() && to.y() <= from.y())) &&
           (!Positions::inForceArea(from, piece.force()) || to.x() == from.x());
}

bool CheckedRule::legal(const Board &board, const Action &action) const {
    Force force = action.piece().force();
    Board b = board.tryApply(action);
    return !b.checked(force);
}

const ActionRule *ActionRule::rule(Kind kind) {
    static std::map<Kind, const ActionRule *> rules;
    if (rules.empty()) {
        rules.insert({Kind::KING, new PieceActionRule<Kind::KING>()});
        rules.insert({Kind::ROOK, new PieceActionRule<Kind::ROOK>()});
        rules.insert({Kind::KNIGHT, new PieceActionRule<Kind::KNIGHT>()});
        rules.insert({Kind::BISHOP, new PieceActionRule<Kind::BISHOP>()});
        rules.insert({Kind::GUARD, new PieceActionRule<Kind::GUARD>()});
        rules.insert({Kind::GUN, new PieceActionRule<Kind::GUN>()});
        rules.insert({Kind::PAWN, new PieceActionRule<Kind::PAWN>()});
    }
    return rules.at(kind);
}

const std::list<const ActionRule *> ActionRule::rulesOf(Kind kind) {
    static std::list<ActionRule *> basicRules;
    static std::list<ActionRule *> globalRules;
    if (basicRules.empty()) {
        basicRules.push_back(new ExistenceRule());
        basicRules.push_back(new PositionChangeRule());
        basicRules.push_back(new TargetForceRule());
    }
    if (globalRules.empty()) {
        globalRules.push_back(new CheckedRule());
        globalRules.push_back(new KingFaceRule());
    }

    std::list<const ActionRule *> rules;

    rules.insert(rules.begin(), basicRules.begin(), basicRules.end());
    rules.push_back(rule(kind));
    rules.insert(rules.end(), globalRules.begin(), globalRules.end());
    return rules;
}

bool ExistenceRule::legal(const Board &board, const Action &action) const {
    Piece piece = action.piece();
    return board.exists(&piece) &&
           board.actionType(action.target()) == action.actionType();
}

bool KingFaceRule::legal(const Board &board, const Action &action) const {
    Board b = board.tryApply(action);
    Piece piece = action.piece();
    Position kingPosition = b.king(piece.force())->position();
    Position opposedKingPosition = b.king(opposed(piece.force()))->position();
    if (Positions::xd(kingPosition, opposedKingPosition) == 0) {
        return !b.empty(Positions::range(kingPosition, opposedKingPosition));
    }
    return true;
}

bool PositionChangeRule::legal(const Board &board, const Action &action) const {
    return action.piece().position() != action.target();
}

bool TargetForceRule::legal(const Board &board, const Action &action) const {
    Position position = action.target();
    Piece *piece = board.piece(position);
    return piece == nullptr || piece->force() != action.piece().force();
}
