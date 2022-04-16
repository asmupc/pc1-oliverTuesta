#include "Monedas.h"
#include "monedasfilemanager.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {

  CMonedas *m = new CMonedas();
  CMonedasFileManager mfm;
  m->agregarMoneda("USD", 3.71);
  m->agregarMoneda("EUR", 3.71);
  mfm.actualizarClaseMonedas("clasemonedas.cs", m);
  m->setListaMonedas(mfm.cargarMonedas("monedas.cs"));
  m->imprimirMonedas();
  return 0;
}
