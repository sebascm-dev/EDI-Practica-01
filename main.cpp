// INCLUDES IMPORTANTES
#include <iostream>
#include <fstream>
#include <cstring>

// INCLUDES DE FICHEROS DE CLASES
#include "Torneo.h"

// USO DEL NAMESPACE
using namespace std;

// CONSTANTES DE REMPLAZO
#define N 10
#define SALTO 4

// DEFINICION DE TIPOS
typedef char cadena[30];

// VARIABLES
int numTorneos;
cadena nuevoNombreTorneo, nuevoNombreFichero;
Torneo* tablaTorneos = new Torneo[N];

// DEFINICION DE STRUCTS
struct TorneoAux {
    int numGolfistasAux;
    cadena nomTorneoAux;
    cadena nomFicheroAux;
};



void crearFicheroTorneo() {
    fstream fichero;
    fichero.open("torneo.dat", ios::binary | ios::in | ios::out);

    if (fichero.fail()) {
        fichero.clear();
        fichero.close();

        fichero.open("torneo.dat", ios::binary | ios::out);
        fichero.close();

        fichero.open("torneo.dat", ios::binary | ios::in | ios::out);
        cout << "\n[+] Fichero de torneos creado: torneo.dat\n" << endl;
    } else {
        fichero.seekg(0, ios::end);
        int tamFichero = fichero.tellg();
        numTorneos = tamFichero / sizeof(TorneoAux);

        fichero.seekg(0, ios::beg);
        for(int i = 0; i < numTorneos; i++) {
            TorneoAux aux;
            fichero.read((char*) &aux, sizeof(TorneoAux));
            tablaTorneos[i].putNomTorneo(aux.nomTorneoAux);
            tablaTorneos[i].putNomFichero(aux.nomFicheroAux);
        }
    }
    fichero.close();
}



void menuPrincipal() {

    int opcMenuPrincipal;

    do{
        system("cls");
        cout << "=== TORNEOS DE GOLF ===" << endl;
        cout << "-----------------------" << endl;
        cout << "Torneos: " << numTorneos << endl;
        cout << endl;
        cout << "\t1. Listado de Torneos" << endl;
        cout << "\t2. Alta Torneo" << endl;
        cout << "\t3. Elegir torneo" << endl;
        cout << "\t4. Salir" << endl;
        cout << endl;
        cout << "Indique la opcion deseada: "; cin >> opcMenuPrincipal; cin.ignore();

        switch (opcMenuPrincipal) {

            case 1:{ // RESUELTO - LISTO PARA CORRECCIÓN CON EL PROFESOR

                system("cls");
                cout << endl;
                cout << "=== LISTADO DE TORNEOS ACTIVOS ===" << endl;
                cout << endl;

                for(int i = 0; i < numTorneos; i++){
                    cadena nombre, fichero;
                    tablaTorneos[i].getNomTorneo(nombre);
                    tablaTorneos[i].getNomFichero(fichero);
                    cout << (i+1) << ". " << nombre << " ---> (Archivo: " << fichero << ")" << endl;
                }

                cout << endl;
                system("pause");
                break;
            }

            case 2: { // RESUELTO - LISTO PARA CORRECCIÓN CON EL PROFESOR

                system("cls");
                cout << endl;
                cout << "=== DAR UN TORNEO DE ALTA ===" << endl;
                cout << endl;

                Torneo nuevoTorneo;
                TorneoAux Taux;

                cout << "[/] Introduzca nombre del torneo a dar de alta: ";
                cin.getline(nuevoNombreTorneo, 30);
                nuevoTorneo.putNomTorneo(nuevoNombreTorneo);

                cout << "[/] Introduzca nombre del fichero para el torneo: ";
                cin.getline(nuevoNombreFichero, 30);

                strcat(nuevoNombreFichero, ".dat");
                nuevoTorneo.putNomFichero(nuevoNombreFichero);

                cout << endl;
                cout << "[+] Torneo " << nuevoNombreFichero << " creado correctamente!" << endl;
                nuevoTorneo.crearFichero(nuevoNombreFichero);

                cout << "[+] Insertando datos del torneo " << nuevoNombreTorneo << " en el fichero torneo.dat" << endl;
                Taux.numGolfistasAux = nuevoTorneo.getNumGolfistas();
                strcpy(Taux.nomTorneoAux, nuevoNombreTorneo);
                strcpy(Taux.nomFicheroAux, nuevoNombreFichero);

                fstream fichero;
                fichero.open("torneo.dat", ios::binary | ios::in | ios::out);

                fichero.seekp(0, ios::end);
                fichero.write((char*) &Taux, sizeof(TorneoAux));

                fichero.seekg(0, ios::end);
                int tamFichero = fichero.tellg();
                numTorneos = tamFichero / sizeof(TorneoAux);

                fichero.seekg(0, ios::beg);
                for(int i = 0; i < numTorneos; i++) {
                    TorneoAux aux;
                    fichero.read((char*) &aux, sizeof(TorneoAux));
                    tablaTorneos[i].putNomTorneo(aux.nomTorneoAux);
                    tablaTorneos[i].putNomFichero(aux.nomFicheroAux);
                }

                cout << endl;
                cout << "[OK] Operacion de Alta Torneo Completada!!!" << endl;
                system("pause");

                break;
            }

            case 3: { // SIN RESOLVER

                cout << "Opción 3" << endl;
                break;
            }

            case 4: { // RESUELTO

                system("cls");
                cout << endl;
                cout << "=== SALIENDO DEL PROGRAMAM ===" << endl;
                break;
            }

            default: { // RESUELTO

                cout << "[!] ERROR: Escriba un valor valido..." << endl;
                break;
            }
        }
    } while (opcMenuPrincipal != 4);
}




int main()
{

    crearFicheroTorneo();

    Torneo t1;
    cadena nombreTor, nombreFic;
    strcpy(nombreTor, "torneo_prueba");
    strcpy(nombreFic, "torneo_prueba.dat");
    t1.putNomTorneo(nombreTor);
    t1.putNomFichero(nombreFic);
    t1.crearFichero(nombreFic);

    // Crear golfistas de prueba
    Golfista g1, g2, g3;

    // Golfista 1
    strcpy(g1.licencia, "LIC-001");
    g1.handicap = 12.5;
    strcpy(g1.nombre, "Sebastian");
    strcpy(g1.apellidos, "Contreras Marin");
    g1.golpes = 0;
    g1.resultado = 0;

    // Golfista 2
    strcpy(g2.licencia, "LIC-002");
    g2.handicap = 8.0;
    strcpy(g2.nombre, "Antonio");
    strcpy(g2.apellidos, "Navarro");
    g2.golpes = 0;
    g2.resultado = 0;

    // Golfista 3
    strcpy(g3.licencia, "LIC-003");
    g3.handicap = 15.0;
    strcpy(g3.nombre, "Miguel");
    strcpy(g3.apellidos, "Gomez");
    g3.golpes = 0;
    g3.resultado = 0;

    // Insertar golfistas en el torneo
    //t1.insertar(g1);
    //t1.insertar(g2);
    //t1.insertar(g3);

    t1.mostrar(8.0);

    //menuPrincipal();

    delete[] tablaTorneos;
    return 0;
}
