#include <iostream>
#include <algorithm>
using namespace std;

struct TNode {
  TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
    : data(data), left(left), right(right) {}
  int data;
  TNode *left, *right;
};

int max(TNode* root) {
  int l = 0;
  int r = 0;
  if (root->left){
    l = max(root->left);
  }
  if (root->right){
    r = max(root->right);
  }
  return max({l, r, root->data});
}

bool evenOnes(int i){
  if (i < 2) return !i;
  return ((i % 2) + evenOnes(i / 2)) % 2;
}

struct Node {
  Node(int data = 0, Node *next = nullptr)
    : data(data), next(next) {}
  int data;
  Node *next;
};

Node* addList(Node* list1, Node* list2){
  if (!list1) return list1;
  return new Node(list1->data + list2->data, addList(list1->next, list2->next));
}

bool palindrome(char* word, int numChar){
  if (numChar <= 1) return true;
  if (word[0] != word[numChar-1]) return false;
  return palindrome(&word[1], numChar-2);
}

int towers(int n, char start, char target, char helper){
  if (n == 0) return 0;
  return towers(n-1, start, helper, target) + 1 + towers(n-1, helper, target, start);
}

int main() {
  cout << evenOnes(2) << endl;
  cout << evenOnes(3) << endl;
  cout << evenOnes(775) << endl;

  Node* n1 = new Node(1, new Node(2, new Node(3, new Node(4))));
  Node* n2 = new Node(5, new Node(6, new Node(7, new Node(8))));

  Node* n3 = addList(n1, n2);
  while (n3){
    cout << n3->data << " ";
    n3 = n3->next;
  }
  cout << "\n";

  TNode a(1), b(2), c(4), d(8, &a, &b), e(32, &c), f(16, &d, &e);
  cout << max(&f) << endl;

  char s[] = "racecar";
  char notPalindrome[] = "raceca";
  if (palindrome(s, 7)) { cout << "Yes!\n"; }
  if (palindrome(notPalindrome, 6)) { cout << "Yes!\n"; }

  cout << towers(1, 'a', 'b', 'c') << endl;
  cout << towers(2, 'a', 'b', 'c') << endl;
  cout << towers(3, 'a', 'b', 'c') << endl;
  cout << towers(4, 'a', 'b', 'c') << endl;
  cout << towers(5, 'a', 'b', 'c') << endl;
  cout << towers(6, 'a', 'b', 'c') << endl;
  cout << towers(7, 'a', 'b', 'c') << endl;
  cout << towers(8, 'a', 'b', 'c') << endl;
  cout << towers(9, 'a', 'b', 'c') << endl;
  cout << towers(10, 'a', 'b', 'c') << endl;

}

  
  
