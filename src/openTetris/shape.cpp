#include "shape.h"
#include "board.h"
#include "texture.h"

#include <glm/glm.hpp>
#include <vector>

Shape::Shape(ShapeType type, int initialX, int initialY) {
   glm::vec3 color = { 0, 0, 0 };
  switch (type) {
  case ShapeType::I:
    tiles = {{.x = 0, .y = 0},
             {.x = 0, .y = -1},
             {.x = 0, .y = 1},
             {.x = 0, .y = 2}};
    color = glm::vec3(0.0F, 1.0F, 1.0F); // Cyan
    break;
  case ShapeType::O:
    tiles = {{.x = 0, .y = 0},
             {.x = 1, .y = 0},
             {.x = 0, .y = -1},
             {.x = 1, .y = -1}};
    color = glm::vec3(1.0F, 1.0F, 0.0F); // Yellow
    break;
  case ShapeType::T:
    tiles = {{.x = 0, .y = 0},
             {.x = -1, .y = 0},
             {.x = 1, .y = 0},
             {.x = 0, .y = -1}};
    color = glm::vec3(0.6F, 0.0F, 0.6F); // Purple NOLINT
    break;
  case ShapeType::S:
    tiles = {{.x = 0, .y = 0},
             {.x = 1, .y = 0},
             {.x = 0, .y = -1},
             {.x = -1, .y = -1}};
    color = glm::vec3(0.0F, 1.0F, 0.0F); // Green
    break;
  case ShapeType::Z:
    tiles = {{.x = 0, .y = 0},
             {.x = -1, .y = 0},
             {.x = 0, .y = -1},
             {.x = 1, .y = -1}};
    color = glm::vec3(1.0F, 0.0F, 0.0F); // Red
    break;
  case ShapeType::J:
    tiles = {{.x = 0, .y = 0},
             {.x = 0, .y = -1},
             {.x = 0, .y = 1},
             {.x = -1, .y = 1}};
    color = glm::vec3(0.0F, 0.0F, 1.0F); // Blue
    break;
  case ShapeType::L:
    tiles = {{.x = 0, .y = 0},
             {.x = 0, .y = -1},
             {.x = 0, .y = 1},
             {.x = 1, .y = 1}};
    color = glm::vec3(1.0F, 0.5F, 0.0F); // Orange NOLINT
    break;
  }
  basePosition = {.x = initialX, .y = initialY, .color = color};
  this->type = type;
}

std::vector<TilePosition> Shape::GetTilePositions() {
  std::vector<TilePosition> tilesPos;
  tilesPos.reserve(tiles.size());

  for (auto &offset : tiles) {
    TilePosition t;
    t.x = basePosition.x + offset.x;
    t.y = basePosition.y + offset.y;
    t.color = basePosition.color;
    tilesPos.push_back(t);
  }

  return tilesPos;
}

void Shape::Rotate(MoveDirection direction, const MoveValidator &validator) {
  std::vector<ShapeOffset> newOffsets = tiles;

  for (auto &offset : newOffsets) {
    const int oldX = offset.x;
    const int oldY = offset.y;
    if (direction == MoveDirection::Right) {
      offset.x = oldY;
      offset.y = -oldX;
    } else {
      offset.x = -oldY;
      offset.y = oldX;
    }
  }

  // Predict new positions
  std::vector<TilePosition> newPositions;
  newPositions.reserve(newOffsets.size());
  for (auto &offset : newOffsets) {
    newPositions.push_back({.x = basePosition.x + offset.x,
                            .y = basePosition.y + offset.y,
                            .color = basePosition.color});
  }

  if (!validator(newPositions)) {
    return;
  }

  tiles = newOffsets;
}

void Shape::Update(const MoveValidator &validator) {
  TilePosition newBase = basePosition;
  newBase.y--;
  std::vector<TilePosition> newPositions;
  newPositions.reserve(tiles.size());
  for (auto &offset : tiles) {
    newPositions.push_back({.x = newBase.x + offset.x,
                            .y = newBase.y + offset.y,
                            .color = basePosition.color});
  }

  // Validate move
  if (!validator(newPositions)) {
    return;
  }
  // Commit move
  basePosition = newBase;
}

void Shape::Move(MoveDirection direction, const MoveValidator &validator) {
  TilePosition newBase = basePosition;

  if (direction == MoveDirection::Right) {
    newBase.x++;
  } else if (direction == MoveDirection::Left) {
    newBase.x--;
  }

  // Predict new positions
  std::vector<TilePosition> newPositions;
  newPositions.reserve(tiles.size());
  for (auto &offset : tiles) {
    newPositions.push_back({.x = newBase.x + offset.x,
                            .y = newBase.y + offset.y,
                            .color = basePosition.color});
  }

  // Validate move
  if (!validator(newPositions)) {
    return;
  }
  // Commit move
  basePosition = newBase;
}

void Shape::Draw(SpriteRenderer &renderer, Texture &texture) {
  for (const auto &offset : tiles) {
    const glm::vec2 pos(static_cast<float>(basePosition.x + offset.x),
                        static_cast<float>(basePosition.y + offset.y));

    renderer.DrawSprite(texture,          // texture of the shape
                        {.position = pos, // position in grid coordinates
                         .size = glm::vec2(1.0F),     // size of one tile
                         .rotate = 0.0F,              // rotation
                         .color = basePosition.color} // tile color
    );
  }
}
