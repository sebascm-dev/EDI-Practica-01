// SEBASTIAN CONTRERAS MARIN - spanolocabo@gmail.com

// INCLUDES IMPORTANTES
#include <iostream>
#include <fstream>
#include <cstring>

// INCLUDES DE FICHEROS DE CLASES
#include "Torneo.h"

// USO DEL NAMESPACE
using namespace std;

// CONSTANTES DE REMPLAZO
#define N 10
#define SALTO 4

// DEFINICION DE TIPOS
typedef char cadena[30];

// VARIABLES
int numTorneos;
cadena nuevoNombreTorneo, nuevoNombreFichero;
Torneo* tablaTorneos = new Torneo[N];

// DEFINICION DE STRUCTS
struct TorneoAux {
    int numGolfistasAux;
    cadena nomTorneoAux;
    cadena nomFicheroAux;
};



// CREACION DEL FICHERO TORNEOS.DAT
void crearFicheroTorneo() {
    fstream fichero;
    fichero.open("torneo.dat", ios::binary | ios::in | ios::out);

    if (fichero.fail()) {
        fichero.clear();
        fichero.close();

        fichero.open("torneo.dat", ios::binary | ios::out);
        fichero.close();

        fichero.open("torneo.dat", ios::binary | ios::in | ios::out);
        cout << "\n[+] Fichero de torneos creado: torneo.dat\n" << endl;
    } else {
        fichero.seekg(0, ios::end);
        int tamFichero = fichero.tellg();
        numTorneos = tamFichero / sizeof(TorneoAux);

        fichero.seekg(0, ios::beg);
        for(int i = 0; i < numTorneos; i++) {
            TorneoAux aux;
            fichero.read((char*) &aux, sizeof(TorneoAux));
            tablaTorneos[i].putNomTorneo(aux.nomTorneoAux);
            tablaTorneos[i].putNomFichero(aux.nomFicheroAux);
        }
    }
    fichero.close();
}



