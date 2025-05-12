#include "Clasificacion.h" // ESTO SE DEBE ESTUDIAR Y CORREGIR

// Constructor: inicializa la tabla con un tamaño = SALTO (4) y 0 jugadores
Clasificacion::Clasificacion() {
    elementos = new Jugador[SALTO];
    Jugadores = 0;
    tamano = SALTO;
}

// Destructor: libera la memoria dinámica
Clasificacion::~Clasificacion() {
    delete[] elementos;
}

// Añade un jugador al final de la tabla dinámica
void Clasificacion::anadirjugador(Jugador j) {
    // Si está llena, redimensionamos + SALTO
    if (Jugadores == tamano) {
        int nuevoTam = tamano + SALTO;
        // Creamos array temporal
        Jugador* temp = new Jugador[nuevoTam];
        // Copiamos los que ya teníamos
        for (int i = 0; i < Jugadores; i++) {
            temp[i] = elementos[i];
        }
        // Liberamos el array antiguo
        delete[] elementos;
        // Actualizamos puntero y tamaño
        elementos = temp;
        tamano = nuevoTam;
    }

    // Insertamos el nuevo jugador al final
    elementos[Jugadores] = j;
    Jugadores++;
}

// Elimina el jugador en la posición i de la tabla dinámica
void Clasificacion::eliminar(int i) {
    if (i < 0 || i >= Jugadores) {
        cout << "[!] ERROR: La posición " << i << " no es válida para eliminar." << endl;
        return;
    }

    // Desplazamos todos los jugadores una posición hacia la izquierda
    for (int pos = i; pos < Jugadores - 1; pos++) {
        elementos[pos] = elementos[pos + 1];
    }
    Jugadores--;
}

// Consulta el jugador que está en la posición n (0-based)
Jugador Clasificacion::consultar(int n) {
    if (n < 0 || n >= Jugadores) {
        cout << "[!] ERROR: La posición " << n << " no es válida para consultar." << endl;
        // Devolvemos uno “vacío” como señal de error
        Jugador j;
        j.indice = -1;
        j.resultado = 0;
        return j;
    }
    return elementos[n];
}

// Indica si la clasificación está vacía
bool Clasificacion::vacio() {
    return (Jugadores == 0);
}

// Devuelve el número de jugadores en la tabla
int Clasificacion::numjugadores() {
    return Jugadores;
}

// Ordena la tabla dinámica de menor a mayor "resultado" (burbuja)
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
