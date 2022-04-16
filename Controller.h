#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "Cuenta.h"
#include "Monedas.h"
#include "cuentasfilemanager.h"
#include "monedasfilemanager.h"
#include <algorithm>
#include <cstddef>
#include <vector>

#define FIRST_ID 100

class CController {
private:
  string CUENTAS_FILE = "cuentas.ci";
  string CLASE_MONEDAS_FILE = "clasemonedas.ci";
  CCuentasFileManager filemanager;
  CMonedasFileManager monedasFM;
  vector<CCuenta *> cuentas;
  CMonedas *monedas;

  void actualizarDatos() {
    filemanager.actualizarUsuarios(CUENTAS_FILE, cuentas);
  }

public:
  CController() {
    cuentas = filemanager.cargarCuentas(CUENTAS_FILE);
    monedas = new CMonedas();
    monedas->setListaMonedas(monedasFM.cargarMonedas(monedas->getFileName()));
    Moneda *sol = monedas->buscarPorNombre("PEN");
    Moneda *dolar = monedas->buscarPorNombre("USD");
    Moneda *euro = monedas->buscarPorNombre("EUR");
    if (sol == nullptr) {
      monedas->agregarMoneda("PEN", 1.0);
    }
    if (dolar == nullptr) {
      monedas->agregarMoneda("USD", 3.71);
    }
    if (euro == nullptr) {
      monedas->agregarMoneda("EUR", 4.03);
    }
  }
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
    monedas->imprimirMonedas();
    cout << "\n0)\tSalir" << '\n';
    int opcion;
    do {
      cout << "Seleccione una opcion: ";
      cin >> opcion;
    } while (opcion < 0 || opcion > monedas->getCantidadMonedas());
    if (opcion == 0)
      return "";
    auto moneda = monedas->buscarPorId(opcion);
    return moneda->nombre;
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
