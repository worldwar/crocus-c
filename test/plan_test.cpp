#include "action.h"
#include "board.h"
#include "plan/plan.h"
#include "gtest/gtest.h"

bool containsPosition(const std::list<Action> &actions,
                      const Position &position) {
    return any_match(actions, [position](Action &action) {
        return action.target() == position;
    });
}

TEST(TestPlan, testKingPlan) {
    const KingPlan &plan = KingPlan();
    Board board = Board();
    board.reset();
    Piece *redKing = board.king(Force::RED);
    const std::list<Action> &actions = plan.plan(board, redKing);

    EXPECT_TRUE(containsPosition(actions, {5, 2}));
    EXPECT_FALSE(containsPosition(actions, {5, 0}));
    EXPECT_FALSE(containsPosition(actions, {5, 3}));
}

TEST(TestPlan, testRookPlan) {
    const Plan &plan = RookPlan();
    Board board = Board();
    board.reset();
    Piece *redRook = board.piece({1, 1});
    const std::list<Action> &actions = plan.plan(board, redRook);

    EXPECT_TRUE(containsPosition(actions, {1, 2}));
    EXPECT_TRUE(containsPosition(actions, {1, 3}));
    EXPECT_FALSE(containsPosition(actions, {2, 2}));
}

TEST(TestPlan, testKnightPlan) {
    const Plan &plan = KnightPlan();
    Board board = Board();
    board.reset();
    Piece *blackKnight = board.piece({8, 10});
    const std::list<Action> &actions = plan.plan(board, blackKnight);

    EXPECT_TRUE(containsPosition(actions, {9, 8}));
    EXPECT_TRUE(containsPosition(actions, {7, 8}));
    EXPECT_FALSE(containsPosition(actions, {8, 8}));
}

TEST(TestPlan, testBishopPlan) {
    const Plan &plan = BishopPlan();
    Board board = Board();
    board.reset();
    Piece *redBishop = board.piece({7, 1});
    const std::list<Action> &actions = plan.plan(board, redBishop);

    EXPECT_TRUE(containsPosition(actions, {9, 3}));
    EXPECT_TRUE(containsPosition(actions, {5, 3}));
    EXPECT_FALSE(containsPosition(actions, {7, 3}));
    EXPECT_FALSE(containsPosition(actions, {9, -1}));
    EXPECT_FALSE(containsPosition(actions, {5, -1}));
}

TEST(TestPlan, testGuardPlan) {
    const Plan &plan = GuardPlan();
    Board board = Board();
    board.reset();
    Piece *blackGuard = board.piece({4, 10});
    const std::list<Action> &actions = plan.plan(board, blackGuard);

    EXPECT_TRUE(containsPosition(actions, {5, 9}));
    EXPECT_FALSE(containsPosition(actions, {5, 11}));
    EXPECT_FALSE(containsPosition(actions, {4, 9}));
}

TEST(TestPlan, testPawnPlan) {
    const Plan &plan = PawnPlan();
    Board board = Board();
    board.reset();
    Piece *blackPawn = board.piece({1, 7});
    const std::list<Action> &actions = plan.plan(board, blackPawn);

    EXPECT_TRUE(containsPosition(actions, {1, 6}));
    EXPECT_FALSE(containsPosition(actions, {1, 5}));
    EXPECT_FALSE(containsPosition(actions, {0, 6}));
}
