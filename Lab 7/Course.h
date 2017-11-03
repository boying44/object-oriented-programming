#ifndef COURSE_H
#define COURSE_H
#include "Student.h"
#include <string>
#include <vector>

class Student;

namespace BrooklynPoly{
    class Course{
    public:
        Course(const std::string& name);
        void display() const;
        void addStudent(Student* student);
        std::string getName() const;
        // void removeStudent(const string& studentName);
    private:
        std::string name;
        std::vector<Student*> students;     
    };
}

#endif