//Boying Tang
//rec03.cpp
//Implementation of Minesweeper

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
using namespace std;

struct Tile {
  void display() const;
  int neighbors;
  bool isVisible;
  bool isBomb;
};
struct Location {
  Location(int row, int col) : row(row), col(col){
  }
  int row;
  int col;
};

class Minesweeper {
public:
  Minesweeper();
  void display(bool displayBombs) const;
  bool done() const;
  bool validRow(int rowNum) const;
  bool validCol(int colNum) const;
  bool isVisible(int rowNum, int colNum) const;
  bool play(int rowNum, int colNum);
private:
  void dfs(int rowNum, int colNum);
  void countNeighbors();
  vector<vector<Tile>> grid;
};

int main() {
  Minesweeper sweeper;
  // Continue until the only invisible cells are bombs
  while (!sweeper.done()) {
      // sweeper.display(true);
      sweeper.display(false); // display the board without bombs

      int row_sel = -1, col_sel = -1;
      while (row_sel == -1) {
          // Get a valid move
          int r, c;
          cout << "row? ";
          cin >> r;
          if (!sweeper.validRow(r)) {
              cout << "Row out of bounds\n";
              continue;
          }
          cout << "col? ";
          cin >> c;
          if (!sweeper.validCol(c)) {
              cout << "Column out of bounds\n";
              continue;
          }
          if (sweeper.isVisible(r,c)) {
              cout << "Square already visible\n";
              continue;
          }
          row_sel = r;
          col_sel = c;
      }
      // Set selected square to be visible. May effect other cells.
      if (!sweeper.play(row_sel,col_sel)) {
          cout << "BOOM!!!\n";
          sweeper.display(true);
          // We're done! Should consider ending more "cleanly",
          // eg. Ask user to play another game.
          exit(0); 
      }
  }
  // Ah! All invisible cells are bombs, so you won!
  cout << "You won!!!!\n";
  sweeper.display(true); // Final board with bombs shown
}

void Tile::display() const {
  if(isBomb){
    cout << "X|";
  }
  else{
    cout << neighbors << "|";
  }
}
Minesweeper::Minesweeper(){
  int size = 10;
  for (int rolNum = 0; rolNum < size; ++rolNum){
    vector<Tile> row;
    for (int colNum = 0; colNum < size; ++colNum){
      Tile tile;
      tile.neighbors = 0;
      tile.isBomb = (rand() % 100) < 10;
      tile.isVisible = false;
      row.push_back(tile);
    }
    grid.push_back(row);
  }
  countNeighbors();
}
void Minesweeper::display(bool displayBombs) const {
  for (const vector<Tile>& row : grid){
    for (const Tile& tile : row){
      if (displayBombs){
        tile.display();
      }
      else if (tile.isVisible){
        tile.display();
      }
      else{
        cout << "_|";
      }
    }
    cout << endl;
  }
}
bool Minesweeper::done() const {
  for (int row = 0; row < grid.size(); ++row){
    for (int col = 0; col < grid[0].size(); ++col){
      if (!grid[row][col].isVisible && !grid[row][col].isBomb)
         return false;
    }
  }
  return true;
}
bool Minesweeper::validRow(int rowNum) const {
  return rowNum >= 0 && rowNum < grid.size();
}
bool Minesweeper::validCol(int colNum) const {
  return colNum >= 0 && colNum < grid[0].size();
}
bool Minesweeper::isVisible(int rowNum, int colNum) const {
  return grid[rowNum][colNum].isVisible;
}
bool Minesweeper::play(int rowNum, int colNum) {
  if (grid[rowNum][colNum].isBomb) return false;
  grid[rowNum][colNum].isVisible = true;
  dfs(rowNum,colNum);
  return true;
}
void Minesweeper::dfs(int rowNum, int colNum){
  vector<Location> stack;
  stack.push_back(Location(rowNum, colNum));
  while(stack.size() != 0){
    Location tileLocation = stack.back();
    stack.pop_back();
    if (grid[tileLocation.row][tileLocation.col].neighbors != 0) continue;
    for (int rowOffset = -1; rowOffset <=1; ++rowOffset){
      for (int colOffset = -1; colOffset <=1; ++colOffset){
        if (validRow(tileLocation .row + rowOffset) && validCol(tileLocation.col + colOffset) && !(colOffset == 0 && rowOffset == 0 )){
          Tile& neighbor = grid[tileLocation.row + rowOffset][tileLocation.col + colOffset];
          if (!neighbor.isVisible && !neighbor.isBomb){
            neighbor.isVisible = true;
            stack.push_back(Location(tileLocation.row + rowOffset, tileLocation.col + colOffset));
          };

        };
      }
    }
  }
}
void Minesweeper::countNeighbors() {
  for (int row = 0; row < grid.size(); ++row){
    for (int col = 0; col < grid[0].size(); ++col){
      for (int rowOffset = -1; rowOffset <=1; ++rowOffset){
        for (int colOffset = -1; colOffset <=1; ++colOffset){
          if (validRow(row + rowOffset) && validRow(col + colOffset) && !(colOffset == 0 && rowOffset == 0 )){
            if (grid[row + rowOffset][col + colOffset].isBomb) grid[row][col].neighbors++;
          };
        }
      }
    }
  }
}
    