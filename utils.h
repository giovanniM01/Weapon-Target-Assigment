#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <sstream>

// Declarar la función como inline para evitar errores de múltiples definiciones
inline std::string vectorToString(const std::vector<int>& vec) {
    std::ostringstream oss;
    for (int val : vec) {
        oss << (val + 1) << " "; // Mostrar desde 1 en vez de 0
    }
    return oss.str();
}

#endif // UTILS_H
