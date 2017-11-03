#include "Registrar.h"
#include "Course.h"
#include "Student.h"
#include <iostream>
using namespace std;

namespace BrooklynPoly{
  void Registrar::printReport() const {
    cout << "Courses:\n" ; 
    for(const Course* const course: courses){
        course->display();
    }
  }
  void Registrar::addCourse(const string& courseName){
    courses.push_back(new Course(courseName));
  } 
  void Registrar::addStudent(const string& studentName){
    students.push_back(new Student(studentName));
  } 

  Student* findStudent(const vector<Student*> students, const string& studentName){
    for(Student* student: students){
        if(student->getName() == studentName){
            return student;
        }
    }
    return nullptr;
  }

  Course* findCourse(const vector<Course*> courses, const string& courseName){
    for(Course* course: courses){
        if(course->getName() == courseName){
            return course;
        }
    }
    return nullptr;
  }
  void Registrar::enrollStudentInCourse(const string& studentName, const string& courseName){
    Course* course = findCourse(courses,courseName);
    Student* student = findStudent(students,studentName);

    if(course != nullptr && student != nullptr){
        course->addStudent(student);
    }
  }
  void Registrar::cancelCourse(const string& courseName){
    for(int i = 0; i < courses.size(); ++i){
        if(courses[i]->getName() == courseName){
            delete courses[i];
            courses[i] = courses[courses.size() - 1];
            courses.pop_back();
            return;
        }
    }

  }
  void Registrar::purge(){
    for(Student* student: students){
        delete student;
    }
    students.clear();
    for(Course* course: courses){
        delete course;
    }
    courses.clear();
  };  
}