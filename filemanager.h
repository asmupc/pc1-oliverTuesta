#ifndef _FILEMANAGER_H_
#define _FILEMANAGER_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class CFileManager {
protected:
  string fileName;

public:
  CFileManager(string fileName) { this->fileName = fileName; }
  ~CFileManager() {}

  void leerArchivo() {
    ifstream file;
    file.open(fileName, ios::in);
    if (file.is_open()) {
      int data;
      while (!file.eof()) {
        file >> data;
        cout << data << " ";
      }
      file.close();
    } else
      cout << "Cannot open the file: " << fileName << '\n';
    cout << '\n';
  }

  void leerLineas() {
    ifstream file;
    file.open(fileName, ios::in);
    string linea;
    if (file.is_open()) {
      while (!file.eof()) {
        getline(file, linea);
        cout << linea << '\n';
      }
    }
  }

  void leerCaracteres() {
    ifstream file;
    file.open(fileName, ios::in);
    if (file.is_open()) {
      char data;
      while (!file.eof()) {
        file >> data;
        cout << data << " ";
      }
      file.close();
    } else
      cout << "Cannot open the file: " << fileName << '\n';
    cout << '\n';
  }

  // Agregar mas notas al archivo notas

  template <class T> void escribir(T dato) {
    ofstream file;
    file.open(fileName, ios::out);
    if (file.is_open()) {
      file << dato;
      file.close();
    } else {
      cout << "Error al modificar cantidad de usuarios" << '\n';
    }
  }
};
#endif
