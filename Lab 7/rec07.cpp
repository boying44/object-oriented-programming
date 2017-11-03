/*Boying Tang
rec07
The University Registrar
*/

#include "Registrar.h"
#include "Course.h"
#include "Student.h"
#include <iostream>
#include <vector>
#include <string>
using namespace BrooklynPoly;
using namespace std;

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    registrar.printReport(); // or cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    registrar.printReport(); // or cout << registrar << endl;
    //    cout << registrar << endl;  // or registrar.printReport()

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    registrar.printReport(); // or cout << registrar << endl;
    //    cout << registrar << endl;  // or registrar.printReport()

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    registrar.printReport(); // or cout << registrar << endl;
    //    cout << registrar << endl;  // or registrar.printReport()

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    registrar.printReport(); // or cout << registrar << endl;
    //    cout << registrar << endl;  // or registrar.printReport()

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout <<  "Should fail, i.e. do nothing, since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    registrar.printReport(); // or cout << registrar << endl;
    //    cout << registrar << endl;  // or registrar.printReport()

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    registrar.printReport(); // or cout << registrar << endl;
    //    cout << registrar << endl;  // or registrar.printReport()
   
    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;  // or registrar.printReport()

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;  // or registrar.printReport()

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;  // or registrar.printReport()
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    registrar.printReport(); // or cout << registrar << endl;
    //    cout << registrar << endl;  // or registrar.printReport()
}




