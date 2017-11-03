#include <iostream>
#include <vector> 
using namespace std;

int main()
{
  vector<int> vectorOfInts;

  // Segmentation fault
  // cout << vectorOfInts[16]; //If memory allocated by another piece of code, will return value at address

  vectorOfInts.push_back(5);
  vectorOfInts.push_back(8);
  
  for(size_t t = 0; i < vectorOfInts.size(); ++i){
    
  }
}