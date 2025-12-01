#include "board.h"
#include "texture.h"

#include <algorithm>
#include <unordered_set>

bool Board::CheckShapeMovement(std::vector<TilePosition> &shape) {
  return std::ranges::any_of(shape, [&](const TilePosition &tile) {
    if ((tile.y - 1) < 0) {
      return true;
    }

    return tile.y < GRID_HEIGHT && boardStatus[tile.y - 1][tile.x].active;
  });
}

std::vector<int> Board::PlaceShape(std::vector<TilePosition> &shape) {
  std::unordered_set<int> rows;
  for (auto &tile : shape) {
    if (tile.y < 0 || tile.x < 0 || tile.x >= GRID_WIDTH) {
      continue;
    }
    boardStatus[tile.y][tile.x].active = true;
    boardStatus[tile.y][tile.x].color = tile.color;
    rows.insert(tile.y);
  }
  return {rows.begin(), rows.end()};
}

int Board::CheckRows(const std::vector<int> &affectedRows) {
  int lowestFilled = BOARD_NO_ROW_CLEARED;

  for (const int y : affectedRows) {
    if (y < 0 || y >= GRID_HEIGHT) {
      continue;
    }

    bool full = true;
    for (int x = 0; x < GRID_WIDTH; ++x) {
      if (!boardStatus[y][x].active) {
        full = false;
        break;
      }
    }

    if (full) {
      lowestFilled = (lowestFilled == BOARD_NO_ROW_CLEARED)
                         ? y
                         : std::min(lowestFilled, y);
    }
  }

  return lowestFilled;
}

std::vector<int> Board::UpdateBoard(int clearedRow) {
  for (int y = clearedRow; y < GRID_HEIGHT - 1; ++y) {
    boardStatus[y] = boardStatus[y + 1];
  }

  boardStatus[GRID_HEIGHT - 1].fill(BoardPosition{});

  // Return rows that changed (from clearedRow up to the last)
  std::vector<int> affected;
  affected.reserve(GRID_HEIGHT - clearedRow);
  for (int y = clearedRow; y < GRID_HEIGHT; ++y) {
    affected.push_back(y);
  }

  return affected;
}

void Board::Draw(SpriteRenderer &renderer, Texture &texture) {
  for (int y = 0; y < GRID_HEIGHT; ++y) {
    for (int x = 0; x < GRID_WIDTH; ++x) {
      const BoardPosition &tile = boardStatus[y][x];
      if (!tile.active) {
        continue; // skip empty tiles
      }

      renderer.DrawSprite(
          texture,
          {.position = glm::vec2(static_cast<float>(x), static_cast<float>(y)),
           .size = glm::vec2(1.0F),
           .rotate = 0.0F,
           .color = tile.color});
    }
  }
}

bool Board::CheckCollision(const std::vector<TilePosition> &tiles) const {
  return std::ranges::any_of(tiles, [&](const TilePosition &tile) {
    if (tile.x < 0 || tile.x >= GRID_WIDTH) {
      return true;
    }
    if (tile.y < 0 || tile.y >= GRID_HEIGHT) {
      return true;
    }
    return boardStatus[tile.y][tile.x].active;
  });
}
