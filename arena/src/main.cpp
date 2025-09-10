#include "game.h"

int main() {
  Game instance{};
  instance.setup();

  while (instance.playing) {
    instance.runtime();
  }
}
