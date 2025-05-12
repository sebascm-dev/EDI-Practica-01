// INCLUDES IMPORTANTES
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>

// INCLUDES FICHEROS
#include "Torneo.h"
#include "Clasificacion.h"

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



bool Torneo::getGanadorTorneo(Golfista &g){
    fichero.close();
    fichero.open(nomFichero, ios::binary | ios::in | ios::out);

    if (fichero.fail()) {
        return false;
    }

    fichero.seekg(0, ios::beg);
    fichero.read((char*) &numGolfistas, sizeof(int));

    if (numGolfistas == 0) {
        fichero.close();
        return false;
    }

    bool torneoJugado = false;

    fichero.seekg(sizeof(int), ios::beg);
    fichero.read((char*) &g, sizeof(Golfista));

    if(g.golpes != 0) {
        torneoJugado = true;
        cout << "(EL TORNEO HA SIDO JUGADO)" << endl;

        Golfista aux;
        Golfista ganadorTorneo;

        fichero.seekg(sizeof(int), ios::beg);

        for(int i = 0; i < numGolfistas; i++){
            fichero.seekg(sizeof(int) + i * sizeof(Golfista));
            fichero.read((char*) &g, sizeof(Golfista));
            for(int j = 0; j < numGolfistas; j++){
                fichero.seekg(sizeof(int) + j * sizeof(Golfista));
                fichero.read((char*) &aux, sizeof(Golfista));
                if(g.resultado < aux.resultado){
                    ganadorTorneo = g;
                }
            }
        }

        g = ganadorTorneo;

        cout << "El ganador es: " << g.nombre << " " << g.apellidos << "\t--> Resultado: " << g.resultado << endl;
        cout << endl;
        return true;
    } else {
        cout << "(EL TORNEO NO HA SIDO JUGADO)";
        cout << endl;
        return false;
    }
    if(torneoJugado == false){
        return false;
    }
}



bool Torneo::exportarGanadores(Torneo t[], int numT, cadena nombreFichero){
    fstream ficheroTG;
    ficheroTG.open("ganadoresTorneo.dat", ios::binary | ios::in | ios::out);

    if (ficheroTG.fail()) {
        ficheroTG.clear();
        ficheroTG.close();

        ficheroTG.open("ganadoresTorneo.dat", ios::binary | ios::out);
        ficheroTG.close();

        ficheroTG.open("ganadoresTorneo.dat", ios::binary | ios::in | ios::out);
        cout << "\n[+] Fichero de torneos creado: ganadoresTorneo.dat\n" << endl;
    } else {
        int numeroGolfistasGanadores = 0;
        ficheroTG.seekp(0, ios::beg);
        ficheroTG.write((char*) &numeroGolfistasGanadores, sizeof(int));

        Golfista g;
        Golfista aux;
        Golfista ganadorTorneo;

        fichero.seekg(sizeof(int), ios::beg);

        for(int i = 0; i < numGolfistas; i++){
            fichero.seekg(sizeof(int) + i * sizeof(Golfista));
            fichero.read((char*) &g, sizeof(Golfista));
            for(int j = 0; j < numGolfistas; j++){
                fichero.seekg(sizeof(int) + j * sizeof(Golfista));
                fichero.read((char*) &aux, sizeof(Golfista));
                if(g.resultado < aux.resultado){
                    ganadorTorneo = g;
                }
            }
        }

        g = ganadorTorneo;

        ficheroTG.seekp(sizeof(int), ios::beg);
        ficheroTG.write((char*) &g, sizeof(Golfista));
        numeroGolfistasGanadores++;
    }
}

