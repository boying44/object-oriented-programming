#include "Noble.h"
#include "Warrior.h"
#include <string>
using namespace std;

namespace WarriorCraft{
  Warrior::Warrior(const string& name,  int strength): name(name), strength(strength){}
  string Warrior::getName() const {return name;}
  int Warrior::getStrength() const {return strength;}
  void Warrior::setStrength(int strength) {this->strength = strength;}
  Noble* Warrior::getNoble() const {return noble;};
  void Warrior::setNoble(Noble* noble) {this->noble = noble;};
  void Warrior::runaway(){
    noble->fire(*this);
  }
}