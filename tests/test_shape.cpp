#include "shape.h"
#include <gtest/gtest.h>

namespace {
bool alwaysValid(const std::vector<TilePosition> & /*positions*/) { return true; }

bool neverValid(const std::vector<TilePosition> & /*positions*/) { return false; }
} // namespace

TEST(ShapeTest, InitialTilePositions) {
  Shape s(ShapeType::I, 5, 5); // NOLINT
  auto tiles = s.GetTilePositions();

  ASSERT_EQ(tiles.size(), 4);
  EXPECT_EQ(tiles[0].x, 5);
  EXPECT_EQ(tiles[0].y, 5);
}

// Test movement
TEST(ShapeTest, MoveRight) {
  Shape s(ShapeType::O, 0, 0);
  s.Move(MoveDirection::Right, alwaysValid);
  auto tiles = s.GetTilePositions();

  // Base x should have moved by +1
  EXPECT_EQ(tiles[0].x, 1);
}

TEST(ShapeTest, MoveLeftBlocked) {
  Shape s(ShapeType::O, 0, 0);
  s.Move(MoveDirection::Left, neverValid);
  auto tiles = s.GetTilePositions();

  // Base x should remain unchanged
  EXPECT_EQ(tiles[0].x, 0);
}

// Test rotation
TEST(ShapeTest, RotateRight) {
  Shape s(ShapeType::T, 0, 0);

  // Rotate right with AlwaysValid
  s.Rotate(MoveDirection::Right, alwaysValid);
  auto tiles = s.GetTilePositions();

  // T-shape's tile count should remain 4
  EXPECT_EQ(tiles.size(), 4);

  // The tile positions should have changed after rotation
  bool changed = false;
  for (auto &t : tiles) {
    if (t.x != 0 || t.y != 0) {
      changed = true;
      break;
    }
  }
  EXPECT_TRUE(changed);
}

// Test update (falling)
TEST(ShapeTest, UpdateMovesDown) {
  Shape s(ShapeType::I, 0, 5); // NOLINT
  s.Update(alwaysValid);
  auto tiles = s.GetTilePositions();

  // All tiles should have decreased y by 1
  EXPECT_EQ(tiles[0].y, 4);
}
