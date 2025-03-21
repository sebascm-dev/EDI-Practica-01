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



// Métodos Básicos
int Torneo::getNumGolfistas() { return numGolfistas; }
void Torneo::putNumGolfistas(int n) { numGolfistas = n; }



// Gestión de Nombres
void Torneo::getNomTorneo(cadena nombre) { strcpy(nombre, nomTorneo); }
void Torneo::getNomFichero(cadena nombre) { strcpy(nombre, nomFichero); }
void Torneo::putNomTorneo(cadena nombre) { strcpy(nomTorneo, nombre); }
void Torneo::putNomFichero(cadena nombre) { strcpy(nomFichero, nombre); }



// Gestión de Ficheros
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



// Método Mostrar
void Torneo::mostrar(float hdcp) {

    if(fichero.fail()) {
        cout << "[!] ERROR: No se pudo abrir el fichero " << nomFichero << endl;
        return;
    }

    fichero.seekg(0, ios::beg);
    fichero.read((char*) &numGolfistas, sizeof(int));

    if(numGolfistas == 0) {
        cout << "[i] No hay golfistas registrados en este torneo." << endl;
        return;
    }

    cout << "=== LISTADO DE GOLFISTAS ";
    if(hdcp == -1) {
        cout << "(TODOS) ===" << endl;
    } else {
        cout << "(HANDICAP "<< hdcp << ") ===" << endl;
    }

    Golfista g;
    int encontrados = 0;

    while(fichero.read((char*) &g, sizeof(Golfista))) {
        if(hdcp == -1 || g.handicap == hdcp) {
            cout << endl;
            cout << "X--- " << g.nombre << " " << g.apellidos << " ---X" << endl;
            cout << "| Licencia: " << g.licencia << endl;
            cout << "| Handicap: " << g.handicap << endl;
            cout << "| Golpes: " << g.golpes << endl;
            cout << "| Resultado: " << g.resultado << endl;
            cout << endl;
            encontrados++;
        }
    }

    if(encontrados == 0) {
        cout << "[i] No se encontraron golfistas con el handicap: " << hdcp << endl;
    } else {
        cout << "=============================" << endl;
        cout << "[i] Total de Golfistas Mostrados: " << encontrados << endl;
    }
}



// Método Consultar (Por Hacer)
Golfista Torneo::consultar(int posicion) {
}



// Método Buscar (Por Hacer)
int Torneo::buscar(cadena licencia) {
}



// Método Insertar (Por Hacer)
void Torneo::insertar(Golfista g) {
}



// Método Modificar
// Método Eliminar
// Método Clasifciar
