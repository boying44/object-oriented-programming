#include <iostream>
using namespace std;

struct Node {
    Node(int data=0, Node* next=nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

void display(Node* list){
    if (!list){
        cout << "Is nullptr";
    }
    while(list){
        cout << list->data << " ";
        list = list->next;
    }
    cout << endl;
}

void listInsertHead(Node*& headPtr, int data) {
    headPtr = new Node(data, headPtr);
}

void spliceInto(Node*& insertAfter, Node* list){
    Node* last = list;
    while(last->next){
        last = last->next;
    }
    last->next = insertAfter->next;
    insertAfter->next = list;
}

bool checkIn(Node* l1, Node* l2){
    while(l2 && l1){
        if(l1->data != l2->data){
            return false;
        }
        l2 = l2->next;
        l1 = l1->next;
    }
    if (l2){
        return false;
    }
    return true;
}

Node* findMatch(Node* l1, Node* l2){
    while (l1 && l1->data != l2->data){
        l1 = l1->next;
    }
    return l1;
}

Node* isSubList(Node* l1, Node* l2){
    Node* match = findMatch(l1,l2);
    while(match){
        if(checkIn(match,l2)){
            return match;
        }
        match = findMatch(match->next,l2);
    }
    return nullptr;
}

int main(){
    Node* L1 = new Node(5, new Node(7, new Node(9, new Node(1))));
    Node* L2 = new Node(6, new Node(3, new Node(2)));

    cout << "L1:";
    display(L1);
    cout << "L2:";
    display(L2);
    
    cout << "Splice L2 into L1 after last element" << endl;
    spliceInto(L1->next->next->next, L2);

    display(L1);
    display(L2);


    Node* L3 = new Node(1, new Node(2, new Node(3, new Node(2, new Node(3, new Node(2, new Node(4, new Node(5, new Node(6)))))))));
    cout << "List:";
    display(L3);

    cout << "Matching 1" << endl;
    Node* N1 = new Node(1);
    display(isSubList(L3, N1));

    cout << "Matching 2" <<endl;
    Node* N2 = new Node(2);
    display(isSubList(L3, N2));

    cout << "Matching 3 9" <<endl;
    Node* N3 = new Node(3, new Node(9));
    display(isSubList(L3, N3));

    cout << "Matching 2 3" <<endl;
    Node* N4 = new Node(2, new Node(3));
    display(isSubList(L3, N4));

    cout << "Matching 2 3 2 4" <<endl;
    Node* N5 = new Node(2, new Node(3, new Node(2, new Node(4))));
    display(isSubList(L3, N5));

    cout << "Matching 5 6 7" <<endl;
    Node* N6 = new Node(5, new Node(6, new Node(7)));
    display(isSubList(L3, N6));

}