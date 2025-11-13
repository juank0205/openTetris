#include "shape.h"
#include "game_constants.h"
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

void Shape::Rotate(unsigned int direction) {
  for (auto &offset : Tiles) {
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
}

void Shape::Update() { BasePosition.y -= 1; }

void Shape::Move(unsigned int direction) {
  if (direction == SHAPE_DIRECTION_RIGHT) {
    BasePosition.x++;
    for (auto &offset : Tiles) {
      if (BasePosition.x + offset.x == GRID_WIDTH) {
        BasePosition.x--;
        break;
      }
    }
  } else {
    BasePosition.x--;
    for (auto &offset : Tiles) {
      if (BasePosition.x + offset.x < 0) {
        BasePosition.x++;
        break;
      }
    }
  }
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
