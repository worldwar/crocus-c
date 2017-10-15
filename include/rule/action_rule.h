#ifndef CROCUS_ACTION_RULE_H
#define CROCUS_ACTION_RULE_H

class Board;
class Action;

class ActionRule {
public:
    virtual bool legal(const Board& board, const Action& action) = 0;
};

class RookActionRule : public ActionRule {
public:
    bool legal(const Board& board, const Action& action) const;

};
#endif //CROCUS_ACTION_RULE_H
