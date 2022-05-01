#include <bits/stdc++.h>
using namespace std;

template <typename T> struct Node {
  T val;
  Node *next;
  Node() : val(0), next(nullptr) {}
  Node(int x) : val(x), next(nullptr) {}
  Node(int x, Node *next) : val(x), next(next) {}
};

template <typename T> class CCola {
private:
  Node<T> *head;
  Node<T> *back;

public:
  CCola() {
    head = nullptr;
    back = head;
  }
  ~CCola() {}

  bool isEmpty() { return head == nullptr; }

  void push(int val) {
    Node<T> *newNode = new Node<T>(val);
    if (isEmpty())
      head = newNode;
    else
      back->next = newNode;
    back = newNode;
  }

  void printAll() {
    Node<T> *aux = head;
    while (aux != nullptr) {
      cout << aux->val << " ";
      aux = aux->next;
    }
    if (!isEmpty())
      cout << '\n';
  }

  void deleteAll() {
    Node<T> *aux = head;
    while (!isEmpty()) {
      pop();
    }
  }

  void pop() {
    if (!isEmpty()) {
      Node<T> *aux = head;
      head = head->next;
      delete aux;
    }
  }
};
