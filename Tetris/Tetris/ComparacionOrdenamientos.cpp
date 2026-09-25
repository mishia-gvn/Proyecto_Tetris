#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "Sorting.h"

using namespace std;
using namespace chrono;

void generarDatos(PlayersScore datos[], int cantidad) {

    for (int i = 0; i < cantidad; i++) {
        datos[i].name = "Jugador";
        datos[i].score = rand() % 100000;
    }
}

void probarInsertionSort(int cantidad) {

    PlayersScore* datos = new PlayersScore[cantidad];

    generarDatos(datos, cantidad);

    long comparaciones = 0;
    long movimientos = 0;

    auto inicio = high_resolution_clock::now();

    insertionSort(
        datos,
        cantidad,
        comparaciones,
        movimientos
    );

    auto fin = high_resolution_clock::now();

    auto tiempo = duration_cast<microseconds>(fin - inicio).count();

    cout << "Insertion Sort" << endl;
    cout << "Tiempo: " << tiempo << " microsegundos" << endl;
    cout << "Comparaciones: " << comparaciones << endl;
    cout << "Movimientos: " << movimientos << endl;
    cout << endl;

    delete[] datos;
}

void probarQuickSort(int cantidad) {

    PlayersScore* datos = new PlayersScore[cantidad];

    generarDatos(datos, cantidad);

    long comparaciones = 0;
    long intercambios = 0;

    auto inicio = high_resolution_clock::now();

    quickSort(
        datos,
        0,
        cantidad - 1,
        comparaciones,
        intercambios
    );

    auto fin = high_resolution_clock::now();

    auto tiempo = duration_cast<microseconds>(fin - inicio).count();

    cout << "Quick Sort" << endl;
    cout << "Tiempo: " << tiempo << " microsegundos" << endl;
    cout << "Comparaciones: " << comparaciones << endl;
    cout << "Intercambios: " << intercambios << endl;
    cout << endl;

    delete[] datos;
}

void ejecutarComparacion() {

    srand(static_cast<unsigned>(time(nullptr)));

    int cantidades[] = { 10, 100, 1000, 10000 };

    for (int i = 0; i < 4; i++) {

        int cantidad = cantidades[i];

        cout << "==============================" << endl;
        cout << "PRUEBA CON " << cantidad << " ELEMENTOS" << endl;
        cout << "==============================" << endl;

        probarInsertionSort(cantidad);
        probarQuickSort(cantidad);
    }
}