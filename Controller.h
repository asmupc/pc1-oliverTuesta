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
  string CUENTAS_FILE = "cuentas.cs";
  string MONEDAS_FILE = "monedas.cs";
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
    Moneda *sol = monedas->buscarPorNombre("PEN");
    Moneda *dolar = monedas->buscarPorNombre("USD");
    Moneda *euro = monedas->buscarPorNombre("EUR");
    monedas->agregarMoneda("PEN", 1.0);
    monedas->agregarMoneda("USD", 3.71);
    monedas->agregarMoneda("EUR", 4.03);
    monedasFM.escribirMoneda(MONEDAS_FILE, monedas->getListaMonedas());
    monedas->setListaMonedas(monedasFM.cargarMonedas(MONEDAS_FILE));
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

  void cambioDivisas(CCuenta *cuenta) {
    cout << "\t\tCAMBIO DE DIVISAS"
         << "\n\n";
    int opcion;
    cuenta->imprimirSaldos();
    cout << "Seleccione la moneda que desea cambiar: ";
    cin >> opcion;
    Saldo *saldo = cuenta->buscarPorId(opcion);
    string monedaInicial = saldo->tipoMoneda;
    if (saldo != nullptr && saldo->dinero > 0) {
      monedas->imprimirMonedas();
      cout << "Seleccione la nueva moneda: ";
      cin >> opcion;
      Moneda *monedaNueva = monedas->buscarPorId(opcion);
      if (monedaNueva != nullptr) {
        float valorInicial;
        cout << "Digite el monto a convertir: ";
        cin >> valorInicial;
        if (valorInicial > 0 && valorInicial <= saldo->dinero) {
          cuenta->retirarSaldo(valorInicial, monedaInicial);
          // convirtiendo a soles
          valorInicial *= monedas->getValorPorNombreRecursivo(
              monedas->getListaMonedas(), monedaInicial);
          // convetir a la nueva moneda
          float valorConvertido = valorInicial / monedaNueva->valor;
          cuenta->addSaldo(valorConvertido, monedaNueva->nombre);
          actualizarDatos();
          cout << "Su cambio se ha realizado correctamente" << '\n';
        } else {
          cout << "No se pudo realizar el cambio,\nel monto minimo a convertir "
                  "es 5"
               << '\n';
        }

      } else {
        cout << "No se ha encontrado esa moneda" << '\n';
      }
    } else {
      cout << "No tiene dinero en esa cuenta" << '\n';
    }
  }
};

#endif
