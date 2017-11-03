#include "Student.h"
#include <iostream>
#include <string>
using namespace std;

namespace BrooklynPoly{
  Student::Student(const string& name): name(name) {}
  void Student::display() const{
      cout << "    " << name << endl;
  };
  string Student::getName() const{
      return name;
  };
}
