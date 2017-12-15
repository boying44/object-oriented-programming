// Doubly linked list
//  Test code

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
private:
    struct Node;
public:
    List(): listSize(0), start(new Node()), finish(new Node()){
        start->next = finish;
        finish->prev = start;
    };
    List(List& rhs): List(){
        for (int i : rhs){
            push_back(i);
        }
    }
    List& operator=(List& rhs){
        if (this == &rhs) {
            return *this;
        }
        clear();
        start->next = finish;
        finish->prev = start;
        listSize = rhs.listSize;
        for (int i : rhs){
            push_back(i);
        }
        return *this;
    }
    ~List(){
        clear();
        delete start;
        delete finish;
    }
    class iterator {
        friend List;
        friend bool operator==(const iterator& lhs, const iterator& rhs) {
            return lhs.ptr == rhs.ptr;
        }
        friend bool operator!=(const iterator& lhs, const iterator& rhs) {
            return !(lhs == rhs);
        }
    public:
        explicit iterator(Node* ptr = nullptr) : ptr(ptr) {}
        iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }
        iterator& operator--() {
            ptr = ptr->prev;
            return *this;
        }
        int operator*() const { return ptr->data; }
    private:
        Node* ptr;
    };
    iterator begin(){
        return iterator(start->next);
    }
    iterator end(){
        return iterator(finish);
    }
    iterator insert(const iterator& iter, int data){
        Node* newNode = new Node(data, iter.ptr->prev, iter.ptr);
        iter.ptr->prev->next = newNode;
        iter.ptr->prev = newNode;
        listSize++;
    }
    iterator erase(const iterator& iter){
        Node* next = iter.ptr->next;
        iter.ptr->prev->next = iter.ptr->next;
        iter.ptr->next->prev = iter.ptr->prev;
        delete iter.ptr;
        listSize--;
        return iterator(next);
    }
    void push_back(int data){
        Node* newNode = new Node(data, finish->prev, finish);
        finish->prev->next = newNode;
        finish->prev = newNode;
        listSize++;
    }
    int pop_back(){
        Node* last = finish->prev;
        last->prev->next = finish;
        finish->prev = last->prev;
        listSize--;
        return last->data;
    }
    void push_front(int data){
        Node* newNode = new Node(data, start, start->next);
        start->next->prev = newNode;
        start->next = newNode;
        listSize++;
    }
    int pop_front(){
        Node* first = start->next;
        first->next->prev = start;
        start->next = first->next;
        listSize--;
        return first->data;
    }
    int front()const {
        return start->next->data;
    }
    int back() const{
        return finish->prev->data;
    }
    int size() const{
        return listSize;
    }
    void clear(){
        Node* curr = start->next;
        Node* next; 
        while (curr != finish){
            next = curr->next;
            delete curr;
            curr = next;
        }
        start->next = finish;
        finish->prev = start;
        listSize = 0;
    }
    int& operator[](int index){
        Node* curr = start->next;
        while (index){
            curr = curr->next;
            index--;
        } 
        return curr->data;
    }
    friend ostream& operator<<(ostream& os, List& list);
private:
    struct Node{
        Node(int data = 0, Node* prev = nullptr, Node* next = nullptr): data(data), prev(prev), next(next){}
        Node(Node& rhs): data(rhs.data), prev(new Node(*rhs.prev)), next(new Node(*rhs.next)){}
        int data;
        Node* prev;
        Node* next;
    };
    Node* start;
    Node* finish;
    int listSize ;
};

ostream& operator<<(ostream& os, List& list){
    List::Node* curr = list.start->next;
    while (curr != list.finish){
        os << curr->data << " ";
        curr = curr->next;
    }
    return os;
}

void printListInfo(List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back: " << myList.back()
             << ", list: " << myList << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}    

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";

    // Task3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";
    
    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "Filling an empty list with insert at one after begin: i*i for i from 0 to 9\n";
    myList.clear();
    myList.insert(myList.begin(), 0);
    for (int i = 0; i < 10; ++i) myList.insert(++myList.begin(), i*i);
    printListInfo(myList);
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    printListInfo(myList);
    // ***Need test for erase other than begin/end***
     for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Erasing the elements in the list, after first\n";
    while (myList.size()-1) {
        printListInfo(myList);
        myList.erase(++myList.begin());
    }
    printListInfo(myList);
    cout << "===================\n";

    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
}
