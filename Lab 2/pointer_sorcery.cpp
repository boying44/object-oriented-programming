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

void sortFormulas(const vector<MolecularFormula>& formulas){
  
}

void printFormulas(const vector<MolecularFormula*>& formulas){
  for (MolecularFormula* formulaptr : formulas){
    MolecularFormula& formula = *formulaptr;
    cout << 'C' << formula.carbons << 'H' << formula.hydrogens << " ";
    // string s = formula.names[0];

    // for (string name : formula.names){
    //   cout << name << " ";
    // }
    cout << endl;
  }
}

size_t findMolecularFormula(const vector<MolecularFormula*>& formulas, int numberOfCarbon, int numberOfHydrogen)
{
  size_t index = 0;
  cout << "printing in" << endl;
  printFormulas(formulas);
  for (size_t index = 0; index < formulas.size(); index++){
    MolecularFormula& formula = *(formulas[index]);
    // cout << "check carbon " << formula.carbons ;
    if (formula.carbons == numberOfCarbon && formula.hydrogens == numberOfHydrogen) return index;
  }
  return formulas.size();
}

int main(){
  ifstream file("data.txt");

  if(!file){
    cerr << "Error";
    return 1;
  }

  vector<MolecularFormula*> formulas;

  string name;
  char throwAwayChar;
  int numberOfCarbon;
  int numberOfHydrogen;
  while(file >> name){
    file >> throwAwayChar;
    file >> numberOfCarbon;
    file >> throwAwayChar;
    file >> numberOfHydrogen;

    cout << "parsed formula: "<< 'C' << numberOfCarbon << 'H' << numberOfHydrogen << " " << endl;
    
    size_t index = findMolecularFormula(formulas, numberOfCarbon, numberOfHydrogen);
    cout << "after find index" << endl;
    printFormulas(formulas);

    cout << "index:" << index << " size:" << formulas.size() << " equal?" << (index == formulas.size()) << endl;

    if (index == formulas.size()){
      cout << "begin add" << endl;
      ///safe
      MolecularFormula newMolecularFormula;
      printFormulas(formulas);
      newMolecularFormula.carbons = numberOfCarbon;
      newMolecularFormula.hydrogens = numberOfHydrogen;
      newMolecularFormula.names.push_back(name); 
      cout << "before push" << endl;
      printFormulas(formulas);
      formulas.push_back(&newMolecularFormula);
      cout << "after push" << endl;
      printFormulas(formulas);
    }
    // else{
      // MolecularFormula& formula = *(formulas[index]);
      // formula.names.push_back(name);
  //   }
  }
  // printFormulas(formulas);
}