void Torneo::Clasificar() {
    // 1) Cerrar el fichero (por si estaba abierto) y reabrirlo en modo lectura-escritura
    fichero.close();
    fichero.open(nomFichero, ios::binary | ios::in | ios::out);

    if (fichero.fail()) {
        cout << "[!] ERROR: No se pudo abrir el fichero para clasificar." << endl;
        return;
    }

    // 2) Leer el número de golfistas al comienzo del fichero
    fichero.seekg(0, ios::beg);
    fichero.read((char*) &numGolfistas, sizeof(int));

    if (numGolfistas == 0) {
        cout << "[i] No hay golfistas inscritos. No hay nada que clasificar." << endl;
        fichero.close();
        return;
    }

    // 3) Creamos un objeto Clasificacion para guardar el índice y resultado de cada golfista
    Clasificacion clasif;

    // (Opcional) Iniciar la semilla de números aleatorios.
    srand((unsigned) time(nullptr));

    // 4) Para cada golfista:
    //    - Leemos su registro
    //    - Generamos golpes aleatorios
    //    - Calculamos resultado
    //    - Sobrescribimos en el fichero
    //    - Añadimos a la tabla dinámica de "Clasificacion"
    for (int i = 0; i < numGolfistas; i++) {
        // Calculamos el offset para este golfista en el fichero
        fichero.seekg(sizeof(int) + i * sizeof(Golfista), ios::beg);

        Golfista g;
        fichero.read((char*)&g, sizeof(Golfista));

        // Generar golpes aleatorios (puedes variar el rango)
        int golpesMin = 70;   // cerca de 72
        int golpesMax = 120;  // máximo imaginario
        g.golpes = golpesMin + rand() % (golpesMax - golpesMin + 1);

        // Calcular resultado: golpes - par (72)
        g.resultado = g.golpes - 72;

        // Sobrescribir ahora los datos actualizados en el fichero
        fichero.seekp(sizeof(int) + i * sizeof(Golfista), ios::beg);
        fichero.write((char*)&g, sizeof(Golfista));

        // Crear un Jugador con el índice en el fichero y el resultado calculado
        Jugador j;
        j.indice = i;               // i es la posición en el fichero (0-based)
        j.resultado = g.resultado;

        // Añadirlo a la Clasificacion
        clasif.anadirjugador(j);
    }

    // Ya terminamos de modificar/reescribir; cerramos el fichero
    fichero.close();

    // 5) Ordenar la clasificación (burbuja interna de la clase Clasificacion)
    clasif.ordenar();

    // 6) Mostrar la clasificación final en orden de menor a mayor resultado

    // Reabrimos el fichero solo en lectura para mostrar datos
    fichero.open(nomFichero, ios::binary | ios::in);
    if (fichero.fail()) {
        cout << "[!] ERROR: No se pudo reabrir el fichero para mostrar la clasificación." << endl;
        return;
    }

    int numeroGolfistas;
    fichero.read((char*)&numeroGolfistas, sizeof(int));

    cout << "=== CLASIFICACION FINAL DEL TORNEO ===" << endl;

    // Recorremos la tabla ya ordenada
    for (int k = 0; k < clasif.numjugadores(); k++) {
        // Consultamos al objeto clasif
        Jugador jj = clasif.consultar(k);

        // Leemos el golfista correspondiente desde el fichero
        fichero.seekg(sizeof(int) + jj.indice * sizeof(Golfista), ios::beg);

        Golfista g;
        fichero.read((char*)&g, sizeof(Golfista));

        cout << "\nPosicion " << (k + 1) << ": " << g.nombre << " " << g.apellidos << endl;
        cout << " Licencia: " << g.licencia << endl;
        cout << " Handicap: " << g.handicap << endl;
        cout << " Golpes:   " << g.golpes << endl;

        // Si quieres mostrar "PAR" cuando resultado == 0
        if (g.resultado == 0) {
            cout << " Resultado: PAR" << endl;
        } else if (g.resultado > 0) {
            cout << " Resultado: +" << g.resultado << endl;
        } else {
            // Es negativo
            cout << " Resultado: " << g.resultado << endl;
        }
    }

    fichero.close();
}
