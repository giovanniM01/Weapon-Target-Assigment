# Weapon Target Assignment Problem (WTAP)

Este proyecto implementa el algoritmo de **Simulated Annealing (SA)** para resolver el **problema de asignación de armas a objetivos (WTAP)**. Se utiliza una solución inicial generada mediante un enfoque **Greedy**, optimizando el daño total esperado.

## Características

- **Solución Inicial Greedy**: Genera una asignación inicial de armas a objetivos utilizando un enfoque Greedy.
- **Optimización con Simulated Annealing**: Refina la solución inicial aplicando el algoritmo de Simulated Annealing.
- **Parámetros Personalizables**: Permite ajustar la temperatura inicial, el factor de enfriamiento y el número máximo de iteraciones.
- **Pruebas con Diferentes Instancias**: Se incluyen archivos de prueba (`wta10.txt`, `wta50.txt`, etc.) para evaluar el algoritmo en diversas situaciones.
- **Resultados Detallados**:
  - Daño total esperado.
  - Tiempo de ejecución del enfoque Greedy y Simulated Annealing.
  - Ejecuciones repetidas para medir consistencia y desempeño.

## Contenido del Repositorio

- **Código fuente**:
  - `swap.cpp`: Implementación del algoritmo Simulated Annealing.
  - `greedy.cpp` y `greedy.h`: Implementación del enfoque Greedy.
  - `utils.h`: Funciones auxiliares para la lectura de instancias.
- **Instancias del problema**: Archivos de prueba como `wta10.txt`, `wta50.txt`, etc.
- **Makefile**: Archivo para compilar el proyecto.

## Requisitos Previos

- Compilador compatible con **C++17** (ejemplo: `g++`).
- Entorno probado en **Linux**.

## Instrucciones de Instalación

1. Abre una terminal en la carpeta raíz del proyecto.
2. Ejecuta el siguiente comando para instalar y compilar:

   ```bash
   make


  Esto generará un ejecutable llamado `swap`.

3. Si deseas limpiar los archivos compilados, utiliza:
   ```bash
   make clean

Cómo ejecutar el proyecto
-------------------------
El programa requiere varios parámetros para ejecutarse. El formato general del 
comando es:

    ./swap T0 alpha iter_max archivo_instancia

Donde:
- `T0`: Temperatura inicial para el algoritmo de Simulated Annealing (ejemplo: 50).
- `alpha`: Factor de enfriamiento (ejemplo: 0.9).
- `iter_max`: Número máximo de iteraciones (ejemplo: 50).
- `archivo_instancia`: Ruta al archivo de instancia del problema (ejemplo: wta50.txt).

Ejemplo de ejecución
--------------------
Para ejecutar el algoritmo con una temperatura inicial de 50, un factor de 
enfriamiento de 0.9, un máximo de 50 iteraciones, y utilizando la instancia 
`wta50.txt`:

    ```bash
    ./swap 50 0.9 50 wta50.txt

La salida mostrará resultados como:

     ```bash
     Danio total esperado Greedy: 427.045
     
     tiempo greedy: 12345
     
     Ejecución 1: T0=50, alpha=0.9, iter_max=50, daño_total=345.67, tiempo_us=56789
     
     Ejecución 2: ...

Notas adicionales
-----------------
- Las soluciones iniciales se generan utilizando el enfoque Greedy.
- El algoritmo de Simulated Annealing se ejecuta cinco veces por defecto.
- La métrica principal es el daño total esperado y su tiempo, que se calculan como parte del 
  proceso.
