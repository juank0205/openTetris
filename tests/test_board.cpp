#include <gtest/gtest.h>
#include "board.h"
#include "game_constants.h"
#include <glm/glm.hpp>

// Test fixture for Board tests
class BoardTest : public ::testing::Test {
protected:
    Board board;
    
    // Helper to create a simple tile
    TilePosition createTile(int x, int y, glm::vec3 color = glm::vec3(1.0F, 0.0F, 0.0F)) {
        return TilePosition{x, y, color};
    }
    
    // Helper to create a horizontal line of tiles
    std::vector<TilePosition> createHorizontalLine(int y, glm::vec3 color = glm::vec3(1.0F, 0.0F, 0.0F)) {
        std::vector<TilePosition> tiles;
        for (int x = 0; x < GRID_WIDTH; ++x) {
            tiles.push_back(createTile(x, y, color));
        }
        return tiles;
    }
};

// Test CheckCollision with empty board
TEST_F(BoardTest, CheckCollisionEmptyBoard) {
    std::vector<TilePosition> tiles = {
        createTile(5, 10),
        createTile(5, 11),
        createTile(6, 10),
        createTile(6, 11)
    };
    
    EXPECT_FALSE(board.CheckCollision(tiles));
}

// Test CheckCollision with wall boundaries
TEST_F(BoardTest, CheckCollisionLeftWall) {
    std::vector<TilePosition> tiles = {createTile(-1, 5)};
    EXPECT_TRUE(board.CheckCollision(tiles));
}

TEST_F(BoardTest, CheckCollisionRightWall) {
    std::vector<TilePosition> tiles = {createTile(GRID_WIDTH, 5)};
    EXPECT_TRUE(board.CheckCollision(tiles));
}

TEST_F(BoardTest, CheckCollisionBottom) {
    std::vector<TilePosition> tiles = {createTile(5, -1)};
    EXPECT_TRUE(board.CheckCollision(tiles));
}

TEST_F(BoardTest, CheckCollisionTop) {
    std::vector<TilePosition> tiles = {createTile(5, GRID_HEIGHT)};
    EXPECT_TRUE(board.CheckCollision(tiles));
}

// Test CheckCollision with placed shapes
TEST_F(BoardTest, CheckCollisionWithPlacedShape) {
    // Place a shape at position (3, 2)
    std::vector<TilePosition> placedTiles = {createTile(3, 2)};
    board.PlaceShape(placedTiles);
    
    // Check collision with the same position
    std::vector<TilePosition> testTiles = {createTile(3, 2)};
    EXPECT_TRUE(board.CheckCollision(testTiles));
    
    // Check no collision with adjacent position
    testTiles = {createTile(4, 2)};
    EXPECT_FALSE(board.CheckCollision(testTiles));
}

// Test PlaceShape
TEST_F(BoardTest, PlaceShapeSingleTile) {
    std::vector<TilePosition> tiles = {createTile(5, 5)};
    std::vector<int> affectedRows = board.PlaceShape(tiles);
    
    EXPECT_EQ(affectedRows.size(), 1);
    EXPECT_EQ(affectedRows[0], 5);
    
    // Verify the tile is now on the board
    EXPECT_TRUE(board.CheckCollision(tiles));
}

TEST_F(BoardTest, PlaceShapeMultipleTiles) {
    glm::vec3 color(0.0F, 1.0F, 0.0F);
    std::vector<TilePosition> tiles = {
        createTile(3, 5, color),
        createTile(4, 5, color),
        createTile(5, 5, color),
        createTile(4, 6, color)
    };
    
    std::vector<int> affectedRows = board.PlaceShape(tiles);
    
    // Should affect rows 5 and 6
    EXPECT_EQ(affectedRows.size(), 2);
    EXPECT_TRUE(std::find(affectedRows.begin(), affectedRows.end(), 5) != affectedRows.end());
    EXPECT_TRUE(std::find(affectedRows.begin(), affectedRows.end(), 6) != affectedRows.end());
    
    // Verify all tiles are on the board
    EXPECT_TRUE(board.CheckCollision(tiles));
}

