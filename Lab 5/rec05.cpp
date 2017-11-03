//Boying Tang
//rec05.cpp
//More about pointers

#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Section;
class LabWorker;
class Student;

class LabWorker{
public:
  LabWorker(const string& name);
  void display() const;
  bool addSection(Section& section);
  void addGrade(const string& student, int grade, int week); 
private:
  string name;
  Section* section = nullptr;
};

class Section{
public:
  Section(const string& section, string day, int hour);
  ~Section();
  Section(const Section& rhs);
  class TimeSlot{
  public:
    TimeSlot(const string& day, int hour);
    TimeSlot(const TimeSlot& rhs);
    void display() const;
  private:
    string day;
    int hour;
  };
  void display() const;
  void reset();
  void setGrade(const string& studentName, int grade, int week) const;
  bool addStudent(const string& studentName);
  bool setWorker(LabWorker* worker);
private:
  string section;
  LabWorker* worker = nullptr;
  vector<Student*> students; 
  TimeSlot timeslot;
};

class Student{
public:
  Student(const string& name);
  ~Student();
  void display() const;
  string getName() const;
  void setGrade(int grade, int week);
private:
  string name;
  vector<int> grades;
};

void doNothing(Section sec) { sec.display(); }

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    secA2.display();

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    secA2.display();

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    moe.display();

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    moe.display();

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    jane.display();

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);  
    moe.addGrade("Paul", 19, 1);  
    moe.addGrade("George", 16, 1);  
    moe.addGrade("Ringo", 7, 1);  
    moe.display();

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);  
    moe.addGrade("Paul", 20, 3);  
    moe.addGrade("Ringo", 0, 3);  
    moe.addGrade("George", 16, 3);  
    moe.display();

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, then make sure the following call works\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main

//Section methods
Section::Section(const string& section, string day, int hour): section(section), timeslot(day,hour){};
Section::~Section(){
  cout << "Section " << section << " is being deleted " << endl;
  for (Student* student: students){
    delete student;
  }
  students.clear();
};
Section::Section(const Section& rhs):
 section(rhs.section), timeslot(rhs.timeslot){
   for (Student* student: rhs.students){
     students.push_back(new Student(*student));
   }
};
void Section::display() const {
  cout << "Section: " << section;
  timeslot.display();
  cout << " Students: ";
  if (!students.size()){
    cout << "None" << endl;
    return;
  }
  cout << endl;
  for (const Student* student: students){
    student->display();
  }
};
void Section::reset(){
  for (Student* student: students){
    delete student;
  }
  students.clear();
};
bool Section::addStudent(const string& studentName){
  students.push_back(new Student(studentName));
  return true;
}
bool Section::setWorker(LabWorker* worker){
  if(this->worker){
    cout << "The section " << section << "already has a worker" << endl;
    return false;
  }
  this->worker = worker;
  return true;
};
void Section::setGrade(const string& studentName, int grade, int week) const{
  for (Student* student: students){
    if (student->getName() == studentName){
      student->setGrade(grade, week);
      return;
    }
  }
  cout << "Student does not exist" << endl;
}

//Timeslot methods
Section::TimeSlot::TimeSlot(const string& day, int hour): day(day), hour(hour){};
Section::TimeSlot::TimeSlot(const TimeSlot& rhs): day(rhs.day), hour(rhs.hour){};
void Section::TimeSlot::display() const{
  if (hour > 12)
  cout << ", Time slot: [Day: " << day << ", Start time: " << hour%12 <<"PM]"; 
  else
  cout << ", Time slot: [Day: " << day << ", Start time: " << hour%12 <<"AM]";   
}

//LabWorker methods
LabWorker::LabWorker(const string& name): name(name){};
void LabWorker::display() const{
  if(section){
    cout << name << " has ";
    section->display();
  }
  else {
    cout << name << " does not have a section";
  }
}
bool LabWorker::addSection(Section& section){
  if(this->section){
    cout << name << " already has a section" << endl;
    return false;
  }
  this->section = &section;
  section.setWorker(this);
  return true;
};
void LabWorker::addGrade(const string& student, int grade, int week){
  section->setGrade(student, grade, week);
};

//Student methods
Student::Student(const string& name): name(name){
  for(int i = 0; i < 14; ++i){
    grades.push_back(-1);
  }
};
Student::~Student(){
  cout << "Deleting " << name << endl;
}
void Student::display() const{
   cout << "Name: " << name << ", Grades: ";
   for (int grade: grades){
    cout << grade << " ";
  }
  cout << endl;
}
string Student::getName() const{
  return name;
}
void Student::setGrade(int grade, int week){
  if (week > 14) return;
  grades[week - 1] = grade;
}