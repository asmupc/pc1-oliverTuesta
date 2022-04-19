#include "Controller.h"
#include "Monedas.h"
#include "monedasfilemanager.h"
#include <bits/stdc++.h>
using namespace std;

void imprimirLista(Moneda *moneda) {
  if (moneda == nullptr) {
    return;
  }
  cout << moneda->id << " \t" << moneda->nombre;
  printf("\t%.2f\n", moneda->valor);
  imprimirLista(moneda->siguiente);
}

int main(int argc, char *argv[]) {

  CController c;
  CCuenta *user = c.buscarCuentaPorUsuario("leonardo");
  c.eliminarCuenta(user);

  return 0;
}
