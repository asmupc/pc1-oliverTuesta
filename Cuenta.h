#ifndef _CUENTA_H_
#define _CUENTA_H_

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
using namespace std;

struct Saldo {
  float dinero = 0;
  string tipoMoneda;
  Saldo *siguiente;
  Saldo() : dinero(0), siguiente(nullptr), tipoMoneda("PEN") {}
};

class CCuenta {
private:
  int id;
  string user;
  string password;
  string name;

  Saldo *listaSaldos;
  Saldo *ultimo;

  Saldo *buscarPorTipoMoneda(string tipoMoneda) {
    Saldo *actual = listaSaldos;
    if (listaSaldos == nullptr) {
      return nullptr;
    }
    while (actual != nullptr) {
      if (actual->tipoMoneda == tipoMoneda) {
        return actual;
      }
      actual = actual->siguiente;
    }
    return nullptr;
  }

public:
  CCuenta() {
    int id = 0;
    string name = "undefined";
    listaSaldos = new Saldo();
    ultimo = listaSaldos;
  }
  CCuenta(string name, string user, string password) {
    this->name = name;
    this->user = user;
    this->password = password;
    listaSaldos = new Saldo();
    ultimo = listaSaldos;
  }
  ~CCuenta() {}

  void setId(int id) { this->id = id; }
  int getId() { return this->id; }

  void setName(string name) { this->name = name; }
  string getName() { return this->name; }

  void setUser(string user) { this->user = user; }
  string getUser() { return this->user; }

  void setPassword(string password) { this->password = password; }
  string getPassword() { return this->password; }

  void addSaldo(float saldo, string tipoMoneda) {
    Saldo *buscado = buscarPorTipoMoneda(tipoMoneda);
    if (buscado == nullptr) {
      Saldo *nuevoSaldo = new Saldo();
      nuevoSaldo->tipoMoneda = tipoMoneda;
      nuevoSaldo->dinero = saldo;
      ultimo->siguiente = nuevoSaldo;
      ultimo = nuevoSaldo;
    } else {
      buscado->dinero += saldo;
    }
    cout << "Se depositado satisfactoriamente " << saldo << " en la cuenta "
         << tipoMoneda << '\n';
  }

  void imprimirSaldos() {
    Saldo *actual = listaSaldos;
    if (listaSaldos == nullptr) {
      return;
    }
    cout << "MONEDA\tSALDO" << '\n';
    while (actual != nullptr) {
      cout << actual->tipoMoneda << ": \t" << actual->dinero << '\n';
      actual = actual->siguiente;
    }
    cout << '\n';
  }
};

#endif
