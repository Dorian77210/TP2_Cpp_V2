CFLAGS = -ansi -pedantic -Wall -Werror -std=c++11
CFLAGS_LINK = -pedantic -Wall -Werror -std=c++11

CC = g++

SRC := src
OBJ := obj
DEBUG := debug
RELEASE := release

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/$(RELEASE)/%.o, $(SOURCES))
OBJECTS_DBG := $(patsubst $(SRC)/%.cpp, $(OBJ)/$(DEBUG)/%.o, $(SOURCES))

# executable sans option de debug
release: $(OBJECTS)
	$(CC) -o main $^ $(CFLAGS_LINK)

# executable avec options de debug + definition de la constante MAP
debug: $(OBJECTS_DBG)
	$(CC) -o main_debug $^ $(CFLAGS_LINK) -g -D MAP

$(OBJ)/$(RELEASE)/%.o: $(SRC)/%.cpp
	mkdir -p $(OBJ)/$(RELEASE)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ)/$(DEBUG)/%.o: $(SRC)/%.cpp
	mkdir -p $(OBJ)/$(DEBUG)
	$(CC) -c $< -o $@ $(CFLAGS) -g -D MAP

clean:
	rm obj/*/*.o debug release -f
