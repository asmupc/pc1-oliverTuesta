#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "Cuenta.h"
#include "filemanager.h"
#include <algorithm>
#include <cstddef>
#include <vector>

#define FIRST_ID 100

struct Moneda {
  float val;
  string nombre;
  Moneda *siguiente;
  Moneda() : val(1.0), siguiente(nullptr) {}
};

class CController {
private:
  string CUENTAS_FILE = "cuentas.ci";
  CFilemanager filemanager;
  vector<CCuenta *> cuentas;
  string MONEDAS[3] = {"PEN", "USD", "EUR"};

  void actualizarDatos() {
    filemanager.actualizarUsuarios(CUENTAS_FILE, cuentas);
  }

public:
  CController() { cuentas = filemanager.cargarCuentas(CUENTAS_FILE); }
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
    actualizarDatos();
  }

  void eliminarCuenta(CCuenta *cuenta) {
    cuentas.erase(cuentas.begin() + cuenta->getId() - FIRST_ID);
    actualizarDatos();
  }
  void agregarSaldo(CCuenta *cuenta, string tipoMoneda, float saldo) {
    cuenta->addSaldo(saldo, tipoMoneda);
    actualizarDatos();
    cout << "Se depositado satisfactoriamente " << saldo << " en la cuenta "
         << tipoMoneda << '\n';
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
