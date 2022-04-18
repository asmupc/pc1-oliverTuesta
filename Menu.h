
#include "Controller.h"
#include "Cuenta.h"
#include <iostream>
#include <string>

class CMenu {
private:
  CController controller;
  void Clear() {
#if defined _WIN32
    system("cls");
    // clrscr(); // including header file : conio.h
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    // std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined(__APPLE__)
    system("clear");
#endif
  }

public:
  CMenu() {}
  ~CMenu() {}

  void registrarUsuario() {
    int opcion = 1;
    string name, user, password;
    name = "";
    cout << "\n\t\tREGISTRAR USUARIO"
         << "\n\n";
    cout << "Ingrese su nombre: ";
    while (name.size() < 1) {
      getline(cin, name);
    }

    bool usuarioExiste = false;
    do {
      cout << "Ingrese su nombre de usuario: ";
      cin >> user;
      usuarioExiste = controller.buscarCuentaPorUsuario(user) != nullptr;
      if (usuarioExiste) {
        cout << "Usuario ya registrado, intente otra vez" << '\n';
      }
    } while (usuarioExiste);

    bool passwordAccepted = false;
    do {
      cout << "Ingrese su contrasena: ";
      cin >> password;
      passwordAccepted = password.size() >= 4;
      if (!passwordAccepted)
        cout << "Su contrasena debe tener mas de 4 digitos" << '\n';
    } while (!passwordAccepted);

    CCuenta *nuevaCuenta = new CCuenta(name, user, password);
    controller.registrarCuenta(nuevaCuenta);
    Clear();
  }

  CCuenta *iniciarSesion() {

    string user, password;
    cout << "\n\t\tINICIAR SESION"
         << "\n\n";
    cout << "Ingrese su usuario: ";
    cin >> user;
    cout << "Ingrese su contrasena: ";
    cin >> password;
    CCuenta *cuenta = controller.iniciarSesion(user, password);
    Clear();
    if (cuenta != nullptr)
      return cuenta;
    return nullptr;
  }

  void menuInisioSesion(CCuenta *cuenta) {

    int opcion = 1;
    do {
      cout << "\n\t\tBienvenido " << cuenta->getName() << "\n\n";
      cout << "1) Depositar dinero" << '\n';
      cout << "2) Ver saldo" << '\n';
      cout << "3) Cambio de divisas" << '\n';
      cout << "4) Retirar dinero" << '\n';
      cout << "0) Salir" << '\n';
      cout << "\nElija una opcion: ";
      cin >> opcion;
      string moneda;
      float monto;
      switch (opcion) {
      case 1:
        Clear();
        cout << "\t\tDEPOSITAR DINERO"
             << "\n\n";
        moneda = controller.seleccionarTipoMoneda();
        if (moneda.empty())
          break;
        cout << "Digite el monto: ";
        cin >> monto;
        cout << "monto ingresado: " << monto << '\n';
        controller.agregarSaldo(cuenta, moneda, monto);
        break;
      case 2:
        Clear();
        cuenta->imprimirSaldos();
        break;
      case 3:
        Clear();
        controller.cambioDivisas(cuenta);
        break;
      case 4:
        Clear();
        cout << "\t\tRETIROS"
             << "\n\n";
        float montoRetirar;
        cuenta->imprimirSaldos();
        int idMoneda;
        cout << "Seleccione el tipo de moneda: ";
        cin >> idMoneda;
        Saldo *saldo = cuenta->buscarPorId(cuenta->getListaSaldos(), idMoneda);
        if (saldo != nullptr) {
          cout << "Digite el monto a retirar: ";
          cin >> montoRetirar;
          cuenta->retirarSaldo(montoRetirar, saldo->tipoMoneda);
          controller.actualizarDatos();
        } else {
          cout << "No tiene dinero en esa cuenta" << '\n';
        }
      }
    } while (opcion != 0);
  }

  void init() {
    int opcion = 1;
    do {
      cout << "\n\t\tBIENVENIDO A CAMBIO SEGURO"
           << "\n\n";
      cout << "1) Inisiar sesion" << '\n';
      cout << "2) Registrarse" << '\n';
      cout << "0) Salir" << '\n';
      cout << "\nElija una opcion: ";
      cin >> opcion;
      CCuenta *cuenta;
      switch (opcion) {
      case 1:
        Clear();
        cuenta = iniciarSesion();
        if (cuenta != nullptr)
          menuInisioSesion(cuenta);
        if (cuenta == nullptr) {
          cout << "\nUsuario o contrasena incorrecta" << '\n';
        }
        break;
      case 2:
        Clear();
        registrarUsuario();
      }
    } while (opcion != 0);
  }
};
