#ifndef NOBLE_H
#define NOBLE_H

#include "Protector.h"
#include <string>
#include <vector>

namespace WarriorCraft{
  class Noble{
  public:
    Noble(const std::string& name);
    std::string getName() const;
    virtual void display() const;
    virtual int getStrength() const = 0;
    virtual void takeDamage(float powerRatio) = 0;
    bool canBattle(const Noble& other);
    bool isAlive()const;
    void battle(Noble& other);
    friend std::ostream& operator<<(std::ostream& os, const Noble& rhs);
  private:
    const std::string name;
    bool alive = true; 
  };
  
  // class Lord: public Noble{
  // public:
  //   Lord(const std::string& name);
  //   void display() const;
  //   int getStrength() const;
  //   bool hires(Protector& protector);
  //   bool fire(Protector& protector);
  //   void takeDamage(float powerRatio);
  // private:
  //   std::vector<Protector*> protectors;
  // };
}

#endif