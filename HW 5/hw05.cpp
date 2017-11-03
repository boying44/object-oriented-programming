//Boying Tang
//hw04.cpp
//Parse a file with a list of commands, and execute them to simulate a 
//a battle between medevial time warriors, with instances created on the heap

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
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
  void display() const;
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
  bool fire(const string& warrior);
  int getStrength() const;
  void takeDamage(float powerRatio);
  bool canBattle(const Noble& other);
  void battle(Noble& other);
private:
  const string name;
  bool alive = true;
  vector<Warrior*> warriors;
};
size_t findNoble(const vector<Noble*>& nobles, const string& noble);
size_t findWarrior(const vector<Warrior*>& warriors, const string& warrior);

int main(){
  fstream file("nobleWarriors.txt");

  if(!file){
    cerr << "failed to open file";
    return 1;
  }

  vector<Warrior*> warriors;
  vector<Noble*> nobles;

  string command;
  string name1;
  string name2;
  int strength;
  while (file >> command){
    if(command == "Noble"){
      file >> name1;
      if (findNoble(nobles, name1) != nobles.size()){
        cerr << "Noble with same name already exist";
        return 1;
      }
      nobles.push_back(new Noble(name1));
    }
    else if(command == "Warrior"){
      file >> name1 >> strength;
      if (findWarrior(warriors, name1) == warriors.size()){
        cerr << "Warrior with same name already exist";
        return 1;
      }
      warriors.push_back(new Warrior(name1, strength));
    }
    else if(command == "Status"){
      cout << "Status =========================" << endl;
      cout << "Nobles:" << endl;
      if (nobles.size() == 0){
        cout << "NONE" << endl;
      }
      for(const Noble* noble: nobles){
        noble->display();
      }
      cout << "Unemployed Warriors:" << endl;
      bool unemployed = false;
      for(const Warrior* warrior: warriors){
        if(warrior->getNoble() == nullptr){
          warrior->display();
          unemployed++;
        }
      }
      if (unemployed == 0){
        cout << "NONE" << endl;
      }
    }
    else if(command == "Hire"){
      file >> name1 >> name2;
      size_t nobleIndex = findNoble(nobles, name1);
      size_t warriorIndex = findWarrior(warriors, name2);
      if (nobleIndex == nobles.size()){
        cerr << name1 << "not found" << endl;
        return 1;
      }
      if (warriorIndex == warriors.size()){
        cerr << name2 << "not found" << endl;
        return 1;
      }
      nobles[nobleIndex]->hire(*warriors[warriorIndex]);
    }
    else if(command == "Battle"){
      file >> name1 >> name2;
      size_t noble1Index = findNoble(nobles, name1);
      size_t noble2Index = findNoble(nobles, name2);
      if (noble1Index == nobles.size()){
        cout << name1 << "not found" << endl;
        return 1;
      }
      if (noble2Index == nobles.size()){
        cout << name2 << "not found" << endl;
        return 1;
      }
      nobles[noble1Index]->battle(*nobles[noble2Index]);
    }
    else if(command == "Clear"){
      for (Noble* noble: nobles){
        delete noble;
      }
      nobles.clear();
      for (Warrior* warrior: warriors){
        delete warrior;
      }
      warriors.clear();
    }
    else if(command == "Fire"){
      file >> name1 >> name2;
      size_t nobleIndex = findNoble(nobles, name1);
      if (nobleIndex == nobles.size()){
        cout << name1 << "not found" << endl;
        return 1;
      }
      if(!nobles[nobleIndex]->fire(name2)){
        return 1;
      };
    }
    else{
      cout << "Bad command";
      return 1;
    }
  }
}
size_t findNoble(const vector<Noble*>& nobles, const string& noble) {
  for (size_t index = 0; index < nobles.size(); index++){
    if (nobles[index]->getName() == noble) {return index;}
  }
  return nobles.size();
}
size_t findWarrior(const vector<Warrior*>& warriors, const string& warrior) {
  for (size_t index = 0; index < warriors.size(); index++){
    if (warriors[index]->getName() == warrior) {return index;}
  }
  return warriors.size();
}

Warrior::Warrior(const string& name,  int strength): name(name), strength(strength){}
string Warrior::getName() const {return name;}
int Warrior::getStrength() const {return strength;}
void Warrior::setStrength(int strength) {this->strength = strength;}
const Noble* Warrior::getNoble() const {return noble;};
void Warrior::setNoble(const Noble* noble) {this->noble = noble;};
void Warrior::display()const{
  cout << name << ": " << strength << endl;
};

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
    warrior->display();
  }
}
bool Noble::fire(const string& warriorName){
  if (!alive) {
    cout << getName() << " is dead!" << endl;
    return false;
  }
  int index = findWarrior(warriors, warriorName);
  if (index == warriors.size() ) { 
    cout << name << " has no warrior " << warriorName << endl;
    return false;
  }
  Warrior* warrior = warriors[index];
  //just move everything forward
  for (index; index < warriors.size() - 1; index++){
    warriors[index] = warriors[index + 1];
  }
  //last one is empty so let's remove it
  warriors.pop_back();
  warrior->setNoble(nullptr);
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