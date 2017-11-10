#include "Noble.h"
#include "Protector.h"
#include <string>
#include <iostream>
using namespace std;

namespace WarriorCraft{
  Protector::Protector(const string& name,  int strength): name(name), strength(strength){}
  string Protector::getName() const {return name;}
  int Protector::getStrength() const {return strength;}
  void Protector::takeDamage(int strength) {this->strength = strength;}
  Lord* Protector::getLord() const {return lord;};
  void Protector::setLord(Lord* lord) {this->lord = lord;};
  void Protector::runaway(){
    lord->fire(*this);
  }

  Wizard::Wizard(const string& name, int strength): Protector(name, strength){}
  Warrior::Warrior(const string& name, int strength): Protector(name, strength){}
  Archer::Archer(const string& name, int strength): Warrior(name, strength){}
  Swordsman::Swordsman(const string& name,  int strength): Warrior(name, strength){}
  
  void Wizard::takeDamage(int strength){
    Protector::takeDamage(strength);
    cout << "POOF!" << endl;
  }
  void Archer::takeDamage(int strength){
    Protector::takeDamage(strength);
    cout << "TWANG! " << getName() << " says: Take that in the name of my lord, " << getLord()->getName() << endl;
  }
  void Swordsman::takeDamage(int strength){
    Protector::takeDamage(strength);
    cout << "CLANG! " << getName() << " says: Take that in the name of my lord, " << getLord()->getName() << endl;
  }
}