#pragma once

#include "board.h"
#include "sprite_renderer.h"
#include "texture.h"
#include <vector>

#define SHAPE_DIRECTION_LEFT 0
#define SHAPE_DIRECTION_RIGHT 1

#include <functional>

using MoveValidator = std::function<bool(const std::vector<TilePosition>&)>;

enum class ShapeType { I, O, T, S, Z, J, L };

struct ShapeOffset {
  int x;
  int y;
};

class Shape {
public:
  Shape(ShapeType type, int initialX, int initialY);
  Shape() {};

  TilePosition BasePosition;
  std::vector<ShapeOffset> Tiles;

  std::vector<TilePosition> GetTilePositions();
  void Rotate(unsigned int direction, MoveValidator validator);
  void Move(unsigned int direction, MoveValidator validator);
  void Update(MoveValidator validator);

  void Draw(SpriteRenderer &renderer, Texture &texture);
};
