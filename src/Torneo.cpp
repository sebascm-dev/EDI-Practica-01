// INCLUDES IMPORTANTES
#include <iostream>
#include <fstream>
#include <cstring>

// INCLUDES FICHEROS
#include "Torneo.h"

using namespace std;



// Constructor y Destructor Clase Torneo
Torneo::Torneo(){}
Torneo::~Torneo(){}



// M�todos B�sicos
int Torneo::getNumGolfistas() { return numGolfistas; }
void Torneo::putNumGolfistas(int n) { numGolfistas = n; }



// Gesti�n de Nombres
void Torneo::getNomTorneo(cadena nombre) { strcpy(nombre, nomTorneo); }
void Torneo::getNomFichero(cadena nombre) { strcpy(nombre, nomFichero); }
void Torneo::putNomTorneo(cadena nombre) { strcpy(nomTorneo, nombre); }
void Torneo::putNomFichero(cadena nombre) { strcpy(nomFichero, nombre); }



// Gesti�n de Ficheros
void Torneo::crearFichero(char nombreFichero[]) {

    fichero.open(nombreFichero, ios::binary | ios::in | ios::out);

    if(fichero.fail()) {
        fichero.clear();
        fichero.close();

        fichero.open(nombreFichero, ios::binary | ios::out);
        numGolfistas = 0;
        fichero.write((char*) &numGolfistas, sizeof(int));
        fichero.close();

        fichero.open(nombreFichero, ios::binary | ios::in | ios::out);
    } else {
        fichero.seekg(0);
        fichero.read((char*) &numGolfistas, sizeof(int));
        cout << "[!] Fichero existente: " << nombreFichero << endl;
        cout << "[i] Numero de Golfistas: " << numGolfistas << endl;
        cout << endl;
    }
    strcpy(nomFichero, nombreFichero);

}



// M�todo Mostrar (Por Hacer)
void Torneo::mostrar(float hdcp) {
}



// M�todo Consultar (Por Hacer)
Golfista Torneo::consultar(int posicion) {
}



// M�todo Buscar (Por Hacer)
int Torneo::buscar(cadena licencia) {
}



// M�todo Insertar (Por Hacer)
void Torneo::insertar(Golfista g) {
}



// M�todo Modificar
// M�todo Eliminar
// M�todo Clasifciar
