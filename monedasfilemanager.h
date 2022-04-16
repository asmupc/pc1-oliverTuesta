#ifndef _MONEDASFILEMANAGER_H_
#define _MONEDASFILEMANAGER_H_

#include "Monedas.h"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
class CMonedasFileManager {
private:
public:
  void escribirMoneda(string fileName, Moneda *moneda) {
    if (moneda == nullptr) {
      return;
    }
    ofstream file;
    file.open(fileName, ios::out | ::ios::binary);
    if (file.is_open()) {
      file.write((const char *)&moneda, sizeof(Moneda));
    } else {
      std::cout << "error al guardar lista de monedas" << std::endl;
    }
  }
  Moneda *cargarMonedas(string fileName) {
    ifstream file;
    Moneda *m = nullptr;
    file.open(fileName, ios::out | ::ios::binary);
    if (file.is_open()) {
      file.seekg(0 * sizeof(&m), ios::beg);
      file.read((char *)&m, sizeof(Moneda));
    } else {
      std::cout << "error al guardar lista de monedas" << std::endl;
    }
    return m;
  }
};
#endif
