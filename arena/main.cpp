#include "./src/game.cpp"

int main() {
  Game instance{};
  instance.setup();

  while (instance.playing) {
    instance.runtime();
  }
}
