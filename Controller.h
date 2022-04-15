#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "Cuenta.h"
#include <algorithm>
#include <cstddef>
#include <vector>

#define FIRST_ID 100

class CController {
private:
  vector<CCuenta *> cuentas;
  string MONEDAS[3] = {"PEN", "USD", "EUR"};

public:
  CController() {}
  ~CController() {}
  CCuenta *buscarCuentaPorUsuario(string user) {
    for (CCuenta *element : cuentas) {
      if (user == element->getUser()) {
        return element;
      }
    }
    return nullptr;
  }

  string seleccionarTipoMoneda() {
    cout << "\nOpcion\tMoneda" << '\n';
    for (int i = 1; i <= MONEDAS->length(); i++) {
      cout << i << ")\t" << MONEDAS[i - 1] << '\n';
    }
    cout << "\n0)\tSalir" << '\n';
    int opcion;
    do {
      cout << "Seleccione una opcion: ";
      cin >> opcion;
    } while (opcion < 0 || opcion > 3);
    if (opcion == 0)
      return "";
    return MONEDAS[opcion - 1];
  }

  void registrarCuenta(CCuenta *cuenta) {
    cuenta->setId(cuentas.size() + FIRST_ID);
    cuentas.push_back(cuenta);
  }

  void eliminarCuenta(CCuenta *cuenta) {
    cuentas.erase(cuentas.begin() + cuenta->getId() - FIRST_ID);
  }

  CCuenta *iniciarSesion(string user, string password) {
    CCuenta *cuentaObjetivo = buscarCuentaPorUsuario(user);
    if (cuentaObjetivo != nullptr &&
        cuentaObjetivo->getPassword() == password) {
      return cuentaObjetivo;
    }
    return nullptr;
  }
};

#endif
