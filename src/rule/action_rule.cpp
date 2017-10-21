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
        std::list<Position> range = Positions ::range(piece.position(), to);
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
