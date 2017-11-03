#include "Noble.h"
#include "Warrior.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace WarriorCraft{
  ostream& operator<<(ostream& os, const Noble& rhs){
    os << rhs.name << " has an army of " << rhs.warriors.size() << endl;
    for(const Warrior* warrior : rhs.warriors){
      os << warrior->getName() << ": " << warrior->getStrength() << endl;
    }
    return os;
  }

  Noble::Noble(const string& name): name(name){}
  string Noble::getName() const {return name;}
  //hires the warrior
  bool Noble::hire(Warrior& warrior){ 
    if (!alive){
      cout << getName() << " is dead!" << endl;
      return false;
    }
    else if (warrior.getNoble()){
      cout << "Warrior already employed." << endl;
      return false;
    }
    warrior.setNoble(this);
    warriors.push_back(&warrior);
    return true; 
  }
  void Noble::display() const {
    cout << name << " has an army of " << warriors.size() << endl;
    for(const Warrior* warrior : warriors){
      cout << warrior->getName() << ": " << warrior->getStrength() << endl;
    }
  }
  size_t findWarrior(const vector<Warrior*>& warriors, const Warrior& warrior){
    for (size_t index = 0; index < warriors.size(); index++){
      if (warriors[index]->getName() == warrior.getName()) {return index;}
    }
    return warriors.size();
  }
  bool Noble::fire(Warrior& warrior){
    if (!alive) {
      cout << getName() << " is dead!" << endl;
      return false;
    }
    int index = findWarrior(warriors, warrior);
    if (index == warriors.size() ) { 
      cout << name << " has no warrior " << warrior.getName() << endl;
      return false;
    }
    //just move everything forward
    for (index; index < warriors.size() - 1; index++){
      warriors[index] = warriors[index + 1];
    }
    //last one is empty so let's remove it
    warriors.pop_back();
    warrior.setNoble(nullptr);
    return true;
  }
  //sum of the warriors' strength
  int Noble::getStrength() const
  {
    int sum = 0;
    for (const Warrior* warrior: warriors){
      sum += warrior->getStrength();
    }
    return sum;
  }
  //recalculate warriors' strengths
  //powerRatio is a multiplier indicative of how much % strength should be left
  void Noble::takeDamage(float powerRatio){
    for(Warrior* warrior: warriors){
      warrior->setStrength(warrior->getStrength()*powerRatio);
    }
  };
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
      cout << "Mutual Annihilation: "<< getName() << " and " << other.getName() << " die at each other's hands" << endl;
      this->takeDamage(0);
      alive = false;
      other.takeDamage(0);
      other.alive =  false;
    } 
    else if (strength < otherStrength){
      cout << other.getName() << " defeats " << getName() << endl;
      powerRatio = 1 - (strength*1.0/otherStrength);
      this->takeDamage(0);
      alive = false;
      other.takeDamage(powerRatio);
    }
    else {
      cout << getName() << " defeats " << other.getName() << endl;
      powerRatio = 1 - (otherStrength*1.0/strength);
      this->takeDamage(powerRatio);
      other.takeDamage(0);
      other.alive =  false;
    }
  }
}