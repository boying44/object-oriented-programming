#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct MolecularFormula{
  int carbons = 0;
  int hydrogens = 0;
  vector<string> names;
  bool sorted = false;
};

size_t findMolecularFormula(const vector<MolecularFormula>& formulas, int numberOfCarbon, int numberOfHydrogen)
{
  size_t index = 0;
  for (size_t index = 0; index < formulas.size(); index++){
    MolecularFormula formula = formulas[index];
    if (formula.carbons == numberOfCarbon && formula.hydrogens == numberOfHydrogen) return index;
  }
  return formulas.size();
}

vector<MolecularFormula> sortFormulas(vector<MolecularFormula>& formulas){
  vector<MolecularFormula> sortedFormulas;
  while (sortedFormulas.size() != formulas.size()){

    //choose a valid beginning
    int begIndex = 0;
    while(formulas[begIndex].sorted){
      begIndex++;
    }
    int min = formulas[begIndex].carbons;
    //
    
    for (size_t index = 1; index < formulas.size(); index++){
      if (formulas[index].carbons <= min && !(formulas[index].sorted) ){
        min = formulas[index].carbons;
        begIndex = index;
      }
    }
    formulas[begIndex].sorted = true;
    sortedFormulas.push_back(formulas[begIndex]);
  }
  return sortedFormulas;
}

void printFormulas(const vector<MolecularFormula>& formulas){
  for (const MolecularFormula& formula : formulas){
    cout << 'C' << formula.carbons << 'H' << formula.hydrogens << " " ;
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

  vector<MolecularFormula> formulas;

  string name;
  char throwAwayChar;
  int numberOfCarbon;
  int numberOfHydrogen;
  int maxCarbon;
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
  vector<MolecularFormula> sorted = sortFormulas(formulas);
  printFormulas(sorted);
}