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



// CREANDO STRUCT PARA GUARDAR LOS TORNEOS DADOS DE ALTA EN TORNEO.DAT
struct TorneoAux
{
    int numGolfistasAux;
    cadena nomTorneoAux;
    cadena nomFicheroAux;
};



// FUNCION PARA CREAR TORNEO.DAT EN CASO DE QUE NO EXISTA Y SI EXISTE LEER DATOS Y VOLCARLOS EN LA TABLA Y SABER CUANTOS TORNEOS HAY DENTRO DEL FICHERO
void crearFicheroTorneo()
{
    fstream fichero;
    fichero.open("torneo.dat", ios::binary | ios::in | ios::out);

    if (fichero.fail())
    {
        fichero.clear();
        fichero.close();

        fichero.open("torneo.dat", ios::binary | ios::out);
        fichero.close();

        fichero.open("torneo.dat", ios::binary | ios::in | ios::out);
        cout << "\n[+] Fichero de torneos creado: torneo.dat\n" << endl;

    }
    else
    {
        fichero.seekg(0, ios::end);
        int tamFichero = fichero.tellg();
        numTorneos = tamFichero / sizeof(TorneoAux);

        fichero.seekg(0, ios::beg);
        for(int i = 0; i < numTorneos; i++)
        {
            fichero.read((char*) &tablaTorneos[i], sizeof(TorneoAux));
        }
    }
}




void menuPrincipal()
{
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
        cout << "Indique la opcion deseada: ";
        cin >> opcMenuPrincipal;
        cin.ignore();

        switch (opcMenuPrincipal)
        {
        case 1:
            system("cls");
            cout << endl;
            cout << "=== LISTADO DE TORNEOS ACTIVOS ===" << endl;
            cout << endl;

            for(int i = 0; i < numTorneos; i++){
                cadena nombre;
                tablaTorneos[i].getNomTorneo(nombre);
                cout << nombre << endl;
            }

            system("pause");
            break;

        case 2:
        {
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

            cout << endl;
            cout << "[OK] Operacion de Alta Torneo Completada!!!" << endl;
            system("pause");

            break;

        }

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
    }
    while (opcMenuPrincipal != 4);
}

int main()
{
    crearFicheroTorneo();
    menuPrincipal();

    delete[] tablaTorneos;
    return 0;
}
