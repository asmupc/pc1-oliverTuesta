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

  CMonedas *m = new CMonedas();
  CMonedasFileManager mfm;
  m->agregarMoneda("USD", 3.71);
  m->agregarMoneda("EUR", 3.71);
  mfm.escribirMoneda("monedas.cs", m->getListaMonedas());
  imprimirLista(mfm.cargarMonedas("monedas.cs"));
  m->setListaMonedas(mfm.cargarMonedas("monedas.cs"));

  m->imprimirMonedas();
  return 0;
}
