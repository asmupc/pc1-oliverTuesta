#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "Cuenta.h"
#include "Monedas.h"
#include "cuentasfilemanager.h"
#include "filemanager.h"
#include "monedasfilemanager.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <ctime>
#include <string>
#include <vector>

#define FIRST_ID 100

class CController {

private:
  string CUENTAS_FILE = "cuentas.cs";
  string MONEDAS_FILE = "monedas.cs";
  CFileManager *fm;
  CCuentasFileManager *cuentasFM;
  CMonedasFileManager *monedasFM;
  vector<CCuenta *> cuentas;

  CMonedas *monedas;

public:
  CController() {
    monedasFM = new CMonedasFileManager(MONEDAS_FILE);
    cuentasFM = new CCuentasFileManager(CUENTAS_FILE);
    cuentas = cuentasFM->cargarCuentas();
    monedas = new CMonedas();
    Moneda *sol = monedas->buscarPorNombre("PEN");
    Moneda *dolar = monedas->buscarPorNombre("USD");
    Moneda *euro = monedas->buscarPorNombre("EUR");
    monedas->agregarMoneda("PEN", 1.0);
    monedas->agregarMoneda("USD", 3.83);
    monedas->agregarMoneda("EUR", 4.03);
    monedasFM->escribirMoneda(monedas->getListaMonedas());
    // monedas->setListaMonedas(monedasFM->cargarMonedas());
  }
  ~CController() {}
  CCuenta *buscarCuentaPorUsuario(string user) {
    CCuenta *buscada = nullptr;
    for_each(cuentas.begin(), cuentas.end(), [=, &buscada](CCuenta *cuenta) {
      if (user == cuenta->getUser()) {
        buscada = cuenta;
      }
    });
    return buscada;
  }

  void actualizarDatos() { cuentasFM->actualizarUsuarios(cuentas); }

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
    fm->escribir(cuenta->getUser() + ".cs",
                 "Se ha creado la cuenta a nombre de " + cuenta->getName());
    actualizarDatos();
  }

  void eliminarCuenta(CCuenta *cuenta) {
    cuentas.erase(cuentas.begin() + cuenta->getId() - FIRST_ID);
    actualizarDatos();
    fm->eliminarArchivo(cuenta->getUser() + ".cs");
    cout << "Su cuenta ha sido eliminada correctamente" << '\n';
  }
  void agregarSaldo(CCuenta *cuenta, string tipoMoneda, float saldo) {
    saldo = (int)((saldo)*100) / 100.0;
    if (cuenta->addSaldo(saldo, tipoMoneda)) {
      actualizarDatos();
      cout << "Se depositado satisfactoriamente " << saldo << " en la cuenta "
           << tipoMoneda << '\n';
      string operacion =
          "Se ha agregado " + to_string(saldo) + " a la cuenta " + tipoMoneda;
      fm->escribir(cuenta->getUser() + ".cs", operacion);
    }
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
    Saldo *saldo = cuenta->buscarPorId(cuenta->getListaSaldos(), opcion);
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
          float valorInicialSoles =
              valorInicial * monedas->getValorPorNombreRecursivo(
                                 monedas->getListaMonedas(), monedaInicial);
          // convetir a la nueva moneda
          // los * 100 y / 100 son para redondear a dos cifras de cimales
          float valorConvertido =
              (int)((valorInicialSoles / monedaNueva->valor) * 100) / 100.0;
          cuenta->addSaldo(valorConvertido, monedaNueva->nombre);
          actualizarDatos();
          cout << "Su cambio se ha realizado correctamente" << '\n';

          string operacion =
              "Se ha cambiado" + to_string(valorInicial) + " " + monedaInicial +
              " a " + to_string(valorConvertido) + " " + monedaNueva->nombre;
          fm->escribir(cuenta->getUser() + ".cs", operacion);

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
  void mostrarHistorial(CCuenta *cuenta) {
    string fileName = cuenta->getUser() + ".cs";
    cout << "\n\tFECHA\t\tOPERACION"
         << "\n\n";
    string history = fm->leerArchivo(fileName);
    cout << '\n';
  }
};

#endif
