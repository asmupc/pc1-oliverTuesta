
#include "Controller.h"
#include "Cuenta.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  CController *controller = new CController();
  CCuenta *cuentaOliver = new CCuenta();
  cuentaOliver->addSaldo(500, "PEN");
  cuentaOliver->addSaldo(0, "USD");
  cuentaOliver->addSaldo(0, "EUR");

  string name, user, password;
  cin >> name >> user >> password;

  cuentaOliver->setName(name);
  cuentaOliver->setUser(user);
  cuentaOliver->setPassword(password);

  controller->registrarCuenta(cuentaOliver);
  CCuenta *cuenta = controller->iniciarSesion(user, password);
  cout << cuenta->getName() << '\n';
  return 0;
}
