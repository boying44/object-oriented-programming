//Boying Tang
//Life.cpp
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
      // cout << row + i << "," << col + j << endl;

      if (col + j < 0 || col + j > maxCol) continue;
      if (i == 0 && j == 0) continue; // check if it's self
      if (grid[row + i][col + j] == '*') aliveNeighbors++;
    }
  }
  return aliveNeighbors;
}

vector<string> gen(vector<string> oldGrid){ //should be const and passed by reference

  vector<string> newGrid;

  for (size_t i = 0; i < oldGrid.size(); ++i) {
    string row = oldGrid[i];
    string newRow = "";

    for (size_t j = 0; j < row.size(); ++j) {
      // cout << i;
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
  // cout << "endgen";
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
  if(!input) cout << "Error";

  vector<string> grid; //memory is reserved
  string line;
  while( getline(input, line) ){
    // cout << line << endl;
    grid.push_back(line);
  }

  //cout << countAliveNeighbors(grid, 0, 1);

  //foo(grid);

  cout << "Initial State";
  displayGrid(grid);

  for (int i = 1 ; i <= 10; ++i){
    cout << "Generation:" << i << endl;
    vector<string> newGrid = gen(grid);
    displayGrid(newGrid);
    grid = newGrid; //will create a copy
  }
}

//pay attention to passing by reference and values