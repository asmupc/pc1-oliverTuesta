
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
    while (!passwordAccepted && !usuarioExiste) {
      cout << "Ingrese su contrasena: ";
      cin >> password;
      passwordAccepted = password.size() >= 4;
      if (!passwordAccepted)
        cout << "Su contrasena debe tener mas de 4 digitos" << '\n';
    }

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

  void escribirComentario(CCuenta *cuenta) {
    cout << "\t\tESCRIBE UN COMENTARIO" << '\n';
    string texto;
    while (texto.size() < 1) {
      getline(cin, texto);
    }
    // cin >> texto;
    controller.agregarComentario(cuenta->getName(), texto);
    cout << "\nGracias por dejar un comentario\n" << '\n';
  }

  void menuInisioSesion(CCuenta *cuenta) {

    int opcion = 1;
    do {
      cout << "\n\t\tBienvenido " << cuenta->getName() << "\n\n";
      cout << "1) Depositar dinero" << '\n';
      cout << "2) Ver saldo" << '\n';
      cout << "3) Cambio de divisas" << '\n';
      cout << "4) Retirar dinero" << '\n';
      cout << "5) Historial" << '\n';
      cout << "6) Escribir Comentarios" << '\n';
      cout << "7) Ver Comentarios" << '\n';
      cout << "\n8) Eliminar cuenta" << '\n';
      cout << "\n9) Ordenar Cuentas" << '\n';
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
        controller.retirarDinero(cuenta);
        break;
      case 5:
        Clear();
        controller.mostrarHistorial(cuenta);
        break;
      case 6:
        Clear();
        escribirComentario(cuenta);
        break;
      case 7:
        Clear();
        controller.imprimirComentarios();
        break;
      case 9:
        Clear();
        controller.ordenarCuentas();
        break;
      case 8:
        Clear();
        cout << "Esta seguro que desea eliminar su cuenta?" << '\n';
        cout << "Su dinero sera retirado y todos sus datos eliminados" << '\n';
        cout << "(si | no)" << '\n';
        string respuesta;
        cin >> respuesta;
        if (respuesta == "Si" || respuesta == "si" || respuesta == "SI") {
          controller.eliminarCuenta(cuenta);
          opcion = 0;
        }
        break;
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
