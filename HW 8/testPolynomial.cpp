// #include "polynomial.h"
#include <iostream>
#include <vector>
using namespace std;

struct Node {
  Node(int data = 0, Node* next = nullptr) :
    data(data), next(next) {}
  Node(Node& rhs);
  Node* next;
  int data;
};

Node::Node(Node& rhs):data(rhs.data), next(nullptr){
  if (rhs.next){
    next = new Node(*rhs.next);
  }
}

void listDisplay(Node* p) {
  if (p == nullptr) { cout << "empty list" << endl; return; }
  while (p != nullptr) {
    cout << p->data << ' ';
    p = p->next;
  }
  cout << endl;
}

Node* listFindTail(Node* p) {
  if (p == nullptr) { return nullptr; }
  while (p->next != nullptr) {
    p = p->next;
  }
  return p;
}

void listAddTail(Node*& hp, int data) {
  Node* nodeToAdd = new Node(data);
  if (hp == nullptr) {
    // empty list. add first node.
    hp = nodeToAdd;
  } else {
    // find end of list and add there
    Node* tail = listFindTail(hp);
    tail->next = nodeToAdd;
  }
}

void listInsertHead(Node*& hp, int data) {
  hp = new Node(data, hp);
}

void listInsertAfter(Node*& p, int data) {
  if (p == nullptr) { 
    listInsertHead(p, data);
  } else {
    p->next = new Node(data, p->next);
  }
}

bool listRemoveAfter(Node* p) {
  if (p == nullptr || p->next == nullptr) return false;
  Node* target = p->next;
  p->next = target->next;
  delete target;
  return true;
}

Node* listCopy(Node* p) {
  if (p == nullptr) return nullptr;
  // init
  Node* copy = new Node(p->data);
  p = p->next;
  Node* lastAdded = copy;
  // loop
  while (p != nullptr) {
    lastAdded->next = new Node(p->data);
    lastAdded = lastAdded->next;
    p = p->next;
  }
  return copy;
}

Node* listCopyRec(Node* p) {
  if (p == nullptr) return nullptr;
  return new Node(p->data, listCopyRec(p->next));
}

void listClear(Node*& hp) {
  while (listRemoveAfter(hp)) { }
  delete hp;
  hp = nullptr;
}





class Polynomial{
    friend ostream& operator<<(ostream& os, const Polynomial& poly);
    friend Polynomial& operator+(const Polynomial& lhs, const Polynomial& rhs);
public:
    Polynomial(vector<int> coeffs);
    Polynomial(const Polynomial& rhs);
    // Polynomial& operator=(const Polynomial& rhs);
    Polynomial& operator+=(const Polynomial& rhs);
// private:
    Node* head;
    int degree;
};

Polynomial::Polynomial(const Polynomial& rhs):degree(rhs.degree), head(new Node(*rhs.head)){}

Polynomial::Polynomial(vector<int> coeffs): head(nullptr), degree(coeffs.size()){
    if (!coeffs.size()){
        head = new Node(0);
        return;
    }
    for (int i: coeffs){
        listInsertHead(head, i);
    }
}
// Polynomial& Polynomial&::Polynomial operator=(const Polynomial& rhs):degree(rhs.degree){

// }
Polynomial& Polynomial::operator+=(const Polynomial& rhs){
    Node* p = rhs.head;
    Node* t = this->head;
    Node* prev = this->head;
    while (p) {
        if (t) {
            t->data += p->data;
        }
        else{
            listInsertAfter(prev, p->data);
            t = prev->next;
        }

        prev = t;
        p = p->next;
        t = t->next;
    }
    return *this;
}
Polynomial& operator+(const Polynomial& lhs, const Polynomial& rhs){
    Polynomial* result = new Polynomial({});
    *result += lhs;
    *result += rhs;
    return *result;
}

ostream& operator<<(ostream& os, const Polynomial& poly){
    Node* p = poly.head;
    if (p == nullptr) { os << "empty polynomial"; return os; }
    string output = to_string(p->data);
    p = p->next;

    int d = 1;
    while (p != nullptr) {
        if (p->data != 0) output = to_string(p->data) + "x^" + to_string(d) + " + " + output;
        p = p->next;
        ++d;
    }
    os << output;
    return os;
}

void doNothing(Polynomial temp) {}

int main() {
	
    //test constructor
    Polynomial p0({}); 
    Polynomial p1({17});                 // 17
    Polynomial p2({1, 2});               // x + 2
    Polynomial p3({-1, 5});              // -1x + 5
    Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    Polynomial has_a_zero({4, 0, 1, 7}); // 4x^3 + x + 7
    
    cout << "p0: " << p0 << endl;
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3: " << p3 << endl;
    cout << "p4: " << p4 << endl;
    cout << "has_a_zero: " << has_a_zero << endl;
    cout << "p2 += p3: " << (p2+=p3) << endl;
    cout << "p2 += p4: " << (p2+=p4) << endl; 
    cout << "p2 + p3: " << (p2+p3) << endl; 
    cout << "p2 + p4: " << (p2+p4) << endl; 
    cout << "p4 + p2: " << (p4+p2) << endl;


    // test copy constructor - the statement below uses the copy constructor
    // to initialize poly3 with the same values as poly4
    Polynomial p5(p4);
    p5 += p3;
    cout << "Polynomial p5(p4);\n"
         << "p5 += p3;\n";

    cout << "p4: " << p4 << endl;
    cout << "p5: " << p5 << endl;  

    cout << "Calling doNothing(p5)\n";
    doNothing(p5);
    cout << "p5: " << p5 << endl;

    // //tests the assignment operator
    // Polynomial p6;
    // cout << "p6: " << p6 << endl;
    // cout << boolalpha;  // Causes bools true and false to be printed that way.
    // cout << "(p4 == p6) is " << (p4 == p6) << endl;
    // p6 = p4;
    // cout << "p6: " << p6 << endl;
    // cout << boolalpha;
    // cout << "(p4 == p6) is " << (p4 == p6) << endl;

    // //test the evaluaton
    // int x = 5;
    // cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(5) << endl;
    // cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(5) << endl;
	
    // Polynomial p7({3, 2, 1});           // 3x^2 + 2x + 1
    // cout << "p7: " << p7 << endl;
    // cout << "Evaluating p7 at " << x << " yields: " << p7.evaluate(5) << endl;

    // cout << boolalpha;
    // cout << "(p1 == p2) is " << (p1 == p2) << endl;
    // cout << "(p1 != p2) is " << (p1 != p2) << endl;
}


