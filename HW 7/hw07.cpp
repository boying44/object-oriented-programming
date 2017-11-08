#include "Noble.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;
using namespace WarriorCraft;

class Protector;

class Lord: public Noble{
public:
  Lord(const std::string& name);
  void display() const;
  int getStrength() const;
  bool hires(Protector& protector);
  bool fire(Protector& protector);
  void takeDamage(float powerRatio);
private:
  std::vector<Protector*> protectors;
};

class PersonWithStrengthToFight: public Noble{
public:
  PersonWithStrengthToFight(const std::string& name, int strength);
  int getStrength() const;
  void takeDamage(float powerRatio);
private:
  int strength;
};

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
  Swordsman(const string& name,  int strength);
  void takeDamage(int strength);
};

int main() {
  Lord sam("Sam");
  Archer samantha("Samantha", 200);
  sam.hires(samantha);
  Lord joe("Joe");
  PersonWithStrengthToFight randy("Randolf the Elder", 250); 	
  joe.battle(randy);	
  joe.battle(sam);	
  Lord janet("Janet");	
  Swordsman hardy("TuckTuckTheHardy", 100);
  Swordsman stout("TuckTuckTheStout", 80);
  janet.hires(hardy);	
  janet.hires(stout);	
  PersonWithStrengthToFight barclay("Barclay the Bold", 300);	
  janet.battle(barclay);	
  janet.hires(samantha);	
  Archer pethora("Pethora", 50);	
  Archer thora("Thorapleth", 60);
  Wizard merlin("Merlin", 150);
  janet.hires(pethora);
  janet.hires(thora);
  sam.hires(merlin);
  janet.battle(barclay);	
  sam.battle(barclay);	
  joe.battle(barclay);
}

Protector::Protector(const string& name,  int strength): name(name), strength(strength){}
string Protector::getName() const {return name;}
int Protector::getStrength() const {return strength;}
void Protector::takeDamage(int strength) {this->strength = strength;}
Lord* Protector::getLord() const {return lord;};
void Protector::setLord(Lord* lord) {this->lord = lord;};
void Protector::runaway(){
  lord->fire(*this);
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
