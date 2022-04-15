#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// ofstream salida
// ifstream entrada
// fstream entrada y salida

void escribirArchivo(string fileName) {
  ofstream file;
  int edad = 20;
  float peso = 60.5;
  char sexo = 'M';
  file.open(fileName, ios::out);
  if (file.is_open()) {
    cout << "File is open" << '\n';
    file << "File created successfully!" << '\n';
    file << "la edad es: " << edad << '\n';
    file << "El peso es: " << peso << '\n';
    file << "El sexo es: " << sexo << '\n';
    file.close();
    cout << "File writted successfully" << '\n';
  } else {
    cout << "Error while open the file" << '\n';
  }
}

void leerArchivo(string fileName) {
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

void leerLineas(string fileName) {
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

void leerCaracteres(string fileName) {
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

void escribir(string fileName) {
  ofstream file;
  file.open(fileName, ios::app);
  if (file.is_open()) {
    cout << "File is open" << '\n';
    int nota;
    while (cin >> nota) {
      file << nota << " ";
      cout << "nota agregada" << '\n';
    }
    file.close();
    cout << "File writted successfully" << '\n';
  } else {
    cout << "Error while open the file" << '\n';
  }
}

int main(int argc, char *argv[]) {
  // escribirArchivo("text");
  // leerArchivo("notas");
  // leerLineas("notas");
  // leerCaracteres("text");
  escribir("notas");
  return 0;
}
