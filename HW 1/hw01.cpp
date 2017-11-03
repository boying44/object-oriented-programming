//Boying Tang
//Life.cpp
//Decode a file encoded with a Caesar cypher
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Decodes the cypher, give the character and number of steps
char decode(char character, int steps){
  int place = character - 'a';
  return (place - steps + 26) % 26 + 'a'; //plus 26 to take care of negative numbers easily
}

int main(){
  ifstream input("encrypted.txt");

  if (!input){
    cerr << "Error\n";
    return 1;
  }

  int steps;
  input >> steps; //reading the steps
  //doesn't read \n

  string line;
  string newText = "";
  getline(input, line); // read the empty leftover line

  while ( getline(input, line) ){
    string newLine = ""; // could save directly to line
    for ( size_t i = 0; i < line.size(); ++i){
      char curr = line[i];
      if ('a' <= curr && curr <= 'z') {
        newLine += decode(curr, steps);
      } else {
        newLine += curr;
      }
    }
    newText = newLine + "\n" + newText;
  }

  cout << newText;
}