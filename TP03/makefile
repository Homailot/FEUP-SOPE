CC = clang

prog = 
SRC := src
OBJ := .

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%, $(SOURCES))

flags = -g -Wall
libs = -lpthread

all: $(OBJECTS)

$(OBJ)/%: $(SRC)/%.c
	$(CC) -MJ $(SRC)/$@.json -I$(SRC) $(flags) $< -o $@ $(libs)

clean:
	rm -f $(OBJECTS)