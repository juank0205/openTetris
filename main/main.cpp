// #include "app.h"
#include "game.h"
#include <cstdint>
#include <iostream>

enum class WindowDimensions : std::uint16_t { height = 600, width = 800 };

int main() {
  // App app;
  // app.run();
  Game game(static_cast<int>(WindowDimensions::width),
            static_cast<int>(WindowDimensions::height), "Lets go");
  game.Setup();
  game.Run();
  std::cin.get();
}
