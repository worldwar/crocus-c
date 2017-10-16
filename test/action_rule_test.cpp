#include "action.h"
#include "gtest/gtest.h"
#include "board.h"
#include "rule/action_rule.h"

TEST(RookActionRule, MoveInLine) {
  auto a = RookActionRule();
  auto b = Board();
  auto rook = Piece{RED, ROOK, {1,1}};
  auto knight = Piece{BLACK, KNIGHT, {1, 3}};
  auto c = Action(rook, {1, 2}, MOVE);

  EXPECT_EQ(true, a.legal(b, c));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}