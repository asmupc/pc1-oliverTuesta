#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "Cuenta.h"
#include <algorithm>
#include <vector>

#define FIRST_ID 100

class CController {
private:
  vector<CCuenta *> cuentas;

  CCuenta *buscarCuentaPorUsuario(string user) {
    for (CCuenta *element : cuentas) {
      if (user == element->getUser()) {
        return element;
      }
    }
    return nullptr;
  }

public:
  CController() {}
  ~CController() {}
  void registrarCuenta(CCuenta *cuenta) {
    cuenta->setId(cuentas.size() + FIRST_ID);
    cuentas.push_back(cuenta);
  }

  void eliminarCuenta(CCuenta *cuenta) {
    cuentas.erase(cuentas.begin() + cuenta->getId() - FIRST_ID);
  }

  CCuenta *iniciarSesion(string user, string password) {
    CCuenta *cuentaObjetivo = buscarCuentaPorUsuario(user);
    if (cuentaObjetivo->getPassword() == password) {
      return cuentaObjetivo;
    }
    return nullptr;
  }
};

#endif
