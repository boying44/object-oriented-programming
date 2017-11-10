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

  size_t findProtector(const vector<Protector*>& protectors, const Protector& protector){
    for (size_t index = 0; index < protectors.size(); index++){
      if (protectors[index]->getName() == protector.getName()) {return index;}
    }
    return protectors.size();
  }
  //recalculate protectors' strengths
  //powerRatio is a multiplier indicative of how much % strength should be left
  void Lord::takeDamage(float powerRatio){
    for(Protector* protector: protectors){
      protector->takeDamage(protector->getStrength()*powerRatio);
    }
  };
  //sum of the protectors' strength
  int Lord::getStrength() const
  {
    int sum = 0;
    for (const Protector* protector: protectors){
      sum += protector->getStrength();
    }
    return sum;
  }
  void Lord::display() const {
    Noble::display();
    cout  << " has an army of " << protectors.size() << endl;
    for(const Protector* protector : protectors){
      cout << protector->getName() << ": " << protector->getStrength() << endl;
    }
  }
  bool Lord::fire(Protector& protector){
    if (!isAlive()) {
      cout << getName() << " is dead!" << endl;
      return false;
    }
    int index = findProtector(protectors, protector);
    if (index == protectors.size() ) { 
      cout << getName() << " has no protector " << protector.getName() << endl;
      return false;
    }
    //just move everything forward
    for (index; index < protectors.size() - 1; index++){
      protectors[index] = protectors[index + 1];
    }
    //last one is empty so let's remove it
    protectors.pop_back();
    protector.setLord(nullptr);
    return true;
  }
  bool Lord::hires(Protector& protector){ 
    if (!isAlive()){
      cout << getName() << " is dead!" << endl;
      return false;
    }
    else if (protector.getLord()){
      cout << "Protector already employed." << endl;
      return false;
    }
    protector.setLord(this);
    protectors.push_back(&protector);
    return true; 
  }

  void PersonWithStrengthToFight::takeDamage(float powerRatio){
    strength*=powerRatio;
  }
  int PersonWithStrengthToFight::getStrength() const
  {
    return strength;
  }
  Lord::Lord(const string& name): Noble(name){}
  PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name, int strength ): Noble(name), strength(strength){}
  
}