#pragma once

#include "board.h"
#include "sprite_renderer.h"
#include "texture.h"
#include <cstdint>
#include <functional>
#include <vector>

/// Direction constants for moving shapes
enum class MoveDirection : uint8_t {
    Left,
    Right
};

/// Function type to validate shape movements
using MoveValidator = std::function<bool(const std::vector<TilePosition> &)>;

/**
 * @brief Enum representing the 7 types of Tetris shapes.
 */
enum class ShapeType : std::uint8_t {
  I, ///< I-shaped tetromino
  O, ///< O-shaped tetromino
  T, ///< T-shaped tetromino
  S, ///< S-shaped tetromino
  Z, ///< Z-shaped tetromino
  J, ///< J-shaped tetromino
  L  ///< L-shaped tetromino
};

/**
 * @brief Represents an offset relative to the base position of a shape.
 */
struct ShapeOffset {
  /// X offset relative to the base position
  int x;

  /// Y offset relative to the base position
  int y;
};

/**
 * @brief Represents a Tetris shape (tetromino) in the game.
 *
 * Manages position, rotation, movement, and drawing of a shape.
 */
class Shape {
public:
  /**
   * @brief Constructs a Shape of a given type at an initial position.
   *
   * @param type Type of the tetromino (ShapeType).
   * @param initialX Initial X coordinate on the board.
   * @param initialY Initial Y coordinate on the board.
   */
  Shape(ShapeType type, int initialX, int initialY);

  /**
   * @brief Returns the current positions of all tiles in the shape.
   *
   * @return Vector of TilePosition representing the shape's tiles.
   */
  std::vector<TilePosition> GetTilePositions();

  /**
   * @brief Rotates the shape clockwise or counter-clockwise.
   *
   * Uses the provided MoveValidator to check if the rotation is valid.
   *
   * @param direction Rotation direction (SHAPE_DIRECTION_LEFT or
   * SHAPE_DIRECTION_RIGHT).
   * @param validator Function to validate the new tile positions.
   */
  void Rotate(MoveDirection direction, const MoveValidator &validator);

  /**
   * @brief Moves the shape left or right.
   *
   * Uses the provided MoveValidator to ensure the move is valid.
   *
   * @param direction Movement direction (SHAPE_DIRECTION_LEFT or
   * SHAPE_DIRECTION_RIGHT).
   * @param validator Function to validate the new tile positions.
   */
  void Move(MoveDirection direction, const MoveValidator &validator);

  /**
   * @brief Updates the shape position, usually for automatic falling.
   *
   * Uses the provided MoveValidator to ensure the update is valid.
   *
   * @param validator Function to validate the new tile positions.
   */
  void Update(const MoveValidator &validator);

  /**
   * @brief Draws the shape using a SpriteRenderer and a texture.
   *
   * @param renderer SpriteRenderer used to draw the tiles.
   * @param texture Texture applied to each tile.
   */
  void Draw(SpriteRenderer &renderer, Texture &texture);

private:
  TilePosition BasePosition;
  std::vector<ShapeOffset> Tiles;
};
