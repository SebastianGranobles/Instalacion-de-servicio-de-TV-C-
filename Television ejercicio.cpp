#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Cliente {
public:
    string nombre;
    string direccion;
    bool tieneDeuda;

    Cliente(string n, string d, string password) : nombre(n), direccion(d) {
        tieneDeuda = (password == "0000");  // Si la contraseña es "0000", el cliente tiene deuda
    }
};

class SolicitudServicio {
public:
    Cliente cliente;
    bool aprobada;
    string fechaInstalacion;
    string horaInstalacion;

    SolicitudServicio(Cliente c) : cliente(c), aprobada(false) {}

    void validarSolicitud() {
        if (cliente.tieneDeuda) {
            cout << "Solicitud rechazada: El cliente tiene una deuda pendiente.\n";
        } else {
            aprobada = true;
            cout << "Solicitud aprobada.\n";
            solicitarFechaHora();
        }
    }

    bool validarHora(string hora) {
        int h, m;
        char separador;
        stringstream ss(hora);
        ss >> h >> separador >> m;

        return (h > 7 || (h == 7 && m >= 30)) && (h < 18 || (h == 18 && m == 0));
    }

    bool validarFecha(string fecha) {
        int dia, mes, anio;
        char separador;
        stringstream ss(fecha);
        ss >> dia >> separador >> mes >> separador >> anio;

        return dia <= 27;  // Se permite hasta el día 27 del mes
    }

    void solicitarFechaHora() {
        cin.ignore(); // Limpiar el buffer antes de usar getline()
        do {
            cout << "Ingrese la fecha de instalación (DD/MM/AAAA): ";
            getline(cin, fechaInstalacion);
            if (!validarFecha(fechaInstalacion)) {
                cout << "Error: La instalación debe ser antes del día 28 del mes.\n";
            }
        } while (!validarFecha(fechaInstalacion));

        do {
            cout << "Ingrese la hora de instalación (HH:MM): ";
            getline(cin, horaInstalacion);
            if (!validarHora(horaInstalacion)) {
                cout << "Error: La hora debe estar entre 07:30 y 18:00.\n";
            }
        } while (!validarHora(horaInstalacion));
    }
};

class Instalacion {
public:
    SolicitudServicio solicitud;
    bool completada;

    Instalacion(SolicitudServicio s) : solicitud(s), completada(false) {}

    void instalar() {
        if (solicitud.aprobada) {
            cout << "Instalando el servicio para " << solicitud.cliente.nombre << "...\n";
            cout << "Fecha de instalación: " << solicitud.fechaInstalacion << "\n";
            cout << "Hora de instalación: " << solicitud.horaInstalacion << "\n";
            completada = true;
            cout << "Instalación completada.\n";
        } else {
            cout << "No se puede instalar el servicio porque la solicitud no fue aprobada.\n";
        }
    }
};

class SatisfaccionCliente {
public:
    Instalacion instalacion;

    SatisfaccionCliente(Instalacion i) : instalacion(i) {}

    void verificarSatisfaccion() {
        if (instalacion.completada) {
            cout << "¿Está satisfecho con el servicio? (s/n): ";
            char respuesta;
            cin >> respuesta;
            if (respuesta == 's' || respuesta == 'S') {
                cout << "Servicio entregado a satisfacción del cliente.\n";
            } else {
                cout << "Reporte de insatisfacción registrado.\n";
            }
        } else {
            cout << "No se puede verificar la satisfacción sin instalacion.\n";
        }
    }
};

int main() {
    string nombre, direccion, password;

    cout << "Ingrese su nombre: ";
    getline(cin, nombre);
    cout << "Ingrese su direccion: ";
    getline(cin, direccion);
    cout << "Ingrese su cedula: ";
    cin >> password;

    Cliente cliente(nombre, direccion, password);
    SolicitudServicio solicitud(cliente);
    solicitud.validarSolicitud();

    Instalacion instalacion(solicitud);
    instalacion.instalar();

    SatisfaccionCliente satisfaccion(instalacion);
    satisfaccion.verificarSatisfaccion();

    return 0;
}