// Test PlaceShape with out-of-bounds tiles (should be ignored)
TEST_F(BoardTest, PlaceShapeIgnoresOutOfBounds) {
    std::vector<TilePosition> tiles = {
        createTile(5, 5),
        createTile(-1, 5),  // Out of bounds
        createTile(GRID_WIDTH, 5),  // Out of bounds
        createTile(5, -1)   // Out of bounds
    };
    
    std::vector<int> affectedRows = board.PlaceShape(tiles);
    
    // Only the valid tile should be placed
    EXPECT_EQ(affectedRows.size(), 1);
    EXPECT_EQ(affectedRows[0], 5);
}

// Test CheckShapeMovement with empty board
TEST_F(BoardTest, CheckShapeMovementEmptyBoard) {
    std::vector<TilePosition> tiles = {createTile(5, 5)};
    EXPECT_FALSE(board.CheckShapeMovement(tiles));
}

// Test CheckShapeMovement at bottom
TEST_F(BoardTest, CheckShapeMovementAtBottom) {
    std::vector<TilePosition> tiles = {createTile(5, 0)};
    EXPECT_TRUE(board.CheckShapeMovement(tiles));
}

// Test CheckShapeMovement with tile below
TEST_F(BoardTest, CheckShapeMovementWithTileBelow) {
    // Place a tile at (5, 3)
    std::vector<TilePosition> placedTiles = {createTile(5, 3)};
    board.PlaceShape(placedTiles);
    
    // Check if shape at (5, 4) can move down
    std::vector<TilePosition> testTiles = {createTile(5, 4)};
    EXPECT_TRUE(board.CheckShapeMovement(testTiles));
    
    // Check if shape at (5, 5) can move down (should be free)
    testTiles = {createTile(5, 5)};
    EXPECT_FALSE(board.CheckShapeMovement(testTiles));
}

// Test CheckRows with no full rows
TEST_F(BoardTest, CheckRowsNoFullRows) {
    std::vector<TilePosition> tiles = {
        createTile(0, 5),
        createTile(1, 5),
        createTile(2, 5)
    };
    board.PlaceShape(tiles);
    
    std::vector<int> affectedRows = {5};
    int clearedRow = board.CheckRows(affectedRows);
    
    EXPECT_EQ(clearedRow, BOARD_NO_ROW_CLEARED);
}

// Test CheckRows with one full row
TEST_F(BoardTest, CheckRowsSingleFullRow) {
    std::vector<TilePosition> fullRow = createHorizontalLine(5);
    board.PlaceShape(fullRow);
    
    std::vector<int> affectedRows = {5};
    int clearedRow = board.CheckRows(affectedRows);
    
    EXPECT_EQ(clearedRow, 5);
}

// Test CheckRows with multiple full rows
TEST_F(BoardTest, CheckRowsMultipleFullRows) {
    std::vector<TilePosition> row1 = createHorizontalLine(3);
    std::vector<TilePosition> row2 = createHorizontalLine(5);
    
    board.PlaceShape(row1);
    board.PlaceShape(row2);
    
    std::vector<int> affectedRows = {3, 5};
    int clearedRow = board.CheckRows(affectedRows);
    
    // Should return the lowest cleared row
    EXPECT_EQ(clearedRow, 3);
}

// Test CheckRows with partial rows
TEST_F(BoardTest, CheckRowsPartialRows) {
    std::vector<TilePosition> row1 = createHorizontalLine(3);
    std::vector<TilePosition> partialRow = {
        createTile(0, 5),
        createTile(1, 5),
        createTile(2, 5)
    };
    
    board.PlaceShape(row1);
    board.PlaceShape(partialRow);
    
    std::vector<int> affectedRows = {3, 5};
    int clearedRow = board.CheckRows(affectedRows);
    
    // Only row 3 is full
    EXPECT_EQ(clearedRow, 3);
}

// Test CheckRows with out-of-bounds rows (should be ignored)
TEST_F(BoardTest, CheckRowsIgnoresOutOfBounds) {
    std::vector<int> affectedRows = {-1, GRID_HEIGHT, 5};
    int clearedRow = board.CheckRows(affectedRows);
    
    EXPECT_EQ(clearedRow, BOARD_NO_ROW_CLEARED);
}

