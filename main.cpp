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



    // PRUEBAS DEL METODO MOSTRAR Y CREAR FICHERO
    strcpy(nombreTor, "torneo_prueba");
    strcpy(nombreFic, "torneo_prueba.dat");
    t1.putNomTorneo(nombreTor);
    t1.putNomFichero(nombreFic);
    t1.crearFichero(nombreFic);

    t1.mostrar(-1);



    // PRUEBAS DEL METODO CONSULTAR:
    /*
    int pos;
    cout << "Ingrese la psocion del goldfista a consultar: ";
    cin >> pos;

    Golfista g = t1.consultar(pos);

    if (g.licencia[0] != '\0') {  // Si el objeto no está vacío
        cout << "\n=== GOLFISTA ENCONTRADO ===" << endl;
        cout << "Nombre: " << g.nombre << " " << g.apellidos << endl;
        cout << "Licencia: " << g.licencia << endl;
        cout << "Handicap: " << g.handicap << endl;
        cout << "Golpes: " << g.golpes << endl;
        cout << "Resultado: " << g.resultado << endl;
    } else {
        cout << "[i] No se encontró ningún golfista en esa posición." << endl;
    }
    */



    // PRUEBAS DEL METODO BUSCAR
    cadena licencia;
    cout << "\nIndique la licencia a mostar: "; cin.getline(licencia, 30);

    int pos = t1.buscar(licencia);

    if(pos != -1) {
        cout << "Golfista encontrado en la posicuon: " << pos << endl;
    } else {
        cout << "La licencia del golfista no se encuentra..." << endl;
    }



    //menuPrincipal();

    delete[] tablaTorneos;
    return 0;
}
