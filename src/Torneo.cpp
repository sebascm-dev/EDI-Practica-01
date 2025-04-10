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
        cout << "[!] Fichero: " << nombreFichero << endl;
        cout << "[i] Numero de Golfistas: " << numGolfistas << endl;
        cout << endl;
    }
    strcpy(nomFichero, nombreFichero);

}



// M�todo Mostrar (PREGUNTAR AL PROFESOR POR QUE NO ME FUNCIONA CORRECTAMENTE SI QUITO EL FICHERO.CLOSE())
void Torneo::mostrar(float hdcp) {

    fichero.close(); // SI QUITO ESTO ME DA ERROR
    fichero.open(nomFichero, ios::binary | ios::in | ios::out); // SI QUITO ESTO ME DA ERROR

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



// M�todo Consultar
Golfista Torneo::consultar(int posicion) {

    Golfista g;

    if(posicion <= 0 || posicion > numGolfistas) {
        cout << "[!] ERROR: Posicion invalida. Debe estar entre 1 y " << numGolfistas << endl;
        return g;
    }

    fichero.seekg(sizeof(int) + sizeof(Golfista) * (posicion - 1), ios::beg);

    fichero.read((char*) &g, sizeof(Golfista));

    return g;
}



// M�todo Buscar (PREGUNTAR AL PROFESOR POR QUE NO ME FUNCIONA CORRECTAMENTE SI QUITO EL FICHERO.CLOSE())
int Torneo::buscar(cadena licencia) {

    fichero.close(); // SI QUITO ESTO ME DA ERROR
    fichero.open(nomFichero, ios::binary | ios::in); // SI QUITO ESTO ME DA ERROR

    if (numGolfistas == 0) {
        cout << "[!] No hay golfistas inscritos." << endl;
        return -1;
    }

    // Leer el n�mero de golfistas desde el inicio del fichero
    fichero.seekg(0, ios::beg);
    fichero.read((char*)&numGolfistas, sizeof(int));

    Golfista g;

    for (int i = 0; i < numGolfistas; i++) {
        fichero.read((char*)&g, sizeof(Golfista));

        if (strcmp(g.licencia, licencia) == 0) {
            return (i + 1);
        }
    }

    return -1;
}



// M�todo Insertar (PREGUNTAR AL PROFESOR POR QUE NO ME FUNCIONA CORRECTAMENTE SI QUITO EL FICHERO.CLOSE())
void Torneo::insertar(Golfista g) {
    // Cerramos y reabrimos el fichero en modo lectura/escritura binaria
    fichero.close();
    fichero.open(nomFichero, ios::binary | ios::in | ios::out);
    // Verificamos que no exista otro golfista con la misma licencia
    if(buscar(g.licencia) != -1) {
        cout << "[+] ERROR: Se ha encontrado una licencia igual. No se ha podido insertar el golfista dentro del torneo." << endl;
    } else {
        fichero.close();
        fichero.open(nomFichero, ios::binary | ios::in | ios::out);

        int posInsercion = 0;
        Golfista golfistaFichero;
        fichero.seekg(0, ios::beg);

        fichero.read((char*) &numGolfistas, sizeof(int));

        posInsercion = numGolfistas;

        for(int i = 0; i < numGolfistas  && posInsercion == numGolfistas; i++) {
            fichero.read((char*) &golfistaFichero, sizeof(Golfista));
            if(g.handicap < golfistaFichero.handicap) {
                posInsercion = i;
            }
        }
        cout << "[+] La posicion donde se insertara es el: " << posInsercion + 1 << endl;

        // Desplazamos desde atr�s hacia adelante para hacer espacio
        for(int i = numGolfistas - 1; i >= posInsercion; i--) {
            fichero.seekg(sizeof(int) + i * sizeof(Golfista), ios::beg);
            fichero.read((char*) &golfistaFichero, sizeof(Golfista));
            fichero.seekp(sizeof(int) + (i + 1) * sizeof(Golfista), ios::beg);
            fichero.write((char*) &golfistaFichero, sizeof(Golfista));
        }

        // Insertamos el nuevo golfista en la posici�n correcta
        fichero.seekp(sizeof(int) + (posInsercion * sizeof(Golfista)), ios::beg);
        fichero.write((char*) &g, sizeof(Golfista));

        // Actualizamos el n�mero de golfistas
        numGolfistas++;
        fichero.seekp(0, ios::beg);
        fichero.write((char*) &numGolfistas, sizeof(int));
    }
}



void modificar(Golfista c, int posicion) {

}


// M�todo Eliminar
// M�todo Clasifciar
