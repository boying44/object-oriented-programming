// rec13_test.cpp

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <set>         // task 20
#include <map>         // task 22
#include <string>
using namespace std;

void printListIter(const list<int>& l){
    for (list<int>::const_iterator iter = l.begin(); iter != l.end() ; ++iter){
        cout << *iter << " ";
    }
}

void printListLoop(const list<int>& l){
    for (int i: l){
        cout << i << " ";
    }
}

void printAuto(const list<int>& l){
    for (auto iter = l.begin(); iter != l.end() ; ++iter){
        cout << *iter << " ";
    }
}

list<int>::const_iterator find(const list<int>& l, int i){
    for (list<int>::const_iterator iter = l.begin(); iter != l.end() ; ++iter){
        if (*iter == i) return iter;
    }
    return l.end();
}

auto findAuto(const list<int>& l, int i){
    for (auto iter = l.begin(); iter != l.end() ; ++iter){
        if (*iter == i) return iter;
    }
    return l.end();
}

bool checkEven(int i){
    return i && 1;
}

class IsEven{
public:
    bool operator()(int i){return i && 1;}
};

//19
// template<typename T>
// typename list<T>::iterator ourFind(typename list<T>::iterator begin, typename list<T>::iterator end, T i){
//     cout << "In ourFind\n";
//     while( begin != end){
//         if (*begin == i) return begin;
//         begin++;
//     }
//     return end;
// }

list<int>::iterator ourFind(list<int>::iterator begin, list<int>::iterator end, int i){
    cout << "In ourFind\n";
    while( begin != end){
        if (*begin == i) return begin;
        begin++;
    }
    return end;
}

//20
template<typename T, typename U>
T ourFind(T begin, T end, U i){
    cout << "In templatedourFind\n";
    while( begin != end){
        if (*begin == i) return begin;
        begin++;
    }
    return end;
}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> v1{6,2,3,4,5,6};
    for (int i: v1){
        cout << i << " ";
    }

    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> l1(v1.begin(), v1.end());
    for (int i: l1){
        cout << i << " ";
    }

    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(v1.begin(), v1.end());
    for (int i: v1){
        cout << i << " ";
    }
    cout << endl;

    for (int i: l1){
        cout << i << " ";
    }

    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";

    for (int i = 0; i < v1.size() ; ++++i){
        cout << v1[i] << " ";
    }

    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";

    // for (int i = 0; i < l1.size() ; ++++i){
    //     cout << l1[i] << " ";
    // }

    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";

    for (vector<int>::iterator iter = v1.begin(); iter != v1.end() ; ++++iter){
        cout << *iter << " ";
    }

    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";

    for (list<int>::iterator iter = l1.begin(); iter != l1.end() ; ++++iter){
        cout << *iter << " ";
    }

    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";

    l1.sort();
    for (int i: l1){
        cout << i << " ";
    }

    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";

    printListIter(l1);
    cout << "\n=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    printListLoop(l1);
    cout << "\n=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    printAuto(l1);
    cout << "\n=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";

    //overloaded find
    cout << *find(l1, 4);
    // cout << *find(l1, 7); //?

    cout << "\n=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    cout << *findAuto(l1, 4);
    // cout << *findAuto(l1, 7); //?
    cout << "\n=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    cout << *find(l1.begin(),l1.end(), 5);

    cout << "\n=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    cout << *find_if(l1.begin(),l1.end(), checkEven);
    cout << "\n=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    IsEven ie;
    cout << *find_if(l1.begin(),l1.end(), ie);

    cout << "\n=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    cout << *find_if(l1.begin(),l1.end(), [](int i){return i && 1;});
    cout << "\n=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int arr[6];

    copy(l1.begin(),l1.end(), arr);
    for (int i: arr){
        cout << i << " ";
    }
    cout << "\n=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    cout << *ourFind(l1.begin(),l1.end(), 5) << endl;;
    cout << "\n=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    cout << *ourFind(v1.begin(),v1.end(), 5) << endl;;
    cout << *ourFind(l1.begin(),l1.end(), 5) << endl;
    cout << "\n=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing 
    cout << "Task 21:\n";
    fstream file("pooh-nopunc.txt");
    vector<string> v;
    string w;
    while(file >> w){
        if (find(v.begin(),v.end(), w) == v.end()){
            v.push_back(w);
        }
    }

    cout << "Size: " << v.size() << "\nContents: ";
    for (string i: v){
        cout << i << " ";
    }
    file.close();
    cout << "\n=======\n";
    
    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    file.open("pooh-nopunc.txt");
    set<string> s;
    while(file >> w){
        s.insert(w);
    }
    file.close();

    cout << "Size: " << s.size() << "\nContents: ";
    for (string i: s){
        cout << i << " ";
    }
    cout << "\n=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    file.open("pooh-nopunc.txt");
    map<string, vector<int>> wordMap;
    int index = 0;
    while(file >> w){
        wordMap[w].push_back(index);
        ++index;
    }

    for(auto p: wordMap){
        cout << p.first << " ";  
        for (int i: p.second){
            cout << i << " ";
        } 
        cout << endl;
    }
    file.close();
    cout << "\n=======\n";
}
