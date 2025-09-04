#include <string>
#include <vector>

struct Damage {
  float health{};
  std::string origin{};
};

struct Character {
  float health = 10.0;
  float level = 0.0;

  std::vector<Damage> damage_taken = {};
};
