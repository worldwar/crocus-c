
#include "common.h"
#include <board.h>
#include <plan/plan.h>

int Board::count(const std::list<Position> &range) const {
    auto pred = [this](auto position) { return this->occupied(position); };
    return count_if(range.begin(), range.end(), pred);
}

Piece *Board::selectOne(std::function<bool(Piece *)> p) const {
    auto pieces = select(p);
    if (!pieces.empty()) {
        return pieces.front();
    }
    return nullptr;
}

std::list<Piece *> Board::select(std::function<bool(Piece *)> p) const {
    std::list<Piece *> result;
    for (auto &row : _positions) {
        for (Piece *piece : row) {
            if (piece != nullptr) {
                if (p(piece)) {
                    result.push_back(piece);
                }
            }
        }
    }
    return result;
}

Piece *Board::king(Force force) const {
    return selectOne([force](auto piece) {
        return piece->kind() == Kind::KING && piece->force() == force;
    });
}

std::list<Piece *> Board::forcePieces(Force force) const {
    return select([force](auto piece) { return piece->force() == force; });
}

std::list<Piece *> Board::all() const {
    return select([](auto piece) { return true; });
}

void Board::reset() {
    place(new Piece{Force::RED, Kind::ROOK, {1, 1}});
    place(new Piece{Force::RED, Kind::KNIGHT, {2, 1}});
    place(new Piece{Force::RED, Kind::BISHOP, {3, 1}});
    place(new Piece{Force::RED, Kind::GUARD, {4, 1}});
    place(new Piece{Force::RED, Kind::KING, {5, 1}});
    place(new Piece{Force::RED, Kind::GUARD, {6, 1}});
    place(new Piece{Force::RED, Kind::BISHOP, {7, 1}});
    place(new Piece{Force::RED, Kind::KNIGHT, {8, 1}});
    place(new Piece{Force::RED, Kind::ROOK, {9, 1}});
    place(new Piece{Force::RED, Kind::GUN, {2, 3}});
    place(new Piece{Force::RED, Kind::GUN, {8, 3}});
    place(new Piece{Force::RED, Kind::PAWN, {1, 4}});
    place(new Piece{Force::RED, Kind::PAWN, {3, 4}});
    place(new Piece{Force::RED, Kind::PAWN, {5, 4}});
    place(new Piece{Force::RED, Kind::PAWN, {7, 4}});
    place(new Piece{Force::RED, Kind::PAWN, {9, 4}});

    place(new Piece{Force::BLACK, Kind::ROOK, {9, 10}});
    place(new Piece{Force::BLACK, Kind::KNIGHT, {8, 10}});
    place(new Piece{Force::BLACK, Kind::BISHOP, {7, 10}});
    place(new Piece{Force::BLACK, Kind::GUARD, {6, 10}});
    place(new Piece{Force::BLACK, Kind::KING, {5, 10}});
    place(new Piece{Force::BLACK, Kind::GUARD, {4, 10}});
    place(new Piece{Force::BLACK, Kind::BISHOP, {3, 10}});
    place(new Piece{Force::BLACK, Kind::KNIGHT, {2, 10}});
    place(new Piece{Force::BLACK, Kind::ROOK, {1, 10}});

    place(new Piece{Force::BLACK, Kind::GUN, {8, 8}});
    place(new Piece{Force::BLACK, Kind::GUN, {2, 8}});
    place(new Piece{Force::BLACK, Kind::PAWN, {9, 7}});
    place(new Piece{Force::BLACK, Kind::PAWN, {7, 7}});
    place(new Piece{Force::BLACK, Kind::PAWN, {5, 7}});
    place(new Piece{Force::BLACK, Kind::PAWN, {3, 7}});
    place(new Piece{Force::BLACK, Kind::PAWN, {1, 7}});
}

Board Board::tryApply(const Action &action) const {
    Board board = duplicate();
    board.apply(action);
    return board;
}

Board Board::duplicate() const {
    Board board = Board();
    std::function<void(Piece *)> op = [&](Piece *piece) {
        board.place(piece->duplicate());
    };
    each(all(), op);
    return board;
}

Board::~Board() {
    std::function<void(Piece * piece)> op = [](auto piece) { delete piece; };
    each(all(), op);
}

void Board::apply(const Action &action) {
    Piece *piece = this->piece(action.piece().position());
    Position to = action.target();
    if (action.actionType() == ActionType::CAPTURE) {
        makeEmpty(to);
    }
    move(piece, to);
}

bool Board::checked(Force force) const {
    auto pieces = forcePieces(opposed(force));
    return any_match(pieces,
                     [this](auto piece) { return this->checkable(piece); });
}

bool Board::checkable(const Piece *piece) const {
    Piece *opposedKing = king(opposed(piece->force()));
    Action action =
        Action(*piece, opposedKing->position(), ActionType::CAPTURE);
    auto rule = ActionRule::rule(piece->kind());
    return rule->legal(*this, action);
}

bool Board::exists(const Piece *piece) const {
    if (!piece->position().legal())
        return false;
    Piece *realPiece = this->piece(piece->position());
    return realPiece != nullptr && piece->force() == realPiece->force() &&
           piece->kind() == piece->kind();
}

bool Board::checkmated(Force force) const {
    return none_match(forcePieces(force), [this](const Piece *piece) {
        return any_match(
            Plan::planOf(piece->kind()).plan(*this, piece),
            [this](const Action &action) { return this->legal(action); });
    });
}

bool Board::legal(const Action &action) const {
    auto &rules = ActionRule::rulesOf(action.piece().kind());
    return all_match(rules, [this, action](const ActionRule *rule) {
        return rule->legal(*this, action);
    });
}
