#ifndef _FILEMANAGER_H_
#define _FILEMANAGER_H_

#include "Cuenta.h"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
class CCuentasFileManager {
private:
public:
  // template <class T>
  void actualizarUsuarios(string fileName, vector<CCuenta *> cuentas) {
    ofstream file;
    file.open(fileName, ios::out);
    if (file.is_open()) {
      file << cuentas.size() << '\n';
      for (auto element : cuentas) {
        file << element->getId() << '\n';
        file << element->getName() << '\n';
        file << element->getUser() << '\n';
        file << element->getPassword() << '\n';
        Saldo *actual = element->getListaSaldos();
        file << element->getCantidadSaldos() << '\n';
        while (actual != nullptr) {
          file << actual->tipoMoneda << '\n';
          file << actual->dinero << '\n';
          actual = actual->siguiente;
        }
      }
      file.close();
      cout << "Se ha procesado la operacion correctamente" << '\n';
    } else {
      cout << "Error al actualizar los datos" << '\n';
    }
  }

  void escribirCuenta(string fileName, CCuenta *cuenta) {
    ofstream file;
    file.open(fileName, ios::app);
    if (file.is_open()) {
      file << cuenta->getId() << '\n';
      file << cuenta->getName() << '\n';
      file << cuenta->getUser() << '\n';
      file << cuenta->getPassword() << '\n';
      Saldo *actual = cuenta->getListaSaldos();
      file << cuenta->getCantidadSaldos() << '\n';
      while (actual != nullptr) {
        file << actual->tipoMoneda << '\n';
        file << actual->dinero << '\n';
        actual = actual->siguiente;
      }
      file.close();
      cout << "Se ha procesado la operacion correctamente" << '\n';
    } else {
      cout << "Error al guardar la operacion" << '\n';
    }
  }

  vector<CCuenta *> cargarCuentas(string fileName) {
    vector<CCuenta *> cuentas;
    int cantidad;
    ifstream file;
    file.open(fileName, ios::in);
    if (file.is_open()) {
      string linea;
      getline(file, linea);
      cantidad = stoi(linea);
      for (int i = 0; i < cantidad; i++) {
        CCuenta *cuenta = new CCuenta();
        // linea 1 = id
        getline(file, linea);
        int id = stoi(linea);
        cuenta->setId(id);
        // linea 2 = name
        getline(file, linea);
        cuenta->setName(linea);
        // linea 3 = user
        getline(file, linea);
        cuenta->setUser(linea);
        // linea 4 = password
        getline(file, linea);
        cuenta->setPassword(linea);
        // linea 5 = cantidad de saldos
        int cantidadSaldos;
        getline(file, linea);
        cantidadSaldos = stoi(linea);
        for (int i = 0; i < cantidadSaldos; i++) {
          getline(file, linea);
          string tipoMoneda = linea;
          getline(file, linea);
          float dinero = stof(linea);
          cuenta->addSaldo(dinero, tipoMoneda);
        }
        cuentas.push_back(cuenta);
      }
    }
    return cuentas;
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

  template <class T> void escribir(string fileName, T dato) {
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
