#include <iostream>
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



