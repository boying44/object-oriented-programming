#ifndef WARRIOR_H
#define WARRIOR_H

#include <string>

namespace WarriorCraft{
  class Noble;
  class Warrior{
  public:
    Warrior(const std::string& name, int strength);
    std::string getName() const;
    int getStrength() const;
    void setStrength(int strength);
    Noble* getNoble() const;
    void setNoble(Noble* noble);
    void runaway();
  private:
    const std::string name;
    int strength;
    Noble* noble = nullptr;
  };
}

#endif