// Test UpdateBoard
TEST_F(BoardTest, UpdateBoardClearsRow) {
    // Place tiles in rows 3, 4, and 5
    std::vector<TilePosition> row3 = createHorizontalLine(3, glm::vec3(1.0F, 0.0F, 0.0F));
    std::vector<TilePosition> row4 = createHorizontalLine(4, glm::vec3(0.0F, 1.0F, 0.0F));
    std::vector<TilePosition> row5 = createHorizontalLine(5, glm::vec3(0.0F, 0.0F, 1.0F));
    
    board.PlaceShape(row3);
    board.PlaceShape(row4);
    board.PlaceShape(row5);
    
    // Clear row 4
    std::vector<int> affected = board.UpdateBoard(4);
    
    // Affected rows should be from 4 to top
    EXPECT_GE(affected.size(), 1);
    EXPECT_EQ(affected[0], 4);
    
    // Row 4 should now have the contents of row 5
    std::vector<TilePosition> testRow4;
    for (int x = 0; x < GRID_WIDTH; ++x) {
        testRow4.push_back(createTile(x, 4));
    }
    EXPECT_TRUE(board.CheckCollision(testRow4));
    
    // Row 5 should now have the contents of row 6 (empty)
    std::vector<TilePosition> testRow5;
    for (int x = 0; x < GRID_WIDTH; ++x) {
        testRow5.push_back(createTile(x, 5));
    }
    EXPECT_FALSE(board.CheckCollision(testRow5));
}

// Test UpdateBoard at bottom row
TEST_F(BoardTest, UpdateBoardBottomRow) {
    std::vector<TilePosition> row0 = createHorizontalLine(0);
    std::vector<TilePosition> row1 = createHorizontalLine(1);
    
    board.PlaceShape(row0);
    board.PlaceShape(row1);
    
    std::vector<int> affected = board.UpdateBoard(0);
    
    // Row 0 should now have contents of row 1
    std::vector<TilePosition> testRow0;
    for (int x = 0; x < GRID_WIDTH; ++x) {
        testRow0.push_back(createTile(x, 0));
    }
    EXPECT_TRUE(board.CheckCollision(testRow0));
}

// Integration test: Place shape, check for full row, clear it
TEST_F(BoardTest, IntegrationPlaceAndClear) {
    // Place a full row at y=2
    std::vector<TilePosition> fullRow = createHorizontalLine(2);
    std::vector<int> affectedRows = board.PlaceShape(fullRow);
    
    // Check if the row is full
    int clearedRow = board.CheckRows(affectedRows);
    EXPECT_EQ(clearedRow, 2);
    
    // Clear the row
    board.UpdateBoard(clearedRow);
    
    // Verify the row is now empty
    std::vector<TilePosition> testRow;
    for (int x = 0; x < GRID_WIDTH; ++x) {
        testRow.push_back(createTile(x, 2));
    }
    EXPECT_FALSE(board.CheckCollision(testRow));
}

// Test multiple shapes on board
TEST_F(BoardTest, MultipleShapesOnBoard) {
    // Place an L-shape
    std::vector<TilePosition> shape1 = {
        createTile(0, 0, glm::vec3(1.0F, 0.0F, 0.0F)),
        createTile(0, 1, glm::vec3(1.0F, 0.0F, 0.0F)),
        createTile(0, 2, glm::vec3(1.0F, 0.0F, 0.0F)),
        createTile(1, 0, glm::vec3(1.0F, 0.0F, 0.0F))
    };
    
    // Place a square shape
    std::vector<TilePosition> shape2 = {
        createTile(5, 5, glm::vec3(0.0F, 1.0F, 0.0F)),
        createTile(6, 5, glm::vec3(0.0F, 1.0F, 0.0F)),
        createTile(5, 6, glm::vec3(0.0F, 1.0F, 0.0F)),
        createTile(6, 6, glm::vec3(0.0F, 1.0F, 0.0F))
    };
    
    board.PlaceShape(shape1);
    board.PlaceShape(shape2);
    
    // Verify both shapes are on the board
    EXPECT_TRUE(board.CheckCollision({createTile(0, 0)}));
    EXPECT_TRUE(board.CheckCollision({createTile(5, 5)}));
    
    // Verify space between is empty
    EXPECT_FALSE(board.CheckCollision({createTile(3, 3)}));
}
