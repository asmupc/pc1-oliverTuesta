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

public:
  void actualizarClaseMonedas(string fileName, CMonedas *monedas) {
    ofstream file;
    file.open(fileName, ios::out);
    if (file.is_open()) {
      file << monedas->getFileName();
      file.close();
      escribirMoneda(monedas->getFileName(), monedas->getListaMonedas());
      cout << "Se ha procesado la operacion correctamente" << '\n';
    } else {
      cout << "Error al actualizar monedas" << '\n';
    }
  }
  Moneda *cargarMonedas(string fileName) {
    ifstream file;
    Moneda *m;
    file.open(fileName, ios::out | ::ios::binary);
    if (file.is_open()) {
      file.seekg(0 * sizeof(&m), ios::beg);
      file.read((char *)&m, sizeof(Moneda));
      cout << m->nombre << '\n';
    } else {
      std::cout << "error al guardar lista de monedas" << std::endl;
    }
    return m;
  }
};
#endif
