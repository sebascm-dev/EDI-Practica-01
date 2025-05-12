#ifndef CLASIFICACION_H
#define CLASIFICACION_H

#include <iostream>
using namespace std;

#define SALTO 4

struct Jugador {
    int indice;
    int resultado;
};

class Clasificacion {
private:
    Jugador* elementos;
    int Jugadores;
    int tamano;

public:
    Clasificacion();
    ~Clasificacion();

    void anadirjugador(Jugador j);
    void eliminar(int i);
    Jugador consultar(int n);
    bool vacio();
    int numjugadores();
    void ordenar();
};

#endif // CLASIFICACION_H
