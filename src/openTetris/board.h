#pragma once

#include "game_constants.h"
#include "sprite_renderer.h"
#include "texture.h"

#include <array>
#include <glm/ext/vector_float3.hpp>
#include <vector>

#define BOARD_NO_ROW_CLEARED -1

struct BoardPosition {
  bool active = false;
  glm::vec3 color = glm::vec3(0.0F);
};

struct TilePosition {
  int x;
  int y;
  glm::vec3 color;
};

class Board {
public:
  bool CheckShapeMovement(std::vector<TilePosition> &shape);
  std::vector<int> PlaceShape(std::vector<TilePosition> &shape);
  int CheckRows(const std::vector<int> &affectedRows);
  std::vector<int> UpdateBoard(int clearedRow = BOARD_NO_ROW_CLEARED);

  void Draw(SpriteRenderer &renderer, Texture &texture);
  [[nodiscard]] bool CheckCollision(const std::vector<TilePosition> &tiles) const;
private:
  std::array<std::array<BoardPosition, GRID_WIDTH>, GRID_HEIGHT> boardStatus;
};
