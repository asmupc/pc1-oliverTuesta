#ifndef _FILEMANAGER_H_
#define _FILEMANAGER_H_

#include <cstring>
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

  string leerArchivo(string fileName) {
    ifstream file;
    file.open(fileName, ios::in);
    string text;
    if (file.is_open()) {
      while (!file.eof()) {
        getline(file, text);
        cout << text << '\n';
      }
    }
    return text;
  }

  void eliminarArchivo(string fileName) {

    // convirtiendo string to char[]
    int n = fileName.length();

    // declaring character array
    char char_array[n + 1];

    // copying the contents of the
    // string to char array
    strcpy(char_array, fileName.c_str());

    if (remove(char_array) != 0)
      perror("Error eliminando el historial");
    else
      puts("Hisotrial eliminado con exito");
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
  //
  //
  void escribirFecha(string fileName) {
    ofstream file;
    file.open(fileName, ios::app);

    time_t now = time(0);
    tm *ltm = localtime(&now);

    if (file.is_open()) {
      file << ltm->tm_hour << ":";
      file << ltm->tm_min;
      file << "   " << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/"
           << 1900 + ltm->tm_year << "  :  ";
      file.close();
    }
  }
  template <typename T> void escribir(string fileName, T dato) {
    escribirFecha(fileName);
    ofstream file;
    file.open(fileName, ios::app);
    if (file.is_open()) {
      file << dato << '\n';
      file.close();
    } else {
      cout << "Error al escribir el archivo" << '\n';
    }
  }
};
#endif
