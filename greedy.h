#ifndef GREEDY_H
#define GREEDY_H

#include <vector>
#include <string>

// Definición de la estructura WTAInstance
struct WTAInstance {
    int numObjetivos;
    std::vector<int> penalizaciones;
    std::vector<std::vector<double>> probabilidades;
};

// Declaración de funciones
WTAInstance leerInstancia(const std::string& filename);
std::vector<int> algoritmoGreedy(const WTAInstance& instancia);

// Función para imprimir un vector como cadena
std::string vectorToString(const std::vector<int>& vec);

#endif // GREEDY_H
