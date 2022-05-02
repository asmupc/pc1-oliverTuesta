#ifndef _COMENTARIOS_H_
#define _COMENTARIOS_H_

#include "filemanager.h"
#include <iostream>
using namespace std;

class CComentarios {
private:
  struct Node {
    string autor;
    string texto;
    Node *next;
    Node() : next(nullptr) {}
  };
  Node *head;
  Node *back;
  CFileManager *fm;

public:
  CComentarios() {
    fm = new CFileManager();
    head = nullptr;
    back = head;
  }
  ~CComentarios() {}

  bool isEmpty() { return head == nullptr; }

  void push(string autor, string texto) {
    Node *newNode = new Node();
    newNode->autor = autor;
    newNode->texto = texto;
    if (isEmpty())
      head = newNode;
    else
      back->next = newNode;
    back = newNode;
  }

  void printAll() {
    cout << "\t\tCOMENTARIOS"
         << "\n\n";
    fm->leerArchivo("comentarios.cs");
  }

  void deleteAll() {
    Node *aux = head;
    while (!isEmpty()) {
      pop();
    }
  }

  void pop() {
    if (!isEmpty()) {
      Node *aux = head;
      head = head->next;
      delete aux;
    }
  }
};
#endif
