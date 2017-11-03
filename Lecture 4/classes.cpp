#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Person {
public:
  Person(const string& aName, int anAge): name(aName), age(anAge){}

  void display(){
    cout << name << ", " << age << endl;
  }
  
  string getName(){ return name; }
private:
  string name;
  int age;
}

int main(){
  Person joey("Joey", 22);
  joey.display();
}