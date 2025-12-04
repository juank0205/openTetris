#pragma once

#include "game_constants.h"
#include "sprite_renderer.h"
#include "texture.h"

#include <glm/ext/vector_float3.hpp>
#include <vector>
#include <array>

/// Returned by UpdateBoard / CheckRows when no rows were cleared
constexpr int BOARD_NO_ROW_CLEARED = -1;

/**
 * @brief Represents the state of a single board cell.
 *
 * Indicates whether a tile is active and stores its color.
 */
struct BoardPosition {
    /// Whether this cell is currently occupied by a tile
    bool active = false;

    /// Color of the tile in this cell (RGB)
    glm::vec3 color = glm::vec3(0.0F);
};

/**
 * @brief Represents the position and color of a single tile in the game.
 */
struct TilePosition {
    /// X coordinate on the board
    int x;

    /// Y coordinate on the board
    int y;

    /// Color of the tile
    glm::vec3 color;
};

/**
 * @brief Represents the Tetris board and handles game logic.
 *
 * Manages tile placement, shape movement, collision checks, and row clearing.
 */
class Board {
public:

    /**
     * @brief Checks whether a shape can move to the given tile positions.
     *
     * @param shape Vector of tile positions representing the shape.
     * @return true if the shape can move without collisions, false otherwise.
     */
    bool CheckShapeMovement(std::vector<TilePosition> &shape);

    /**
     * @brief Places a shape on the board and returns affected rows.
     *
     * Updates the board state with the shape's tiles.
     *
     * @param shape Vector of tile positions representing the shape.
     * @return Vector of row indices that were affected by the placement.
     */
    std::vector<int> PlaceShape(std::vector<TilePosition> &shape);

    /**
     * @brief Checks for completed rows in the affected rows.
     *
     * @param affectedRows Vector of row indices to check.
     * @return The index of the row cleared, or BOARD_NO_ROW_CLEARED if none.
     */
    int CheckRows(const std::vector<int> &affectedRows);

    /**
     * @brief Updates the board after clearing a row.
     * Shifts down tiles above the cleared row.
     *
     * @param clearedRow Index of the row that was cleared (optional).
     * @return Vector of indices of rows that were affected/updated.
     */
    std::vector<int> UpdateBoard(int clearedRow = BOARD_NO_ROW_CLEARED);

    /**
     * @brief Draws the current board state using a SpriteRenderer and texture.
     *
     * @param renderer SpriteRenderer used to draw tiles.
     * @param texture Texture applied to each tile.
     */
    void Draw(SpriteRenderer &renderer, Texture &texture);

    /**
     * @brief Checks for collisions of a set of tiles with the board boundaries or active tiles.
     *
     * @param tiles Vector of tile positions to check.
     * @return true if any collision occurs, false otherwise.
     */
    [[nodiscard]] bool CheckCollision(const std::vector<TilePosition> &tiles) const;

private:
    std::array<std::array<BoardPosition, GRID_WIDTH>, GRID_HEIGHT> boardStatus;
};

