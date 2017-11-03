#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Cat {
  string color = "black"; // needs C++ 11 => to do what? Default implementation?
  string name = "felix"; // needs C++ 11
};

struct Word {
  string token;
  vector<int> positions;
};

size_t findToken(const string& token, const vector<Word>& words){
  for (size_t index = 0; index < words.size(); index++){
    if (words[index].token == token) {return index;}
  }
  // some OSes might use unsigned ints 
  // return -1;
  return words.size();
}

void printWords(const vector<Word>& words){
  for (const Word& w : words){
    cout << w.token << ':';
    for (int position : w.positions) {cout << position << ' ';} //without braket will print endl after each position, why?
    cout << endl;
  }
}

int main(){
  // will not compile, equality operator not implemented
  // if (myCat == yourCat){}
  
  // Cat myCat;
  // cout << myCat.color;

  ifstream file("data.txt");
  
  if (!file){
    cerr << "Error";
    return 1;
  };
  
  vector<Word> words;

  string token;
  int position = 0;
  while (file >> token){
    // cout << token;
    size_t index = findToken(token, words);

    if( index == words.size() ){
      Word word;
      word.token = token;
      word.positions.push_back(position);
      words.push_back(word);
    }
    else {
      words[index].positions.push_back(position);
    }
    position++;
  }

  printWords(words);
}