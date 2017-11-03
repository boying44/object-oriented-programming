#include <iostream>
// #include <string>
using namespace std;

void addOne(int n){
  int *np = &n;
  cout << np << endl;
  n = n + 1;
  cout << n << endl;
}

int main(){
  int x = 5;
  int *p = &x;
  cout << p << endl;

  addOne(x);
  cout << x << endl;
}

void printHello(){
  cout << "Hello" << endl;
}