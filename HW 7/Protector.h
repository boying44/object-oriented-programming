#ifndef PROTECTOR_H
#define PROTECTOR_H

#include <string>

namespace WarriorCraft{
  class Lord;
  class Protector{
  public:
    Protector(const std::string& name, int strength);
    std::string getName() const;
    int getStrength() const;
    virtual void takeDamage(int strength);
    Lord* getLord() const;
    void setLord(Lord* lord);
    void runaway();
  private:
    const std::string name;
    int strength;
    Lord* lord = nullptr;
  };

  class Wizard : public Protector{
  public:
    Wizard(const std::string& name, int strength);
    void takeDamage(int strength);
  };
  
  class Warrior : public Protector{
  public:
    Warrior(const std::string& name, int strength);
  };
  
  class Archer : public Warrior{
  public:
    Archer(const std::string& name, int strength);
    void takeDamage(int strength);
  };
  
  class Swordsman : public Warrior{
  public:
    Swordsman(const std::string& name,  int strength);
    void takeDamage(int strength);
  };
}

#endif