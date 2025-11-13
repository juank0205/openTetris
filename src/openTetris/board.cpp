#include "board.h"
#include "texture.h"

#include <unordered_set>

bool Board::CheckShapeMovement(std::vector<TilePosition> &shape) {
  for (auto &tile : shape) {
    if ((tile.y - 1) < 0)
      return true; // touching or out of bounds

    if (tile.y < GRID_HEIGHT && BoardStatus[tile.y - 1][tile.x].active) {
      return true; // collided with existing tile
    }
  }

  return false;
}

std::vector<int> Board::PlaceShape(std::vector<TilePosition> &shape) {
  std::unordered_set<int> rows;
  for (auto &tile : shape) {
    if (tile.y < 0 || tile.x < 0 ||
        tile.x >= GRID_WIDTH)
      continue;
    BoardStatus[tile.y][tile.x].active = true;
    BoardStatus[tile.y][tile.x].color = tile.color;
    rows.insert(tile.y);
  }
  return {rows.begin(), rows.end()};
}

int Board::CheckRows(const std::vector<int> &affectedRows) {
  int lowestFilled = BOARD_NO_ROW_CLEARED;

  for (int y : affectedRows) {
    if (y < 0 || y >= GRID_HEIGHT)
      continue;

    bool full = true;
    for (int x = 0; x < GRID_WIDTH; ++x) {
      if (!BoardStatus[y][x].active) {
        full = false;
        break;
      }
    }

    if (full)
      lowestFilled = (lowestFilled == BOARD_NO_ROW_CLEARED)
                         ? y
                         : std::min(lowestFilled, y);
  }

  return lowestFilled;
}

std::vector<int> Board::UpdateBoard(int clearedRow) {
  for (int y = clearedRow; y < GRID_HEIGHT - 1; ++y)
    BoardStatus[y] = BoardStatus[y + 1];

  BoardStatus[GRID_HEIGHT - 1].fill(BoardPosition{});

  // Return rows that changed (from clearedRow up to the last)
  std::vector<int> affected;
  affected.reserve(GRID_HEIGHT - clearedRow);
  for (int y = clearedRow; y < GRID_HEIGHT; ++y)
    affected.push_back(y);

  return affected;
}

void Board::Draw(SpriteRenderer &renderer, Texture &texture) {
  for (int y = 0; y < GRID_HEIGHT; ++y) {
    for (int x = 0; x < GRID_WIDTH; ++x) {
      const BoardPosition &tile = BoardStatus[y][x];
      if (!tile.active)
        continue; // skip empty tiles

      renderer.DrawSprite(
          texture, glm::vec2(static_cast<float>(x), static_cast<float>(y)),
          glm::vec2(1.0f), // one tile
          0.0f, tile.color);
    }
  }
}

bool Board::CheckCollision(const std::vector<TilePosition> &tiles) const {
    for (auto &tile : tiles) {
        if (tile.x < 0 || tile.x >= GRID_WIDTH) return true;
        if (tile.y < 0 || tile.y >= GRID_HEIGHT) return true;
        if (BoardStatus[tile.y][tile.x].active) return true;
    }
    return false;
}
