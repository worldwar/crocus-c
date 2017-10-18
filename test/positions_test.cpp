#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <enums.h>
#include <position.h>
#include <positions.h>

TEST(TestPositions, testInForceArea) {
    ASSERT_TRUE(Positions::inForceArea(Position(3, 5), Force::RED));
    ASSERT_TRUE(Positions::inForceArea(Position(3, 6), Force::BLACK));
    ASSERT_FALSE(Positions::inForceArea(Position(3, 5), Force::BLACK));
    ASSERT_FALSE(Positions::inForceArea(Position(3, 6), Force::RED));
}

TEST(TestPositions, testInKingArea) {
    ASSERT_TRUE(Positions::inKingArea(Position(4, 3), Force::RED));
    ASSERT_TRUE(Positions::inKingArea(Position(6, 1), Force::RED));
    ASSERT_TRUE(Positions::inKingArea(Position(5, 8), Force::BLACK));
    ASSERT_TRUE(Positions::inForceArea(Position(4, 10), Force::BLACK));

    ASSERT_FALSE(Positions::inKingArea(Position(4, 3), Force::BLACK));
    ASSERT_FALSE(Positions::inKingArea(Position(3, 3), Force::RED));
    ASSERT_FALSE(Positions::inKingArea(Position(3, 3), Force::BLACK));
    ASSERT_FALSE(Positions::inKingArea(Position(5, 7), Force::BLACK));
    ASSERT_FALSE(Positions::inKingArea(Position(9, 10), Force::BLACK));
}

TEST(TestPositions, testDistanceInX) {
    EXPECT_EQ(Positions::xd(Position(1, 2), Position(1, 2)), 0);
    EXPECT_EQ(Positions::xd(Position(1, 2), Position(1, 5)), 0);
    EXPECT_EQ(Positions::xd(Position(1, 2), Position(3, 5)), 2);
    EXPECT_EQ(Positions::xd(Position(3, 2), Position(1, 5)), 2);
    EXPECT_EQ(Positions::xd(Position(9, 5), Position(1, 5)), 8);
}

TEST(TestPositions, testDistanceInY) {
    EXPECT_EQ(Positions::yd(Position(1, 2), Position(1, 2)), 0);
    EXPECT_EQ(Positions::yd(Position(1, 2), Position(1, 5)), 3);
    EXPECT_EQ(Positions::yd(Position(1, 2), Position(3, 5)), 3);
    EXPECT_EQ(Positions::yd(Position(3, 9), Position(1, 5)), 4);
    EXPECT_EQ(Positions::yd(Position(9, 5), Position(1, 5)), 0);
}

TEST(TestPositions, testManhattanDistance) {
    EXPECT_EQ(Positions::md(Position(1, 2), Position(1, 2)), 0);
    EXPECT_EQ(Positions::md(Position(1, 2), Position(1, 5)), 3);
    EXPECT_EQ(Positions::md(Position(1, 2), Position(3, 5)), 5);
    EXPECT_EQ(Positions::md(Position(3, 9), Position(1, 5)), 6);
    EXPECT_EQ(Positions::md(Position(9, 5), Position(1, 5)), 8);
}

TEST(TestPositions, testPositionRangeBetweenTwoPositionsInLine) {
    EXPECT_THAT(Positions::range(Position(1, 2), Position(1, 2)), ::testing::ElementsAre());
    EXPECT_THAT(Positions::range(Position(1, 2), Position(1, 3)), ::testing::ElementsAre());
    EXPECT_DEATH(Positions::range(Position(1, 2), Position(2, 3)), "");
    EXPECT_THAT(Positions::range(Position(1, 2), Position(1, 4)), ::testing::ElementsAre(Position(1, 3)));
    EXPECT_THAT(Positions::range(Position(5, 4), Position(2, 4)),
                ::testing::ElementsAre(Position(4, 4), Position(3, 4)));
    EXPECT_THAT(Positions::range(Position(5, 4), Position(5, 6)),
                ::testing::ElementsAre(Position(5, 5)));

}

TEST(TestPositions, testPositionRangeOfRowsAndColumns) {
    EXPECT_THAT(Positions::row(Position(1, 2)),
                ::testing::ElementsAre(Position(1, 2), Position(2, 2), Position(3, 2), Position(4, 2),
                                       Position(5, 2), Position(6, 2), Position(7, 2), Position(8, 2),
                                       Position(9, 2)));

    EXPECT_THAT(Positions::column(Position(4, 2)),
                ::testing::ElementsAre(Position(4, 1), Position(4, 2), Position(4, 3), Position(4, 4),
                                       Position(4, 5), Position(4, 6), Position(4, 7), Position(4, 8),
                                       Position(4, 9), Position(4, 10)));
}

TEST(TestPositions, testKnightObstacle) {
    EXPECT_EQ(Positions::knightObstacle(Position(3, 3), Position(1, 2)), Position(2, 3));
    EXPECT_EQ(Positions::knightObstacle(Position(3, 3), Position(2, 1)), Position(3, 2));
    EXPECT_EQ(Positions::knightObstacle(Position(3, 3), Position(4, 1)), Position(3, 2));
    EXPECT_EQ(Positions::knightObstacle(Position(3, 3), Position(5, 2)), Position(4, 3));
    EXPECT_EQ(Positions::knightObstacle(Position(3, 3), Position(5, 4)), Position(4, 3));
    EXPECT_EQ(Positions::knightObstacle(Position(3, 3), Position(4, 5)), Position(3, 4));
    EXPECT_EQ(Positions::knightObstacle(Position(3, 3), Position(2, 5)), Position(3, 4));
    EXPECT_EQ(Positions::knightObstacle(Position(3, 3), Position(1, 4)), Position(2, 3));
}

TEST(TestPositions, testBishopObstacle) {
    EXPECT_EQ(Positions::bishopObstacle(Position(5, 3), Position(3, 1)), Position(4, 2));
    EXPECT_EQ(Positions::bishopObstacle(Position(5, 3), Position(7, 1)), Position(6, 2));
    EXPECT_EQ(Positions::bishopObstacle(Position(5, 3), Position(7, 5)), Position(6, 4));
    EXPECT_EQ(Positions::bishopObstacle(Position(5, 3), Position(3, 5)), Position(4, 4));
}