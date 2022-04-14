#ifndef _CUENTA_H_
#define _CUENTA_H_

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
using namespace std;

struct Saldo {
  float valor;
  string tipoMoneda;
};

class CCuenta {
private:
  int id;
  string name;
  Saldo *saldo;

public:
  CCuenta() {
    int id = rand() % 1000;
    string name = "undefined";
    saldo = new Saldo();
    saldo->tipoMoneda = "PEN";
  }
  CCuenta(int id, string name, string tipoMoneda) {
    this->name = name;
    this->id = id;
    saldo = new Saldo();
    for_each(tipoMoneda.begin(), tipoMoneda.end(),
             [](char &c) { c = ::toupper(c); });
    saldo->tipoMoneda = tipoMoneda;
  }
  ~CCuenta() {}

  void setId(int id) { this->id = id; }
  void setName(string name) { this->name = name; }
  int getId() { return this->id; }
  string getName() { return this->name; }
};

#endif
