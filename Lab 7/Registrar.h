#ifndef REGISTRAR_H
#define REGISTRAR_H
#include "Student.h"
#include "Course.h"
#include <vector>

class Student;
class Course;
namespace BrooklynPoly{
    class Registrar{
    public:
        void printReport() const;
        void addCourse(const std::string& courseName);
        void addStudent(const std::string& studentName);
        void enrollStudentInCourse(const std::string& studentName, const std::string& courseName);
        void cancelCourse(const std::string& studentName);
        void purge();
    private: 
        std::vector<Student*> students;
        std::vector<Course*> courses;
    };
}
#endif