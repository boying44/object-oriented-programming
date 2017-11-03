//Boying Tang
//rec02.cpp
//Parse a file with a list of the name and molecular formula of a compund,
//store unique molecular formulas and its various names,
//and output the list of molecular formulas sorted by the number of carbons

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct MolecularFormula{
  int carbons = 0;
  int hydrogens = 0;
  vector<string> names;
};

//Prototypes
size_t findMolecularFormula(const vector<MolecularFormula>& formulas, int numberOfCarbon, int numberOfHydrogen);
void printFormulas(const vector<MolecularFormula>& formulas, int maxCarbon);

int main(){
  ifstream file("data.txt");
  
  if(!file){
    cerr << "Error"; //cerr also outputs to screen
    return 1;
  }
  
  vector<MolecularFormula> formulas;
  
  string name;
  char throwAwayChar;
  int numberOfCarbon;
  int numberOfHydrogen;
  int maxCarbon = 0;
  while(file >> name >> throwAwayChar >> numberOfCarbon >> throwAwayChar >> numberOfHydrogen){
    size_t index = findMolecularFormula(formulas, numberOfCarbon, numberOfHydrogen);
    
    if (numberOfCarbon > maxCarbon) maxCarbon = numberOfCarbon;
    if (index == formulas.size()){
      MolecularFormula newMolecularFormula;
      newMolecularFormula.carbons = numberOfCarbon;
      newMolecularFormula.hydrogens = numberOfHydrogen;
      newMolecularFormula.names.push_back(name);
      formulas.push_back(newMolecularFormula);
    }
    else{
      formulas[index].names.push_back(name);
    }
  }
  printFormulas(formulas, maxCarbon);
}

size_t findMolecularFormula(const vector<MolecularFormula>& formulas, int numberOfCarbon, int numberOfHydrogen)
{
  for (size_t index = 0; index < formulas.size(); index++){
    const MolecularFormula& formula = formulas[index];
    if (formula.carbons == numberOfCarbon && formula.hydrogens == numberOfHydrogen) return index;
  }
  return formulas.size();
}

void printFormulas(const vector<MolecularFormula>& formulas, int maxCarbon){
  for (int numCarbon = 0; numCarbon <= maxCarbon; numCarbon++){
    for (const MolecularFormula& formula : formulas){
      if (formula.carbons == numCarbon){
        cout << 'C' << formula.carbons << 'H' << formula.hydrogens << " " ;
        for (const string name : formula.names){
          cout << name << " ";
        }
        cout << endl;
      }
    }
  }
}