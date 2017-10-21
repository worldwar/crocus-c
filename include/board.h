#ifndef CROCUS_BOARD_H
#define CROCUS_BOARD_H

#include "action.h"
#include "common.h"
#include "piece.h"
#include "position.h"

class Board {
private:
    Piece *_positions[10][11];

public:
    void place(Piece *const piece, const Position &position) {
        piece->setPosition(position);
        _positions[position.x()][position.y()] = piece;
    }

    void place(Piece *const piece) {
        place(piece, piece->position());
    }

    bool empty(const Position &position) const {
        const Piece *p = piece(position);
        return p == nullptr;
    }

    bool occupied(const Position &position) const {
        return !empty(position);
    }

    bool empty(const std::list<Position> &range) const {
        return all_match(range, [this](const Position &position) {
            return empty(position);
        });
    }

    Piece *piece(const Position &position) const {
        return _positions[position.x()][position.y()];
    }

    int count(const std::list<Position> &range) const;

    std::list<Piece *> select(std::function<bool(Piece *)> p) const;

    Piece *selectOne(std::function<bool(Piece *)> p) const;

    Piece *king(Force force) const;

    std::list<Piece *> forcePieces(Force force) const;

    std::list<Piece *> all() const;

    void makeEmpty(const Position &position) {
        _positions[position.x()][position.y()] = nullptr;
    }

    void move(Piece *piece, const Position &position) {
        makeEmpty(piece->position());
        place(piece, position);
    }

    ActionType actionType(const Position &position) const {
        return occupied(position) ? ActionType::CAPTURE : ActionType::MOVE;
    }

    Action makeAction(const Piece *piece, const Position &position) const {
        ActionType type = actionType(position);
        return Action{*piece, position, type};
    }

    void reset();
};

#endif // CROCUS_BOARD_H
