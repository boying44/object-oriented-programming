#include "Course.h"
#include "Student.h"
#include <iostream>
#include <string>
using namespace std;

namespace BrooklynPoly {
  Course::Course(const string& name): name(name) {}
  void Course::display() const{
      cout << "  " << name << endl;
      cout << "  Students: " << students.size() << endl;
      for(Student* student: students){
          student->display();
      }
  };
  void Course::addStudent(Student* student){
      students.push_back(student);
  };
  string Course::getName() const{
      return name;
  };
}