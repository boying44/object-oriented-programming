//Boying Tang
//hw03.cpp
//Parse a file with a list of commands, and execute them to simulate a 
//a battle between medevial time warriors, rewritten with a Warrior as a class

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


struct Weapon{
  Weapon(string& name, int strength) : name(name), strength(strength){};
  string name;
  int strength;
};

class Warrior{
public:
  Warrior(string& name, string& weaponName, int strength): name(name), weapon(weaponName, strength){}
  int getStrength() const;
  void setStrength(int strength);
  string getName() const; 
  string getWeaponName() const;
  void battle(Warrior& other); 
private:
  string name;
  Weapon weapon;
};

bool canBattle(const Warrior& warrior1, const Warrior& warrior2);
void printWinner(const Warrior& warrior1, const Warrior& warrior2);
size_t findWarrior(const vector<Warrior>& warriors, const string& name);
void printStatus(const vector<Warrior>& warriors);
void printWarriors(const vector<Warrior>& warriors);

int main(){
  fstream file("warriors.txt");
  
  if(!file){
    cerr << "Error";
    return 1;
  }
  vector<Warrior> warriors;
  
  string command;
  string name;
  string weaponName;
  int strength;
  string name1;
  string name2;
  while (file >> command){
    if (command == "Status"){ 
      printStatus(warriors);
    }
    else if(command == "Warrior"){
      file >> name;
      file >> weaponName;
      file >> strength;
      Warrior newWarrior(name, weaponName, strength);
      warriors.push_back(newWarrior);
    }
    else{
      // cout << "Battle";
      file >> name1;
      file >> name2;
      cout << name1 << " battles " << name2 << endl; 

      warriors[findWarrior(warriors, name1)].battle(warriors[findWarrior(warriors, name2)]);
    }
  }
  file.close();
}

int Warrior::getStrength() const {return weapon.strength;}
void Warrior::setStrength(int strength) {weapon.strength = strength;}
string Warrior::getName() const {return name;}
string Warrior::getWeaponName() const {return weapon.name;}
void Warrior::battle(Warrior& other){
  if (!canBattle(*this, other)) return;
  
  int tempStrength = getStrength();
  setStrength(getStrength() - other.getStrength());
  other.setStrength(other.getStrength() - tempStrength);
  if (getStrength() < 0) setStrength(0);
  if (other.getStrength() < 0) other.setStrength(0);
  
  printWinner(*this, other);
}

bool canBattle(const Warrior& warrior1, const Warrior& warrior2){
  if (warrior1.getStrength() == 0 && warrior2.getStrength() == 0){
    cout << "Oh, NO! They're both dead! Yuck!" << endl;
    return false;
  }
  else if (warrior1.getStrength() == 0){
    cout << "He's dead, " << warrior2.getName() << endl;
    return false;
  }
  else if (warrior2.getStrength() == 0){
    cout << "He's dead, " << warrior1.getName() << endl;
    return false;
  }
  return true;
}

void printWinner(const Warrior& warrior1, const Warrior& warrior2){
  if (warrior1.getStrength() == 0 && warrior2.getStrength() == 0){
    cout << "Mutual Annihilation: "<< warrior1.getName() << " and " << warrior2.getName() << " die at each other's hands" << endl;
  }
  else if (warrior1.getStrength() == 0){
    cout << warrior2.getName() << " defeats " << warrior1.getName() << endl;
  }
  else if (warrior2.getStrength() == 0){
    cout << warrior1.getName() << " defeats " << warrior2.getName() << endl;
  }
}

size_t findWarrior(const vector<Warrior>& warriors, const string& name){
  for (size_t index = 0; index < warriors.size(); index++){
    if (warriors[index].getName() == name) {return index;}
  }
  return warriors.size();
}

void printStatus(const vector<Warrior>& warriors){
  cout << "There are: " << warriors.size() << " warriors" << endl;
  printWarriors(warriors);
}

void printWarriors(const vector<Warrior>& warriors){
  for (const Warrior& w : warriors){
    cout << "Warrior: "<< w.getName() << ", weapon: "<< w.getWeaponName() << ", " << w.getStrength() << endl;
  }
}