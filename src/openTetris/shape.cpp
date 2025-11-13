#include "shape.h"
#include "board.h"
#include "texture.h"

Shape::Shape(ShapeType type, int initialX, int initialY) {
  glm::vec3 color;
  switch (type) {
  case ShapeType::I:
    Tiles = {{0, 0}, {0, -1}, {0, 1}, {0, 2}};
    color = glm::vec3(0.0f, 1.0f, 1.0f); // Cyan
    break;
  case ShapeType::O:
    Tiles = {{0, 0}, {1, 0}, {0, -1}, {1, -1}};
    color = glm::vec3(1.0f, 1.0f, 0.0f); // Yellow
    break;
  case ShapeType::T:
    Tiles = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}};
    color = glm::vec3(0.6f, 0.0f, 0.6f); // Purple
    break;
  case ShapeType::S:
    Tiles = {{0, 0}, {1, 0}, {0, -1}, {-1, -1}};
    color = glm::vec3(0.0f, 1.0f, 0.0f); // Green
    break;
  case ShapeType::Z:
    Tiles = {{0, 0}, {-1, 0}, {0, -1}, {1, -1}};
    color = glm::vec3(1.0f, 0.0f, 0.0f); // Red
    break;
  case ShapeType::J:
    Tiles = {{0, 0}, {0, -1}, {0, 1}, {-1, 1}};
    color = glm::vec3(0.0f, 0.0f, 1.0f); // Blue
    break;
  case ShapeType::L:
    Tiles = {{0, 0}, {0, -1}, {0, 1}, {1, 1}};
    color = glm::vec3(1.0f, 0.5f, 0.0f); // Orange
    break;
  }
  BasePosition = {initialX, initialY, color};
}

std::vector<TilePosition> Shape::GetTilePositions() {
  std::vector<TilePosition> tilesPos;
  tilesPos.reserve(Tiles.size());

  for (auto &offset : Tiles) {
    TilePosition t;
    t.x = BasePosition.x + offset.x;
    t.y = BasePosition.y + offset.y;
    t.color = BasePosition.color;
    tilesPos.push_back(t);
  }

  return tilesPos;
}

void Shape::Rotate(unsigned int direction, MoveValidator validator) {
  std::vector<ShapeOffset> newOffsets = Tiles;

  for (auto &offset : newOffsets) {
    int oldX = offset.x;
    int oldY = offset.y;
    if (direction == SHAPE_DIRECTION_RIGHT) {
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
    newPositions.push_back({BasePosition.x + offset.x,
                            BasePosition.y + offset.y, BasePosition.color});
  }

  if (!validator(newPositions))
    return;

  Tiles = newOffsets;
}

void Shape::Update(MoveValidator validator) {
  TilePosition newBase = BasePosition;
  newBase.y--;
  std::vector<TilePosition> newPositions;
  newPositions.reserve(Tiles.size());
  for (auto &offset : Tiles) {
    newPositions.push_back(
        {newBase.x + offset.x, newBase.y + offset.y, BasePosition.color});
  }

  // Validate move
  if (!validator(newPositions))
    return;
  // Commit move
  BasePosition = newBase;
}

void Shape::Move(unsigned int direction, MoveValidator validator) {
  TilePosition newBase = BasePosition;

  if (direction == SHAPE_DIRECTION_RIGHT)
    newBase.x++;
  else if (direction == SHAPE_DIRECTION_LEFT)
    newBase.x--;

  // Predict new positions
  std::vector<TilePosition> newPositions;
  newPositions.reserve(Tiles.size());
  for (auto &offset : Tiles) {
    newPositions.push_back(
        {newBase.x + offset.x, newBase.y + offset.y, BasePosition.color});
  }

  // Validate move
  if (!validator(newPositions))
    return;
  // Commit move
  BasePosition = newBase;
}

void Shape::Draw(SpriteRenderer &renderer, Texture &texture) {
  for (const auto &offset : Tiles) {
    glm::vec2 pos(static_cast<float>(BasePosition.x + offset.x),
                  static_cast<float>(BasePosition.y + offset.y));

    renderer.DrawSprite(
        texture,           // texture of the shape
        pos,               // position in grid coordinates
        glm::vec2(1.0f),   // size of one tile (can be scaled later)
        0.0f,              // rotation
        BasePosition.color // tile color
    );
  }
}
