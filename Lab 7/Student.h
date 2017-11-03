#ifndef STUDENT_H
#define STUDENT_H
#include <string>

namespace BrooklynPoly{
    class Student{
    public:
        Student(const std::string& name);
        void display() const;
        std::string getName() const;
    private:
        std::string name;
    };
}

#endif