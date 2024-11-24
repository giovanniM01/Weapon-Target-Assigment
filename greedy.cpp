/*
    Giovanni Mealla
    02-11-2024
    Algoritmo Greedy - WTA problem
*/

#include "utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <set>
#include <chrono>
#include <iomanip> // Para formato de salida
#include <sstream>

using namespace std;


// Estructura para almacenar los datos de una instancia
struct WTAInstance {
    int numObjetivos;                      // Número de armas y objetivos
    vector<int> penalizaciones;             // Penalización V_j para cada objetivo
    vector<vector<double>> probabilidades;  // Matriz de probabilidades P_ij
};

// Función para leer el archivo de entrada y cargar los datos en una estructura WTAInstance
WTAInstance leerInstancia(const string& filename) {
    ifstream file(filename);
    WTAInstance instancia;

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    file >> instancia.numObjetivos;

    // Leer penalizaciones
    instancia.penalizaciones.resize(instancia.numObjetivos);
    for (int i = 0; i < instancia.numObjetivos; ++i) {
        file >> instancia.penalizaciones[i];
    }

    // Leer matriz de probabilidades
    instancia.probabilidades.resize(instancia.numObjetivos, vector<double>(instancia.numObjetivos));
    for (int i = 0; i < instancia.numObjetivos; ++i) {
        for (int j = 0; j < instancia.numObjetivos; ++j) {
            file >> instancia.probabilidades[i][j];
        }
    }

    file.close();
    return instancia;
}

// Función para imprimir la matriz de probabilidades con encabezados
void imprimirMatrizProbabilidades(const WTAInstance& instancia) {
    cout << "Matriz de Probabilidades (P_ij):" << endl;

    // Encabezado de columnas
    cout << setw(15) << "Armas/Objetivos";
    for (int j = 0; j < instancia.numObjetivos; ++j) {
        cout << setw(8) << "Obj " << j + 1;
    }
    cout << endl;

    // Fila de penalizaciones
    cout << setw(15) << "Penalización";
    for (int j = 0; j < instancia.numObjetivos; ++j) {
        cout << setw(8) << instancia.penalizaciones[j];
    }
    cout << endl;

    // Imprimir filas de probabilidades
    for (int i = 0; i < instancia.numObjetivos; ++i) {
        cout << setw(15) << "Arma " << i + 1;
        for (int j = 0; j < instancia.numObjetivos; ++j) {
            cout << setw(8) << fixed << setprecision(4) << instancia.probabilidades[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// Función para imprimir la matriz de daño esperado para cada arma y objetivo con encabezados
void imprimirMatrizDanioEsperado(const WTAInstance& instancia) {
    cout << "Matriz de Danio Esperado (E) para cada arma y objetivo:" << endl;

    // Encabezado de columnas
    cout << setw(15) << "Armas/Objetivos";
    for (int j = 0; j < instancia.numObjetivos; ++j) {
        cout << setw(8) << "Obj " << j + 1;
    }
    cout << endl;

    // Imprimir filas de daño esperado
    for (int i = 0; i < instancia.numObjetivos; ++i) {
        cout << setw(15) << "Arma " << i + 1;
        for (int j = 0; j < instancia.numObjetivos; ++j) {
            double danioEsperado = instancia.penalizaciones[j] * (1 - instancia.probabilidades[i][j]);
            cout << setw(8) << fixed << setprecision(4) << danioEsperado;
        }
        cout << endl;
    }
    cout << endl;
}

// Función para aplicar el algoritmo Greedy
vector<int> algoritmoGreedy(const WTAInstance& instancia) {
    int N = instancia.numObjetivos;
    vector<int> asignaciones(N, -1);      // Almacena el objetivo asignado a cada arma
    set<int> objetivosAsignados;          // Conjunto de objetivos que ya han sido asignados
    double totalDanioEsperado = 0.0;

    for (int i = 0; i < N; ++i) {
        double minDanio = numeric_limits<double>::infinity();
        int mejorObjetivo = -1;

        // Buscar el objetivo que minimice el daño esperado para el arma actual
        for (int j = 0; j < N; ++j) {
            if (objetivosAsignados.find(j) == objetivosAsignados.end()) { // Si el objetivo no ha sido asignado
                double danioEsperado = instancia.penalizaciones[j] * (1 - instancia.probabilidades[i][j]);
                if (danioEsperado < minDanio) {
                    minDanio = danioEsperado;
                    mejorObjetivo = j;
                }
            }
        }

        // Asignar el objetivo que minimiza el daño esperado para la arma actual
        asignaciones[i] = mejorObjetivo;
        objetivosAsignados.insert(mejorObjetivo);
        totalDanioEsperado += minDanio;
    }

    cout << "Danio total esperado Greedy: " << totalDanioEsperado << endl;
    return asignaciones;
}