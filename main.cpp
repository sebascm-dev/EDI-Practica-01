#include <iostream>
#include <fstream>

#include "Torneo.h"

using namespace std;

#define N 10
#define SALTO 4

void menu1() {
    int torneos = 0;
    int decisionMenu1 = 0;

    do {
        system("cls");

        cout << "CLUB DE GOLF" << endl;
        cout << "------------------------------------" << endl;
        cout << "Torneos: " << torneos << endl;
        cout << endl;
        cout << "\t 1. Listado Torneos Abiertos" << endl;
        cout << "\t 2. Alta Torneo" << endl;
        cout << "\t 3. Elegir Torneo" << endl;
        cout << "\t 4. Salir" << endl;
        cout << endl;
        cout << "Indique la opcion deseada: ";

        cin >> decisionMenu1;

        switch (decisionMenu1) {

            case 1:
                system("cls");

                cout << endl;
                cout << "Listado de torneos abiertos:" << endl;
                break;


            case 2:
                system("cls");

                cout << endl;
                cout << "Alta de nuevo torneo:" << endl;
                break;


            case 3:
                system("cls");

                cout << endl;
                cout << "Eleccion de torneo:" << endl;
                break;


            case 4:
                system("cls");

                cout << endl;
                cout << "Saliendo de la aplicacion..." << endl;
                break;


            default:
                system("cls");

                cout << endl;
                cout << "Opcion no valida. Por favor, seleccione una opcion del 1 al 4." << endl;
                break;
        }

        if (decisionMenu1 != 4) {
            cout << endl;
            cout << "Presione Enter para continuar...";
            cin.ignore();
            cin.get();
        }

    } while (decisionMenu1 != 4);
}

int main() {

    //menu1();

    Torneo t1;
    t1.CrearFichero("Open Huelva");
    t1.mostrar(2);

    return 0;
}
