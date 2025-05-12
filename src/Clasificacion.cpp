#include "Clasificacion.h" // ESTO SE DEBE ESTUDIAR Y CORREGIR

// Constructor: inicializa la tabla con un tama�o = SALTO (4) y 0 jugadores
Clasificacion::Clasificacion() {
    elementos = new Jugador[SALTO];
    Jugadores = 0;
    tamano = SALTO;
}

// Destructor: libera la memoria din�mica
Clasificacion::~Clasificacion() {
    delete[] elementos;
}

// A�ade un jugador al final de la tabla din�mica
void Clasificacion::anadirjugador(Jugador j) {
    // Si est� llena, redimensionamos + SALTO
    if (Jugadores == tamano) {
        int nuevoTam = tamano + SALTO;
        // Creamos array temporal
        Jugador* temp = new Jugador[nuevoTam];
        // Copiamos los que ya ten�amos
        for (int i = 0; i < Jugadores; i++) {
            temp[i] = elementos[i];
        }
        // Liberamos el array antiguo
        delete[] elementos;
        // Actualizamos puntero y tama�o
        elementos = temp;
        tamano = nuevoTam;
    }

    // Insertamos el nuevo jugador al final
    elementos[Jugadores] = j;
    Jugadores++;
}

// Elimina el jugador en la posici�n i de la tabla din�mica
void Clasificacion::eliminar(int i) {
    if (i < 0 || i >= Jugadores) {
        cout << "[!] ERROR: La posici�n " << i << " no es v�lida para eliminar." << endl;
        return;
    }

    // Desplazamos todos los jugadores una posici�n hacia la izquierda
    for (int pos = i; pos < Jugadores - 1; pos++) {
        elementos[pos] = elementos[pos + 1];
    }
    Jugadores--;
}

// Consulta el jugador que est� en la posici�n n (0-based)
Jugador Clasificacion::consultar(int n) {
    if (n < 0 || n >= Jugadores) {
        cout << "[!] ERROR: La posici�n " << n << " no es v�lida para consultar." << endl;
        // Devolvemos uno �vac�o� como se�al de error
        Jugador j;
        j.indice = -1;
        j.resultado = 0;
        return j;
    }
    return elementos[n];
}

// Indica si la clasificaci�n est� vac�a
bool Clasificacion::vacio() {
    return (Jugadores == 0);
}

// Devuelve el n�mero de jugadores en la tabla
int Clasificacion::numjugadores() {
    return Jugadores;
}

// Ordena la tabla din�mica de menor a mayor "resultado" (burbuja)
void Clasificacion::ordenar() {
    bool cambio;
    do {
        cambio = false;
        for (int i = 0; i < Jugadores - 1; i++) {
            // Si encontramos dos resultados fuera de orden, los intercambiamos
            if (elementos[i].resultado > elementos[i + 1].resultado) {
                Jugador aux = elementos[i];
                elementos[i] = elementos[i + 1];
                elementos[i + 1] = aux;
                cambio = true;
            }
        }
    } while (cambio);
}
