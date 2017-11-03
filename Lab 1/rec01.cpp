//Boying Tang
//rec01.cpp
//Implement Conway's Game of Life
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int countAliveNeighbors(vector<string> grid, int row, int col){
  int aliveNeighbors = 0 ;
  int maxRow = grid.size() - 1;
  int maxCol = grid[0].size() - 1; //valid only bc rows are all the same size

  for (int i = -1; i <= 1; ++i) {

    if (row + i < 0 || row + i > maxRow) continue; // just continue the loop if it's out of bounds
    for (int j = -1; j <= 1; ++j) {
      if (col + j < 0 || col + j > maxCol) continue;
      if (i == 0 && j == 0) continue; // check if it's self
      if (grid[row + i][col + j] == '*') aliveNeighbors++;
    }
  }
  return aliveNeighbors;
}

vector<string> gen(vector<string> oldGrid){ //should be const and passed by reference since it's not being changed

  vector<string> newGrid;

  for (size_t i = 0; i < oldGrid.size(); ++i) {
    string row = oldGrid[i];
    string newRow = "";

    for (size_t j = 0; j < row.size(); ++j) {
      int aliveNeighbors = countAliveNeighbors(oldGrid, i, j);
      if (oldGrid[i][j] == '*' && (aliveNeighbors == 2 || aliveNeighbors == 3)){
        newRow.push_back('*');
      }else if ( aliveNeighbors == 3){
        newRow.push_back('*');
      } 
      else{
        newRow.push_back(' ');
      }
    }

    newGrid.push_back(newRow);
  }
  return newGrid; //put in memory a vector<string>
  //would have returned a copy back in the days
}

void displayGrid(vector<string> grid){
  for( string s : grid ){
    cout << s << endl;
  }
}

int main(){
  ifstream input("life.txt");
  if(input) {
    cerr << "Error" << endl;
    return 1;
  };

  vector<string> grid; //memory is reserved
  string line;
  while( getline(input, line) ){
    grid.push_back(line);
  }

  cout << "Initial State" << endl;
  displayGrid(grid);

  for (int i = 1 ; i <= 10; ++i){
    cout << "Generation:" << i << endl;
    vector<string> newGrid = gen(grid);
    displayGrid(newGrid);
    grid = newGrid; //will create a copy
  }
}

//pay attention to passing by reference and values