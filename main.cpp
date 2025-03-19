#include <iostream>
#include <fstream>
#include <cstring>

#include "Torneo.h"

using namespace std;

#define N 10
#define SALTO 4

typedef char cadena[30];

fstream fichero("torneo.dat", ios::binary | ios::in | ios::out);

cadena nuevoNombreTorneo, nuevoNombreFichero;
int numTorneos = 0;

// Función para leer el número de torneos desde el archivo
void cargarTorneosDesdeFichero() {
    fstream fichero("torneo.dat", ios::binary | ios::in | ios::ate);

    if (fichero) {
        numTorneos = fichero.tellg() / sizeof(Torneo);
        fichero.close();
    } else {
        numTorneos = 0;
    }
}

void menuPrincipal() {
    int opcMenuPrincipal;

    do {
        cout << "MENU PRINCIPAL" << endl;
        cout << "Torneos Activos: " << numTorneos << endl;
        cout << "1. Listado de Torneos" << endl;
        cout << "2. Alta Torneo" << endl;
        cout << "3. Elegir torneo" << endl;
        cout << "4. Salir" << endl;
        cout << endl;

        cout << "Elegir una opcion: ";
        cin >> opcMenuPrincipal;
        cin.ignore();

        switch (opcMenuPrincipal) {
            case 1:
                cout << "Opción 1" << endl;
                break;

            case 2:
                system("cls");
                cout << "\n === DAR UN TORNEO DE ALTA ===" << endl;

                fichero.open("torneo.dat", ios::binary | ios::in | ios::out);

                if (fichero.fail()) {

                    fichero.clear();
                    fichero.close();
                    fichero.open("torneo.dat", ios::binary | ios::out);
                    fichero.close();
                    fichero.open("torneo.dat", ios::binary | ios::in | ios::out);
                    cout << "[+] Fichero de torneos creado: torneo.dat" << endl;

                } else {

                    Torneo nuevoTorneo;

                    cout << "[/] Introduzca nombre del torneo a dar de alta: ";
                    cin.getline(nuevoNombreTorneo, 30);
                    nuevoTorneo.putNomTorneo(nuevoNombreTorneo);

                    cout << "[/] Introduzca nombre del fichero para el torneo: ";
                    cin.getline(nuevoNombreFichero, 30);

                    strcat(nuevoNombreFichero, ".dat");
                    nuevoTorneo.putNomFichero(nuevoNombreFichero);

                    nuevoTorneo.crearFichero(nuevoNombreFichero);



                    cout << "Insertando el torneo " << nuevoNombreTorneo << " dentro del fichero torneo.dat" << endl;

                    fichero.seekp(numTorneos * sizeof(Torneo), ios::beg);
                    fichero.write((char*) &nuevoTorneo, sizeof(Torneo));

                    numTorneos++;

                }

                fichero.close();
                break;

            case 3:
                cout << "Opción 3" << endl;
                break;

            case 4:
                cout << "Saliendo del programa" << endl;
                break;

            default:
                cout << "Introduzca un valor correcto" << endl;
                break;
        }
    } while (opcMenuPrincipal != 4);
}

int main() {
    cargarTorneosDesdeFichero();  // Cargar el número de torneos al inicio
    menuPrincipal();

    return 0;
}
