// the extension is for C files whoops
#include <iostream>// preprocessor files
#include <string> // string is in namespace std
using namespace std;

int main()
{
  int x = 5;
  string s = "world"; // double quotes are for strings, strings are an array of charaters
  s[3] = 'e'; // single-quote -> character
  s += "ie";
  string input;
  cout << "A question\n";
  cin >> input; //read input
  cout << "Hello " << input << endl; //cout and endl are bot in std
}