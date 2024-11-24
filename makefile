# Compilador y flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Archivos fuente y objetos
SOURCES = swap.cpp greedy.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = swap

# Regla para compilar el ejecutable
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS)

# Compilación de archivos objeto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpieza de archivos objeto y ejecutable
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
