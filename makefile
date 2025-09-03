# Compilateur
CXX = g++
# Flags de compilation
CXXFLAGS = -Wall -Wextra -std=c++17 -Iincludes -MMD -MP
# Librairies Raylib et dépendances
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Fichiers sources et objets
SRC = $(wildcard src/*.cpp) main.cpp
OBJ = $(SRC:.cpp=.o)
DEP = $(OBJ:.o=.d)


# Nom de l'exécutable
TARGET = raycaster

# Cible par défaut
all: $(TARGET)

# Règle de l'exécutable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LIBS)

# Compilation des .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEP)

# Nettoyage
clean:
	rm -f $(OBJ) $(TARGET)

# Optionnel : rebuild complet
re: clean all

.PHONY: all clean re
