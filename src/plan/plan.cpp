#include <board.h>
#include <plan/plan.h>
#include <positions.h>

std::list<Action> Plan::plan(const Board &board, const Piece *piece) const {
    std::list<Position> positions = this->positions(board, piece);
    Position from = piece->position();

    positions.remove_if([&from](const Position &position) {
        return (!position.legal()) || (from == position);
    });

    std::function<Action(Position)> op = [&board, piece](Position position) {
        return board.makeAction(piece, position);
    };
    return common::map(positions, op);
}

const Plan &Plan::planOf(Kind kind) {
    static std::map<Kind, const Plan *> plans;
    if (plans.empty()) {
        plans.insert({Kind::KING, new KingPlan()});
        plans.insert({Kind::ROOK, new RookPlan()});
        plans.insert({Kind::KNIGHT, new KnightPlan()});
        plans.insert({Kind::GUN, new GunPlan()});
        plans.insert({Kind::BISHOP, new BishopPlan()});
        plans.insert({Kind::GUARD, new GuardPlan()});
        plans.insert({Kind::PAWN, new PawnPlan()});
    }

    return *plans[kind];
}

std::list<Position> KingPlan::positions(const Board &board,
                                        const Piece *piece) const {
    std::list<Position> positions;
    Position from = piece->position();
    positions.push_back(from.move(1, 0));
    positions.push_back(from.move(-1, 0));
    positions.push_back(from.move(0, 1));
    positions.push_back(from.move(0, -1));
    return positions;
}

std::list<Position> RookPlan::positions(const Board &board,
                                        const Piece *piece) const {
    return Positions::cross(piece->position());
}

std::list<Position> KnightPlan::positions(const Board &board,
                                          const Piece *piece) const {
    std::list<Position> positions;
    Position from = piece->position();
    positions.push_back(from.move(1, 2));
    positions.push_back(from.move(1, -2));
    positions.push_back(from.move(-1, 2));
    positions.push_back(from.move(-1, -2));
    positions.push_back(from.move(2, 1));
    positions.push_back(from.move(2, -1));
    positions.push_back(from.move(-2, 1));
    positions.push_back(from.move(-2, -1));
    return positions;
}

std::list<Position> GunPlan::positions(const Board &board,
                                       const Piece *piece) const {
    return Positions::cross(piece->position());
}

std::list<Position> BishopPlan::positions(const Board &board,
                                          const Piece *piece) const {
    std::list<Position> positions;
    Position from = piece->position();
    positions.push_back(from.move(2, 2));
    positions.push_back(from.move(2, -2));
    positions.push_back(from.move(-2, 2));
    positions.push_back(from.move(-2, -2));
    return positions;
}

std::list<Position> GuardPlan::positions(const Board &board,
                                         const Piece *piece) const {
    std::list<Position> positions;
    Position from = piece->position();
    positions.push_back(from.move(1, 1));
    positions.push_back(from.move(1, -1));
    positions.push_back(from.move(-1, 1));
    positions.push_back(from.move(-1, -1));
    return positions;
}

std::list<Position> PawnPlan::positions(const Board &board,
                                        const Piece *piece) const {
    std::list<Position> positions;
    Position from = piece->position();
    positions.push_back(from.move(1, 0));
    positions.push_back(from.move(-1, 0));
    positions.push_back(from.move(0, 1));
    positions.push_back(from.move(0, -1));
    return positions;
}
