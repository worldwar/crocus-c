
#include <board.h>
#include <functional>
#include <list>
#include <position.h>

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
