#ifndef CROCUS_ACTION_RULE_H
#define CROCUS_ACTION_RULE_H

#include <enums.h>

class Board;
class Action;

class ActionRule {
public:
    virtual bool legal(const Board &board, const Action &action) const = 0;
    static const ActionRule *rule(Kind kind);
};

class RookActionRule : public ActionRule {
public:
    bool legal(const Board &board, const Action &action) const override;
};

template <Kind>
class PieceActionRule : public ActionRule {};

template <>
class PieceActionRule<Kind::KING> : public ActionRule {
public:
    bool legal(const Board &board, const Action &action) const override;
};

template <>
class PieceActionRule<Kind::ROOK> : public ActionRule {
public:
    bool legal(const Board &board, const Action &action) const override;
};

template <>
class PieceActionRule<Kind::KNIGHT> : public ActionRule {
public:
    bool legal(const Board &board, const Action &action) const override;
};

template <>
class PieceActionRule<Kind::GUN> : public ActionRule {
public:
    bool legal(const Board &board, const Action &action) const override;
};

template <>
class PieceActionRule<Kind::BISHOP> : public ActionRule {
public:
    bool legal(const Board &board, const Action &action) const override;
};

template <>
class PieceActionRule<Kind::GUARD> : public ActionRule {
public:
    bool legal(const Board &board, const Action &action) const override;
};

template <>
class PieceActionRule<Kind::PAWN> : public ActionRule {
public:
    bool legal(const Board &board, const Action &action) const override;
};

class CheckedRule : public ActionRule {
public:
    bool legal(const Board &board, const Action &action) const override;
};

class ExistenceRule : public ActionRule {
public:
    bool legal(const Board &board, const Action &action) const override;
};

class KingFaceRule : public ActionRule {
public:
    bool legal(const Board &board, const Action &action) const override;
};

class PositionChangeRule : public ActionRule {
public:
    bool legal(const Board &board, const Action &action) const override;
};

class TargetForceRule : public ActionRule {
public:
    bool legal(const Board &board, const Action &action) const override;
};

#endif // CROCUS_ACTION_RULE_H
