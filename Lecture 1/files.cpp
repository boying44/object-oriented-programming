#include <iostream>
#include <fstream> 
using namespace std;
// using namespace ifstream;

int main()
{
  ifstream ifs("data.txt");

  // test if ifs was opened successfully
  // checking for a null(?)
  int anInt;
  while (cout << (ifs >> anInt)) {
    cout << anInt << endl;

  }
}