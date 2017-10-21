#include "action.h"
#include "board.h"
#include "rule/action_rule.h"
#include "gtest/gtest.h"

TEST(RookActionRule, MoveInLine) {
    auto a = RookActionRule();
    auto b = Board();
    auto rook = Piece{Force::RED, Kind::ROOK, {1, 1}};
    auto knight = Piece{Force::BLACK, Kind::KNIGHT, {1, 3}};
    auto c = Action(rook, {1, 2}, ActionType::MOVE);

    EXPECT_EQ(true, a.legal(b, c));
}

TEST(KingActionRule, testRuleForRedKing) {
    auto board = Board();
    const PieceActionRule<Kind::KING> &rule = PieceActionRule<Kind::KING>();
    Piece *rook = new Piece{Force::RED, Kind::ROOK, {1, 1}};
    Piece *knight = new Piece{Force::RED, Kind::KNIGHT, {5, 3}};
    Piece *king = new Piece{Force::RED, Kind::KING, {4, 3}};
    board.place(rook);
    board.place(knight);
    board.place(king);

    Action moveAction = Action{*king, {4, 2}, ActionType::MOVE};
    Action captureAction = Action(*king, {5, 3}, ActionType::CAPTURE);
    Action illegalAction = Action(*king, {3, 3}, ActionType::MOVE);
    Action illegalAction2 = Action(*king, {4, 4}, ActionType::MOVE);
    Action illegalAction3 = Action(*king, {4, 1}, ActionType::MOVE);

    EXPECT_TRUE(rule.legal(board, moveAction));
    EXPECT_TRUE(rule.legal(board, captureAction));
    EXPECT_FALSE(rule.legal(board, illegalAction));
    EXPECT_FALSE(rule.legal(board, illegalAction2));
    EXPECT_FALSE(rule.legal(board, illegalAction3));

    board.move(king, {6, 3});

    Action illegalAction4 = Action{*king, {7, 3}, ActionType::MOVE};
    Action illegalAction5 = Action{*king, {6, 4}, ActionType::MOVE};

    EXPECT_FALSE(rule.legal(board, illegalAction4));
    EXPECT_FALSE(rule.legal(board, illegalAction5));
}

TEST(KnightActionRule, testRuleForKnight) {

    auto board = Board();
    auto rule = PieceActionRule<Kind::KNIGHT>();
    Piece *rook = new Piece{Force::RED, Kind::ROOK, {1, 1}};
    Piece *knight = new Piece{Force::BLACK, Kind::KNIGHT, {5, 3}};
    Piece *king = new Piece{Force::RED, Kind::KING, {4, 3}};
    Piece *pawn = new Piece{Force::RED, Kind::PAWN, {6, 5}};
    board.place(rook);
    board.place(knight);
    board.place(king);
    board.place(pawn);

    Action moveAction = Action(*knight, {4, 5}, ActionType::MOVE);

    Action captureAction = Action(*knight, {6, 5}, ActionType::CAPTURE);
    Action illegalAction = Action(*knight, {7, 5}, ActionType::MOVE);
    Action obstacleActionByKing1 = Action(*knight, {3, 4}, ActionType::MOVE);
    Action obstacleActionByKing2 = Action(*knight, {3, 2}, ActionType::MOVE);

    EXPECT_TRUE(rule.legal(board, moveAction));
    EXPECT_TRUE(rule.legal(board, captureAction));
    EXPECT_FALSE(rule.legal(board, illegalAction));
    EXPECT_FALSE(rule.legal(board, obstacleActionByKing1));
    EXPECT_FALSE(rule.legal(board, obstacleActionByKing2));

    board.makeEmpty(king->position());

    EXPECT_TRUE(rule.legal(board, obstacleActionByKing1));
    EXPECT_TRUE(rule.legal(board, obstacleActionByKing2));
}

TEST(CheckedRule, testCheckable) {
    Board board = Board();
    board.reset();

    Piece *redRook = board.piece({1, 1});
    Piece *redGun = board.piece({2, 3});
    EXPECT_FALSE(board.checkable(redRook));
    EXPECT_FALSE(board.checkable(redGun));

    board.move(redRook, {5, 8});
    board.move(redGun, {5, 6});
    EXPECT_TRUE(board.checkable(redRook));
    EXPECT_FALSE(board.checkable(redGun));
    board.move(redRook, {1, 1});
    EXPECT_TRUE(board.checkable(redGun));
}

TEST(CheckedRule, testForceChecked) {
    Board board = Board();
    board.reset();

    EXPECT_FALSE(board.checked(Force::RED));
    Piece *blackKnight = board.piece({2, 10});
    Piece *blackPawn = board.piece({1, 7});

    board.move(blackKnight, {3, 2});
    EXPECT_TRUE(board.checked(Force::RED));
    board.move(blackPawn, {4, 2});
    EXPECT_FALSE(board.checked(Force::RED));
    board.move(blackPawn, {5, 2});
    EXPECT_TRUE(board.checked(Force::RED));
    board.move(blackKnight, {2, 10});
    EXPECT_TRUE(board.checked(Force::RED));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}