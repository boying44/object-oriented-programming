#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct MolecularFormula{
  int carbons = 0;
  int hydrogens = 0;
  vector<string> names;
  MolecularFormula* prev;
  MolecularFormula* next;
};

MolecularFormula* findMolecularFormula(MolecularFormula* formula, int numberOfCarbon, int numberOfHydrogen)
{
  while ((*formula).carbons <= numberOfCarbon){
    if ((*formula).hydrogens != numberOfHydrogens)
    formula = (*formula).next;
  }
  return formula;
}

void insertMolecularFormula(MolecularFormula* formula, int numberOfCarbon, int numberOfHydrogen){
  MolecularFormula newMolecularFormula;
  newMolecularFormula.carbons = numberOfCarbon;
  newMolecularFormula.hydrogens = numberOfHydrogen;
  newMolecularFormula.names.push_back(name);
  formulas.push_back(newMolecularFormula);

  (*((*formula).next)).prev = &newMolecularFormula;
}

void printFormulas(const vector<MolecularFormula>& formulas){
  for (const MolecularFormula& formula : formulas){
    cout << 'C' << formula.carbons << 'H' << formula.hydrogens << " ";
    for (const string name : formula.names){
      cout << name << " ";
    }
    cout << endl;
  }
}

int main(){
  ifstream file("data.txt");

  if(!file){
    cerr << "Error";
    return 1;
  }

  MolecularFormula formula;

  string name;
  char throwAwayChar;
  int numberOfCarbon;
  int numberOfHydrogen;
  while(file >> name){
    file >> throwAwayChar;
    file >> numberOfCarbon;
    file >> throwAwayChar;
    file >> numberOfHydrogen;

    MolecularFormula* place = findMolecularFormula(&formula, numberOfCarbon, numberOfHydrogen);

    insertMolecularFormula(place, numberOfCarbon, numberOfHydrogen, name);

    // if (index != 0){
    //   MolecularFormula newMolecularFormula;
    //   newMolecularFormula.carbons = numberOfCarbon;
    //   newMolecularFormula.hydrogens = numberOfHydrogen;
    //   newMolecularFormula.names.push_back(name);
    //   formulas.push_back(newMolecularFormula);
    // }
    // else{
    //   formulas[index].names.push_back(name);
    // }
  }
  // printFormulas(formulas);
}