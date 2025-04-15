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
        cout << "[!] Fichero: " << nombreFichero << endl;
        cout << "[i] Numero de Golfistas: " << numGolfistas << endl;
        cout << endl;
    }
    strcpy(nomFichero, nombreFichero);

}



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

    // En lugar de while(...), leemos exactamente numGolfistas registros
    for(int i = 0; i < numGolfistas; i++) {
        fichero.read((char*)&g, sizeof(Golfista));

        // Filtramos por hdcp o mostramos todos
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



int Torneo::buscar(cadena licencia) {

    fichero.close(); // SI QUITO ESTO ME DA ERROR
    fichero.open(nomFichero, ios::binary | ios::in); // SI QUITO ESTO ME DA ERROR

    if (numGolfistas == 0) {
        cout << "[!] No hay golfistas inscritos." << endl;
        return -1;
    }

    // Leer el número de golfistas desde el inicio del fichero
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

        // Desplazamos desde atrás hacia adelante para hacer espacio
        for(int i = numGolfistas - 1; i >= posInsercion; i--) {
            fichero.seekg(sizeof(int) + i * sizeof(Golfista), ios::beg);
            fichero.read((char*) &golfistaFichero, sizeof(Golfista));
            fichero.seekp(sizeof(int) + (i + 1) * sizeof(Golfista), ios::beg);
            fichero.write((char*) &golfistaFichero, sizeof(Golfista));
        }

        // Insertamos el nuevo golfista en la posición correcta
        fichero.seekp(sizeof(int) + (posInsercion * sizeof(Golfista)), ios::beg);
        fichero.write((char*) &g, sizeof(Golfista));

        // Actualizamos el número de golfistas
        numGolfistas++;
        fichero.seekp(0, ios::beg);
        fichero.write((char*) &numGolfistas, sizeof(int));
    }
}



void Torneo::modificar(Golfista c, int posicion) {
    // 1. Comprobar si la posición es válida
    if (posicion <= 0 || posicion > numGolfistas) {
        cout << "[!] ERROR: La posición " << posicion << " no es válida." << endl;
        return;
    }

    // 2. Cerrar y volver a abrir el fichero en binario lectura/escritura
    fichero.close();
    fichero.open(nomFichero, ios::binary | ios::in | ios::out);
    if (fichero.fail()) {
        cout << "[!] ERROR: No se pudo abrir el fichero para modificar." << endl;
        return;
    }

    // 3. Leer el número de golfistas desde el fichero (por seguridad, aunque suele ser opcional
    //    si ya sabemos numGolfistas en memoria)
    int numeroGolfistasEnFichero;
    fichero.seekg(0, ios::beg);
    fichero.read((char*)&numeroGolfistasEnFichero, sizeof(int));

    // 4. Ir hasta la posición solicitada y leer el golfista original
    //    - posición en fichero = sizeof(int) + (posicion-1)*sizeof(Golfista)
    fichero.seekg(sizeof(int) + (posicion - 1) * sizeof(Golfista), ios::beg);

    Golfista original;
    fichero.read((char*)&original, sizeof(Golfista));

    // 5. Comprobar que sea el mismo golfista (opcional, según interpretación)
    //    Si quieres asegurarte de que no cambien la licencia a alguien totalmente distinto:
    if (strcmp(original.licencia, c.licencia) != 0) {
        cout << "[!] ERROR: La licencia que se desea modificar ("
             << c.licencia << ") no coincide con la del golfista en esa posición ("
             << original.licencia << ")." << endl;
        fichero.close();
        return;
    }

    // 6. Conservar el hándicap original: "No se admite en la modificación cambiar el hándicap"
    c.handicap = original.handicap;

    // 7. Volver al inicio de la zona a escribir (la misma posición) y sobrescribir el registro
    fichero.seekp(sizeof(int) + (posicion - 1) * sizeof(Golfista), ios::beg);
    fichero.write((char*)&c, sizeof(Golfista));

}



void Torneo::eliminar(int posicion) {
    // 1) Validar que la posición sea correcta
    if (posicion <= 0 || posicion > numGolfistas) {
        cout << "[!] ERROR: La posicion " << posicion << " no es valida. Debe estar entre 1 y " << numGolfistas << endl;
        return;
    }

    // 2) Cerrar y reabrir el fichero en binario (lectura/escritura)
    fichero.close();
    fichero.open(nomFichero, ios::binary | ios::in | ios::out);

    if (fichero.fail()) {
        cout << "[!] ERROR: No se pudo abrir el fichero para eliminar." << endl;
        return;
    }

    // 3) Leer el número de golfistas del fichero (para asegurarte de que coincida con numGolfistas)
    int numeroGolfistas;
    fichero.seekg(0, ios::beg);
    fichero.read((char*)&numeroGolfistas, sizeof(int));

    // 4) Desplazar a la izquierda todas las inscripciones que estén por detrás de la posición a eliminar
    Golfista g;
    for(int i = posicion - 1; i< numeroGolfistas - 1; i++) {
        // Leer el golfista que está en la posición i+1
        fichero.seekg(sizeof(int) + (i + 1) * sizeof(Golfista), ios::beg);
        fichero.read((char*)&g, sizeof(Golfista));

        // Escribirlo en la posición i
        fichero.seekp(sizeof(int) + i * sizeof(Golfista), ios::beg);
        fichero.write((char*)&g, sizeof(Golfista));
    }

    // 5) Actualizar la cantidad de golfistas
    numeroGolfistas--;
    fichero.seekp(0, ios::beg);
    fichero.write((char*)&numeroGolfistas, sizeof(int));

    // Sincronizar la variable interna de la clase también
    numGolfistas = numeroGolfistas;
}



// Método Clasifciar
