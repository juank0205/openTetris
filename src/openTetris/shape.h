#pragma once

#include "board.h"
#include "sprite_renderer.h"
#include "texture.h"
#include <vector>

#define SHAPE_DIRECTION_LEFT 0
#define SHAPE_DIRECTION_RIGHT 1

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
  void Rotate(unsigned int direction);
  void Move(unsigned int direction);
  void Update();

  void Draw(SpriteRenderer &renderer, Texture &texture);
};
