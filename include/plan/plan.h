#ifndef CROCUS_PLAN_H
#define CROCUS_PLAN_H

#include <board.h>
#include <piece.h>

class Plan {
public:
    std::list<Action> plan(const Board &board, const Piece *piece) const;
    static const Plan &planOf(Kind kind);

protected:
    virtual std::list<Position> positions(const Board &board,
                                          const Piece *piece) const = 0;
};

class KingPlan : public Plan {
protected:
    std::list<Position> positions(const Board &board,
                                  const Piece *piece) const override;
};

class RookPlan : public Plan {
protected:
    std::list<Position> positions(const Board &board,
                                  const Piece *piece) const override;
};

class KnightPlan : public Plan {
protected:
    std::list<Position> positions(const Board &board,
                                  const Piece *piece) const override;
};

class GunPlan : public Plan {
protected:
    std::list<Position> positions(const Board &board,
                                  const Piece *piece) const override;
};

class BishopPlan : public Plan {
protected:
    std::list<Position> positions(const Board &board,
                                  const Piece *piece) const override;
};

class GuardPlan : public Plan {
protected:
    std::list<Position> positions(const Board &board,
                                  const Piece *piece) const override;
};

class PawnPlan : public Plan {
protected:
    std::list<Position> positions(const Board &board,
                                  const Piece *piece) const override;
};

#endif // CROCUS_PLAN_H
