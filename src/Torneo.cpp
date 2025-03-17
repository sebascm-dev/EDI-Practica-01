#include <iostream>
#include <fstream>
#include <cstring>
#include "Torneo.h"

using namespace std;

// Constructor y Destructor de la clase Torneo
Torneo::Torneo(){}
Torneo::~Torneo(){}

// Métodos Básicos
int Torneo::getNumGolfistas() { return numGolfistas; }
void Torneo::putNumGolfistas(int n) { numGolfistas = n; }

// Gestión de Nombres
void Torneo::getNomTorneo(cadena nombre) { strcpy(nombre, nomTorneo); }
void Torneo::getNomFichero(cadena nombre) { strcpy(nombre, nomFichero); }
void Torneo::putNomTorneo(cadena nombre) { strcpy(nomTorneo, nombre); }
void Torneo::putNomFichero(cadena nombre) { strcpy(nomFichero, nombre); }

// Gestión de Ficheros
void Torneo::CrearFichero(char nombreFichero[]) {
    fstream fichero(nombreFichero, ios::binary | ios::in | ios::out);

    if(fichero.fail()) {
        fichero.clear();
        fichero.close();

        fichero.open(nombreFichero, ios::binary | ios::out);
        numGolfistas = 0;
        fichero.write((char*) &numGolfistas, sizeof(int));
        fichero.close();

        fichero.open(nombreFichero, ios::binary | ios::in | ios::out);

        cout << endl;
        cout << "[+] El Fichero " << nombreFichero << " se ha creado correctamente!" << endl;

    } else {
        cout << endl;
        cout << "[!] El Fichero " << nombreFichero << " ya existe..." << endl;

        cout << endl;
        fichero.seekg(0);
        fichero.read((char*) &numGolfistas, sizeof(int));
    }
}

// Método Mostrar
void Torneo::mostrar(float hdcp) {
    if(numGolfistas == 0) {
        cout << "[!] No hay golfistas inscritos." << endl;
        return;
    }

    Golfista* buffer = new Golfista[numGolfistas];

    fichero.seekg(sizeof(int), ios::beg);
    fichero.read((char*) buffer, numGolfistas * sizeof(Golfista));

    for(int i = 0; i < numGolfistas; i++) {
        if(hdcp == -1 || buffer[i].handicap == hdcp) {
            cout << "Licencia: " << buffer[i].licencia << endl
                 << "Handicap: " << buffer[i].handicap << endl
                 << "Nombre: " << buffer[i].nombre << " " << buffer[i].apellidos << endl
                 << "X=================================X" << endl;
        }
    }
    delete[] buffer;
}

// Método Consultar
Golfista Torneo::consultar(int posicion) {
    Golfista g;
    if(posicion < 1 || posicion > numGolfistas) {
        return g;
    }

    fichero.seekg(sizeof(int) + (posicion - 1) * sizeof(Golfista));
    fichero.read((char*) &g, sizeof(Golfista));
    return g;
}

// Método Buscar
int Torneo::buscar(cadena licencia) {
    if(numGolfistas == 0) {
        return -1;
    }

    Golfista* buffer = new Golfista[numGolfistas];
    fichero.seekg(sizeof(int), ios::beg);
    fichero.read((char*) buffer, numGolfistas * sizeof(Golfista));

    for(int i = 0; i < numGolfistas; i++) {
        if(strcmp(buffer[i].licencia, licencia) == 0) {
            delete[] buffer;
            return i + 1;
        }
    }
    delete[] buffer;
    return -1;
}

// Método Insertar
// Método Modificar
// Método Eliminar
// Método Clasifciar