// MANEJO DEL PROGRAMA MEDIANTE MENUS
void menuPrincipal() {

    int opcMenuPrincipal;

    do{
        system("cls");
        cout << "=== TORNEOS DE GOLF ===" << endl;
        cout << "-----------------------" << endl;
        cout << "Torneos: " << numTorneos << endl;
        cout << endl;
        cout << "\t1. Listado de Torneos" << endl;
        cout << "\t2. Alta Torneo" << endl;
        cout << "\t3. Elegir torneo" << endl;
        cout << "\t4. ExportarGanadores y Mostrarlos" << endl;
        cout << "\t5. Salir" << endl;
        cout << endl;
        cout << "Indique la opcion deseada: "; cin >> opcMenuPrincipal; cin.ignore();

        switch (opcMenuPrincipal) {

            case 1:{

                system("cls");
                cout << endl;
                cout << "=== LISTADO DE TORNEOS ACTIVOS ===" << endl;
                cout << endl;

                for(int i = 0; i < numTorneos; i++){
                    cadena nombre, fichero;
                    tablaTorneos[i].getNomTorneo(nombre);
                    tablaTorneos[i].getNomFichero(fichero);
                    cout << (i+1) << ". " << nombre << " --->\t(Archivo: " << fichero << ")" << endl;
                }

                cout << endl;
                system("pause");
                break;
            }

            case 2: {

                system("cls");
                cout << endl;
                cout << "=== DAR UN TORNEO DE ALTA ===" << endl;
                cout << endl;

                Torneo nuevoTorneo;
                TorneoAux Taux;

                cout << "[/] Introduzca nombre del torneo a dar de alta: ";
                cin.getline(nuevoNombreTorneo, 30);
                nuevoTorneo.putNomTorneo(nuevoNombreTorneo);

                cout << "[/] Introduzca nombre del fichero para el torneo: ";
                cin.getline(nuevoNombreFichero, 30);

                strcat(nuevoNombreFichero, ".dat");
                nuevoTorneo.putNomFichero(nuevoNombreFichero);

                cout << endl;
                cout << "[+] Torneo " << nuevoNombreFichero << " creado correctamente!" << endl;
                nuevoTorneo.crearFichero(nuevoNombreFichero);

                cout << "[+] Insertando datos del torneo " << nuevoNombreTorneo << " en el fichero torneo.dat" << endl;
                Taux.numGolfistasAux = nuevoTorneo.getNumGolfistas();
                strcpy(Taux.nomTorneoAux, nuevoNombreTorneo);
                strcpy(Taux.nomFicheroAux, nuevoNombreFichero);

                fstream fichero;
                fichero.open("torneo.dat", ios::binary | ios::in | ios::out);

                fichero.seekp(0, ios::end);
                fichero.write((char*) &Taux, sizeof(TorneoAux));

                fichero.seekg(0, ios::end);
                int tamFichero = fichero.tellg();
                numTorneos = tamFichero / sizeof(TorneoAux);

                fichero.seekg(0, ios::beg);
                for(int i = 0; i < numTorneos; i++) {
                    TorneoAux aux;
                    fichero.read((char*) &aux, sizeof(TorneoAux));
                    tablaTorneos[i].putNomTorneo(aux.nomTorneoAux);
                    tablaTorneos[i].putNomFichero(aux.nomFicheroAux);
                }
                fichero.close(); // AÑADIDO

                cout << endl;
                cout << "[OK] Operacion de Alta Torneo Completada!!!" << endl;
                system("pause");

                break;
            }

            case 3: {

                system("cls");
                cout << endl;
                cout << "=== LISTADO DE TORNEOS ACTIVOS ===" << endl;
                cout << endl;

                for(int i = 0; i < numTorneos; i++){
                    cadena nombre, fichero;
                    tablaTorneos[i].getNomTorneo(nombre);
                    tablaTorneos[i].getNomFichero(fichero);
                    cout << (i+1) << ". " << nombre << " --->\t(Archivo: " << fichero << ")" << endl;
                }


                int elegirTorneo;
                cout << endl;
                cout << "Elija el torneo: "; cin >> elegirTorneo; cout << endl;
                elegirTorneo--;

                if(elegirTorneo < numTorneos) {
                    cadena nombreFichero, nombreTorneo;
                    int numGolfistas;
                    Torneo eleccionTorneo;

                    for(int i = 0; i < numTorneos ; i++){
                        if(elegirTorneo == i){
                            tablaTorneos[i].getNomFichero(nombreFichero);
                            eleccionTorneo.putNomFichero(nombreFichero);
                            eleccionTorneo.getNomFichero(nombreFichero);

                            tablaTorneos[i].getNomTorneo(nombreTorneo);
                            eleccionTorneo.putNomTorneo(nombreTorneo);
                            eleccionTorneo.getNomTorneo(nombreTorneo);

                            fstream archivoElegido;
                            archivoElegido.open(nombreFichero, ios::binary | ios::in | ios::out);

                            archivoElegido.seekg(0, ios::beg);
                            archivoElegido.read((char*) &numGolfistas, sizeof(int));

                            eleccionTorneo.putNumGolfistas(numGolfistas);
                            archivoElegido.close();
                        }
                    }

                    int menuOpc2 = 0;
                    do{

                        system("cls");
                        cout << endl;

                        cout << "Torneo " << nombreTorneo << endl;
                        cout << "----------------------------------------------" << endl;
                        cout << "Golfistas: " << numGolfistas << endl;

                        cout << endl;

                        cout << "\t1. Consulta de Inscripciones" << endl;
                        cout << "\t2. Inscripcion al Torneo" << endl;
                        cout << "\t3. Busqueda de una Inscripcion" << endl;
                        cout << "\t4. Modificar Datos de una Inscripcion" << endl;
                        cout << "\t5. Eliminar una Inscripcion" << endl;
                        cout << "\t6. Mostrar Resultados del Torneo" << endl;
                        cout << "\t7. Salir" << endl;

                        cout << endl;

                        Golfista g;
                        eleccionTorneo.getGanadorTorneo(g);

                        cout << "Indique la opcion deseada: "; cin >> menuOpc2; cin.ignore();


                        system("cls");
                        switch(menuOpc2){

                            case 1: {
                                cout << endl;
                                cout << "=== CONSULTA DE INSCRIPCIONES EN " << nombreTorneo << " ===" << endl;
                                cout << endl;

                                float handicapBuscado;

                                cout << "[?] Introduzca el handicap a consultar (-1 para mostrar todos): ";
                                cin >> handicapBuscado;
                                cin.ignore();
                                cout << endl;

                                eleccionTorneo.mostrar(handicapBuscado);

                                cout << endl;
                                system("pause");
                                break;
                            }

                            case 2: {
                                cout << endl;
                                cout << "=== INSCRIPCION AL TORNEO " << nombreTorneo << " ===" << endl;
                                cout << endl;

                                Golfista nuevoGolfista;

                                cout << "[+] Introduzca un nombre: "; cin.getline(nuevoGolfista.nombre, 30);
                                cout << "[+] Introduzca un apellido: "; cin.getline(nuevoGolfista.apellidos, 30);
                                cout << "[+] Introduzca una licencia: "; cin.getline(nuevoGolfista.licencia, 30);
                                cout << "[+] Introduzca su handicap: "; cin >> nuevoGolfista.handicap;
                                cout << endl;

                                nuevoGolfista.golpes = 0;
                                nuevoGolfista.resultado = 0;

                                eleccionTorneo.insertar(nuevoGolfista);

                                numGolfistas++;

                                cout << "[i] Golfista introducido con exito!" << endl;

                                cout << endl;
                                system("pause");
                                break;
                            }

                            case 3: {
                                cout << endl;
                                cout << "=== BUSQUEDA DE UNA INSCRIPCION EN " << nombreTorneo << " ===" << endl;
                                cout << endl;

                                cadena licencia;

                                cout << "[i] Introduzca la licencia del golfista: "; cin.getline(licencia, 30);

                                int posicion = eleccionTorneo.buscar(licencia);

                                if(posicion != -1) {
                                    Golfista encontrarGolfista = eleccionTorneo.consultar(posicion);

                                    cout << endl;
                                    cout << "X--- " << encontrarGolfista.nombre << " " << encontrarGolfista.apellidos << " ---X" << endl;
                                    cout << "| Licencia: " << encontrarGolfista.licencia << endl;
                                    cout << "| Handicap: " << encontrarGolfista.handicap << endl;
                                    cout << "| Golpes: " << encontrarGolfista.golpes << endl;
                                    cout << "| Resultado: " << encontrarGolfista.resultado << endl;
                                } else {
                                    cout << endl;
                                    cout << "[!] El golfista no se encuentra dentro del torneo." << endl;
                                }

                                cout << endl;
                                system("pause");
                                break;
                            }

                            case 4: {
                                cout << endl;
                                cout << "=== MODIFICAR DATOS DE UNA INSCRIPCION ===" << endl;
                                cout << endl;

                                cadena licencia;
                                cout << "[?] Introduzca la licencia del golfista a modificar: ";
                                cin.getline(licencia, 30);
                                cout << endl;

                                // 1. Buscar su posición en el fichero
                                int pos = eleccionTorneo.buscar(licencia);

                                if (pos == -1) {

                                    cout << "[!] El golfista con licencia " << licencia << " no se encuentra inscrito en el torneo." << endl;

                                } else {

                                    // 2. Consultar los datos actuales (para poder conservar el handicap)
                                    Golfista actual = eleccionTorneo.consultar(pos);

                                    // Mostrar brevemente los datos que tenía antes
                                    cout << "X--- " << actual.nombre << " " << actual.apellidos << " ---X" << endl;
                                    cout << "| Licencia: " << actual.licencia << endl;
                                    cout << "| Handicap: " << actual.handicap << endl;
                                    cout << "| Golpes: " << actual.golpes << endl;
                                    cout << "| Resultado: " << actual.resultado << endl;
                                    cout << endl;

                                    // 3. Pedir los datos nuevos.
                                    Golfista modificado;

                                    // Copiamos la licencia y handicap ANTES, para que no se pierdan.
                                    strcpy(modificado.licencia, actual.licencia);
                                    modificado.handicap = actual.handicap;

                                    // Ahora pedimos sólo los datos que se pueden cambiar
                                    cout << "[+] Introduzca el nuevo nombre: ";
                                    cin.getline(modificado.nombre, 30);

                                    cout << "[+] Introduzca el nuevo apellido: ";
                                    cin.getline(modificado.apellidos, 30);

                                    cout << "[+] Introduzca los nuevos golpes: ";
                                    cin >> modificado.golpes;
                                    cin.ignore();

                                    cout << "[+] Introduzca el nuevo resultado: ";
                                    cin >> modificado.resultado;
                                    cin.ignore();

                                    // 4. Llamar al método modificar, pasando el Golfista “modificado” y la posición
                                    eleccionTorneo.modificar(modificado, pos);

                                    cout << endl;
                                    cout << "[OK] Modificacion realizada." << endl;
                                }

                                cout << endl;
                                system("pause");
                                break;
                            }

                            case 5: {
                                cout << endl;
                                cout << "=== ELIMINAR INSCRIPCION AL TORNEO ===" << endl;
                                cout << endl;

                                cadena licencia;
                                cout << "[?] Introduzca la licencia del golfista a eliminar: ";
                                cin.getline(licencia, 30);
                                cout << endl;

                                int posicion = eleccionTorneo.buscar(licencia);

                                if (posicion == -1) {

                                    cout << "[!] El golfista con licencia " << licencia << " no se encuentra inscrito en el torneo." << endl;

                                } else {

                                    eleccionTorneo.eliminar(posicion);

                                    numGolfistas--;

                                    cout << "[+] Golfista eliminado con exito" << endl;

                                }

                                cout << endl;
                                system("pause");
                                break;
                            }

                            case 6: {
                                cout << "=== MOSTRAR RESULTADOS DEL TORNEO ===" << endl << endl;

                                eleccionTorneo.Clasificar(); // Simula el torneo y muestra la clasificación
                                cout << endl;

                                system("pause");
                                break;
                            }

                        }
                    } while(menuOpc2 != 7);

                } else {
                    cout << "[!] ERROR: No se encuentra el torneo insertado." << endl;
                    system("pause");
                }

                break;
            }

            case 4: {

                system("cls");
                cout << endl;
                cout << "=== EXPORTANDO Y MOSTRANDO GANADORES ===" << endl;
                cout << endl;

                for(int i = 0; i < numTorneos; i++){
                    cadena nombre, fichero;
                    tablaTorneos[i].getNomTorneo(nombre);
                    tablaTorneos[i].getNomFichero(fichero);
                }

                system("cls");
                cout << endl;
                break;
            }

            case 5: {

                system("cls");
                cout << endl;
                cout << "=== SALIENDO DEL PROGRAMAM ===" << endl;
                break;
            }

            default: {

                cout << "[!] ERROR: Escriba un valor valido..." << endl;
                break;
            }

        }
    } while (opcMenuPrincipal != 5);
}



int main()
{
    crearFicheroTorneo();

    menuPrincipal();

    delete[] tablaTorneos;

    return 0;
}
