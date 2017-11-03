#ifndef NOBLE_H
#define NOBLE_H

#include "Warrior.h"
#include <string>
#include <vector>

namespace WarriorCraft{
  class Noble{
  public:
    Noble(const std::string& name);
    std::string getName() const;
    bool hire(Warrior& warrior);
    void display() const;
    bool fire(Warrior& warrior);
    int getStrength() const;
    void takeDamage(float powerRatio);
    bool canBattle(const Noble& other);
    void battle(Noble& other);
    friend std::ostream& operator<<(std::ostream& os, const Noble& rhs);
  private:
    const std::string name;
    bool alive = true; //Faster than getting strength to check if alive. 
    //Alternatively, we can check if the first warrior is alive, since if one is dead then all should be dead.
    std::vector<Warrior*> warriors;
  };
}

#endif