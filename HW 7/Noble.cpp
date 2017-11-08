#include "Noble.h"
#include "Protector.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace WarriorCraft{
  ostream& operator<<(ostream& os, const Noble& rhs){
    rhs.display();
    // os << rhs.name << " has an army of " << rhs.protectors.size() << endl;
    // for(const Protector* protector : rhs.protectors){
    //   os << protector->getName() << ": " << protector->getStrength() << endl;
    // }
    return os;
  }
  
  Noble::Noble(const string& name): name(name){}
  string Noble::getName() const {return name;}
  //hires the protector
  void Noble::display() const {
    cout << name << endl;
  }
  //are the Nobles alive?
  bool Noble::canBattle(const Noble& other){
    if (!alive && !other.alive){
      cout << "Oh, NO! They're both dead! Yuck!" << endl;
      return false;
    }
    else if (!alive){
      cout << "He's dead, " << other.getName() << endl;
      return false;
    }
    else if (!other.alive){
      cout << "He's dead, " << getName() << endl;
      return false;
    }
    return true;
  }
  void Noble::battle(Noble& other){
    cout << getName() << " battles " << other.getName() << endl; 
    if (!canBattle(other)) {return;}
    int strength = getStrength();
    int otherStrength = other.getStrength();
    float powerRatio; //multiplier for taking damage
    if (strength == otherStrength){
      this->takeDamage(0);
      alive = false;
      other.takeDamage(0);
      other.alive =  false;
      cout << "Mutual Annihilation: "<< getName() << " and " << other.getName() << " die at each other's hands" << endl;
    } 
    else if (strength < otherStrength){
      powerRatio = 1 - (strength*1.0/otherStrength);
      this->takeDamage(0);
      alive = false;
      other.takeDamage(powerRatio);
      cout << other.getName() << " defeats " << getName() << endl;
    }
    else {
      powerRatio = 1 - (otherStrength*1.0/strength);
      this->takeDamage(powerRatio);
      other.takeDamage(0);
      other.alive =  false;
      cout << getName() << " defeats " << other.getName() << endl;
    }
  }
  bool Noble::isAlive() const{
    return alive;
  }
}