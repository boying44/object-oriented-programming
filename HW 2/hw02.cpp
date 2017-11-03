//Boying Tang
//hw02.cpp
//Parse a file with a list of commands, and excute them to simulate a 
//a battle between medevial time warriors

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Warrior{
  string name;
  int strength;
};

bool canBattle(const Warrior& warrior1, const Warrior& warrior2);
void printWinner(const Warrior& warrior1, const Warrior& warrior2);
void battle(Warrior& warrior1, Warrior& warrior2);
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
  string name1;
  string name2;
  while (file >> command){
    if (command == "Status"){
      printStatus(warriors);
    }
    else if(command == "Warrior"){
      Warrior newWarrior;
      file >> newWarrior.name;
      file >> newWarrior.strength;
      warriors.push_back(newWarrior);
    }
    else{
      // cout << "Battle";
      file >> name1;
      file >> name2;
      cout << name1 << " battles " << name2 << endl; 
  
      battle(warriors[findWarrior(warriors, name1)], warriors[findWarrior(warriors, name2)]);
    }
  }
}


bool canBattle(const Warrior& warrior1, const Warrior& warrior2){
  if (warrior1.strength == 0 && warrior2.strength == 0){
    cout << "Oh, NO! They're both dead! Yuck!" << endl;
    return false;
  }
  else if (warrior1.strength == 0){
    cout << "He's dead, " << warrior2.name << endl;
    return false;
  }
  else if (warrior2.strength == 0){
    cout << "He's dead, " << warrior1.name << endl;
    return false;
  }
  return true;
}

void printWinner(const Warrior& warrior1, const Warrior& warrior2){
  if (warrior1.strength == 0 && warrior2.strength == 0){
    cout << "Mutual Annihilation: "<< warrior1.name << " and " << warrior2.name << " die at each other's hands" << endl;
  }
  else if (warrior1.strength == 0){
    cout << warrior2.name << " defeats " << warrior1.name << endl;
  }
  else if (warrior2.strength == 0){
    cout << warrior1.name << " defeats " << warrior2.name << endl;
  }
}

void battle(Warrior& warrior1, Warrior& warrior2){
  if (!canBattle(warrior1, warrior2)) return;

  int tempStrength = warrior1.strength;
  warrior1.strength -= warrior2.strength;
  warrior2.strength -= tempStrength;
  if (warrior1.strength < 0) warrior1.strength = 0;
  if (warrior2.strength < 0) warrior2.strength = 0;

  printWinner(warrior1, warrior2);
}

size_t findWarrior(const vector<Warrior>& warriors, const string& name){
  for (size_t index = 0; index < warriors.size(); index++){
    if (warriors[index].name == name) {return index;}
  }
  return warriors.size();
}

void printStatus(const vector<Warrior>& warriors){
  cout << "There are: " << warriors.size() << " warriors" << endl;
  printWarriors(warriors);
}

void printWarriors(const vector<Warrior>& warriors){
  for (const Warrior& w : warriors){
    cout << "Warrior: "<< w.name << ", strength: "<< w. strength<< endl;
  }
}