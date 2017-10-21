#include <board.h>
#include <gtest/gtest.h>
#include <position.h>
#include <positions.h>

TEST(TestBoard, testPlaceAPiece) {
    auto position = Position(1, 2);
    auto board = Board();
    Piece *const piece = new Piece{Force::RED, Kind::ROOK, {5, 5}};
    board.place(piece, position);
    EXPECT_EQ(piece->position(), Position(1, 2));
    EXPECT_EQ(board.piece(position), piece);
}

TEST(TestBoard, testAPositionIsEmptyOrNot) {
    auto position = Position(1, 2);
    auto board = Board();
    Piece *const piece = new Piece{Force::RED, Kind::ROOK, {5, 5}};
    EXPECT_TRUE(board.empty(position));
    board.place(piece, position);
    EXPECT_TRUE(board.occupied(position));
}

TEST(TestBoard, testPieceCountInRange) {
    auto position = Position(2, 2);
    auto board = Board();
    Piece *const piece = new Piece{Force::RED, Kind::ROOK, {5, 5}};
    auto range = Positions::range({1, 2}, {5, 2});

    EXPECT_EQ(board.count(range), 0);
    board.place(piece, position);
    EXPECT_EQ(board.count(range), 1);
}

TEST(TestBoard, testSelectPiecesMatchSpecifiedCondition) {
    auto position = Position(2, 2);
    auto board = Board();
    Piece *const redRook = new Piece{Force::RED, Kind::ROOK, {5, 5}};
    Piece *const redKnight = new Piece{Force::RED, Kind::KNIGHT, {5, 1}};
    Piece *const blackRook = new Piece{Force::BLACK, Kind::ROOK, {5, 2}};
    Piece *const blackKnight = new Piece{Force::BLACK, Kind::KNIGHT, {3, 5}};
    auto range = Positions::range({1, 2}, {5, 2});
    board.place(redRook);
    board.place(redKnight);
    board.place(blackRook);
    board.place(blackKnight);

    const std::list<Piece *> &list =
        board.select([](auto piece) { return piece->kind() == Kind::ROOK; });
    EXPECT_EQ(list.size(), 2);
    EXPECT_TRUE(contains(list, redRook));
    EXPECT_TRUE(contains(list, blackRook));
}

TEST(TestBoard, testSelectOnePieceMatchSpecifiedCondition) {
    auto position = Position(2, 2);
    auto board = Board();
    Piece *const redRook = new Piece{Force::RED, Kind::ROOK, {5, 5}};
    Piece *const redKnight = new Piece{Force::RED, Kind::KNIGHT, {5, 1}};
    Piece *const blackRook = new Piece{Force::BLACK, Kind::ROOK, {5, 2}};
    Piece *const blackKnight = new Piece{Force::BLACK, Kind::KNIGHT, {3, 5}};
    auto range = Positions::range({1, 2}, {5, 2});
    board.place(redRook);
    board.place(redKnight);
    board.place(blackRook);
    board.place(blackKnight);

    auto piece = board.selectOne([](auto piece) {
        return piece->kind() == Kind::KNIGHT && piece->force() == Force::BLACK;
    });
    EXPECT_EQ(piece, blackKnight);
}

TEST(TestBoard, testMakeEmpty) {
    auto board = Board();
    Piece *const redRook = new Piece{Force::RED, Kind::ROOK, {5, 5}};
    board.place(redRook);
    board.makeEmpty({5, 5});
    EXPECT_EQ(board.piece({5, 5}), nullptr);
}
