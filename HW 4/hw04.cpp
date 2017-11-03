//Boying Tang
//hw04.cpp
//Parse a file with a list of commands, and execute them to simulate a 
//a battle between medevial time warriors, with the addition of nobless

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Noble;

class Warrior{
public:
  Warrior(const string& name, int strength);
  string getName() const;
  int getStrength() const;
  void setStrength(int strength);
  const Noble* getNoble() const;
  void setNoble(const Noble* noble);
private:
  const string name;
  int strength;
  const Noble* noble = nullptr;
};

class Noble{
public:
  Noble(const string& name);
  string getName() const;
  bool hire(Warrior& warrior);
  void display() const;
  bool fire(Warrior& warrior);
  int getStrength() const;
  void takeDamage(float powerRatio);
  bool canBattle(const Noble& other);
  void battle(Noble& other);
private:
  const string name;
  bool alive = true; //Faster than getting strength to check if alive. 
  //Alternatively, we can check if the first warrior is alive, since if one is dead then all should be dead.
  vector<Warrior*> warriors;
};

int main() {
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

  jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	jim.display();
	lance.display();
	art.display();
	linus.display();
	billie.display();

	art.fire(cheetah);
	art.display();

  art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
  billie.battle(lance);
}

Warrior::Warrior(const string& name,  int strength): name(name), strength(strength){}
string Warrior::getName() const {return name;}
int Warrior::getStrength() const {return strength;}
void Warrior::setStrength(int strength) {this->strength = strength;}
const Noble* Warrior::getNoble() const {return noble;};
void Warrior::setNoble(const Noble* noble) {this->noble = noble;};

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