#include "game.h"
#include "gtest/gtest.h"

TEST(TestGame, testGamePlay) {
    Game game = Game();
    game.start();
    const TimePoint &startDate = game.startDate();

    game.move({5, 7}, {5, 6});
    game.move({2, 3}, {5, 7});
    game.move({8, 8}, {9, 8});
    game.play({8, 3}, {8, 8});

    const TimePoint &turnStartDate = game.turnStartDate();
    EXPECT_EQ(game.turn(), Force::BLACK);
    EXPECT_EQ(game.forceUsedTime(Force::RED),
              common::duration(turnStartDate, startDate));

    game.play({9, 7}, {9, 6});
    EXPECT_EQ(game.turn(), Force::RED);
    EXPECT_FALSE(game.ended());

    game.play({8, 8}, {5, 8});
    EXPECT_TRUE(game.ended());
    EXPECT_EQ(game.result(), GameResult::RED_WIN);
}
