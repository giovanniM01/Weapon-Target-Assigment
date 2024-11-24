#include "utils.h"
#include "greedy.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <set>
#include <unordered_set>
#include <chrono>
#include <fstream>

using namespace std;
using namespace chrono;

// Function to calculate the total expected damage
double calcularDanioTotal(const WTAInstance& instancia, const vector<int>& asignaciones) {
    double danioTotal = 0.0;
    for (int i = 0; i < instancia.numObjetivos; ++i) {
        int objetivo = asignaciones[i];
        danioTotal += instancia.penalizaciones[objetivo] * (1 - instancia.probabilidades[i][objetivo]);
    }
    return danioTotal;
}

// Swap function to generate a neighbor and calculate evaluation
vector<int> generarMovimientoSwap(const vector<int>& solucion, int i, int j) {
    vector<int> nuevaSolucion = solucion;
    swap(nuevaSolucion[i], nuevaSolucion[j]);
    return nuevaSolucion;
}

// Imprimir nombre columnas de la tabla iteraciones (opcional)
void printHeader() {
    cout << left << setw(6) << "It" 
         << setw(25) << "Sol-Actual" 
         << setw(22) << "Sol-Vecina" 
         << setw(12) << "Temp" 
         << setw(10) << "ΔF" 
         << setw(15) << "Probabilidad"
         << setw(12) << "Decisión"
         << setw(15) << "Danio-Actual"
         << setw(15) << "Danio Vecina" << endl;
    cout << string(110, '-') << endl;
}

// Simulated Annealing con First Improvement
vector<int> simulatedAnnealing(const WTAInstance& instancia, vector<int> solucionInicial, double temperaturaInicial, double factorEnfriamiento, int iteracionesMax) {
    vector<int> mejorSolucion = solucionInicial;
    vector<int> solucionActual = solucionInicial;
    double mejorDanio = calcularDanioTotal(instancia, solucionInicial);
    double danioActual = mejorDanio;
    double temperatura = temperaturaInicial;

    unordered_set<string> solucionesVisitadas;
    solucionesVisitadas.insert(vectorToString(solucionActual));

    // printHeader();

    int iteracionesAceptadas = 0;
    while (iteracionesAceptadas < iteracionesMax && temperatura > 1) {
        bool solucionAceptada = false;

        for (size_t i = 0; i < solucionActual.size() - 1 && !solucionAceptada; ++i) {
            for (size_t j = i + 1; j < solucionActual.size() && !solucionAceptada; ++j) {
                vector<int> solucionVecina = generarMovimientoSwap(solucionActual, i, j);
                string solucionVecinaStr = vectorToString(solucionVecina);
                if (solucionesVisitadas.count(solucionVecinaStr)) {
                    continue;
                }

                double danioVecino = calcularDanioTotal(instancia, solucionVecina);
                double deltaF = danioVecino - danioActual;

                double probabilidad = 1.0;
                string decision = "Aceptada";

                if (deltaF < 0) { 
                    solucionActual = solucionVecina;
                    danioActual = danioVecino;
                    solucionAceptada = true;
                    decision = "Mejora";
                    if (danioActual < mejorDanio) {
                        mejorSolucion = solucionActual;
                        mejorDanio = danioActual;
                    }
                }
                else { 
                    probabilidad = exp(-deltaF / temperatura);
                    if (((double) rand() / RAND_MAX) < probabilidad) {
                        solucionActual = solucionVecina;
                        danioActual = danioVecino;
                        solucionAceptada = true;
                    } else {
                        decision = "Rechazada";
                    }
                }

                solucionesVisitadas.insert(solucionVecinaStr);
                /*
                // Visualizar iteraciones
                cout << left << setw(6) << iteracionesAceptadas
                     << setw(25) << vectorToString(solucionActual)
                     << setw(25) << vectorToString(solucionVecina)
                     << setw(12) << fixed << setprecision(2) << temperatura
                     << setw(10) << deltaF
                     << setw(15) << fixed << setprecision(4) << probabilidad
                     << setw(12) << decision
                     << setw(15) << danioActual
                     << setw(15) << danioVecino << endl;
                */
                if (solucionAceptada) {
                    iteracionesAceptadas++;
                    break;
                }
            }
        }
        if (solucionAceptada) {
            temperatura *= factorEnfriamiento;
        }
    }

    return mejorSolucion;
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cerr << "Uso: ./swap T0 alpha iter_max archivo_instancia" << endl;
        return 1;
    }

    // Leer parámetros desde línea de comandos
    double temperaturaInicial = atof(argv[1]);
    double factorEnfriamiento = atof(argv[2]);
    int iteracionesMax = atoi(argv[3]);
    string archivoInstancia = argv[4];

    // Cargar la instancia desde el archivo
    WTAInstance instancia = leerInstancia(archivoInstancia);

    // Semilla aleatoria
    srand(time(0));

    // Generar solución inicial (Greedy)
    auto startG = high_resolution_clock::now();
    vector<int> solucionInicial = algoritmoGreedy(instancia);
    auto endG = high_resolution_clock::now();
    auto durationG = duration_cast<microseconds>(endG - startG).count();

    cout << "tiempo greedy: " << durationG << endl;

    // Ejecutar 5 veces
    for (int ejecucion = 1; ejecucion <= 5; ++ejecucion) {
        // Medir tiempo y ejecutar Simulated Annealing
        auto start = high_resolution_clock::now();
        vector<int> mejorSolucion = simulatedAnnealing(instancia, solucionInicial, temperaturaInicial, factorEnfriamiento, iteracionesMax);
        auto end = high_resolution_clock::now();

        // Calcular daño total
        double mejorDanio = calcularDanioTotal(instancia, mejorSolucion);
        auto duration = duration_cast<microseconds>(end - start).count();

        // Mostrar resultados
        cout << "Ejecución " << ejecucion << ": "
             << ", T0=" << temperaturaInicial
             << ", alpha=" << factorEnfriamiento
             << ", iter_max=" << iteracionesMax
             << ", daño_total=" << mejorDanio
             << ", tiempo_us=" << duration << endl;
    }

    return 0;
}
