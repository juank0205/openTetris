// #include "app.h"
#include "game.h"

int main(int argc, char *argv[]) {
  // App app;
  // app.run();
  Game game(800, 600, "Lets go");
  game.Setup();
  game.Run();
}
