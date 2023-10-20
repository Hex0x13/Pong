
CPP = gcc
FLAGS = -Wall -std=c++17

SRC = main.cpp
EXE = pong

INC_DIR = -Isrc/include
LIB_DIR = -Lsrc/lib

LIBS = -lmingw32 -lSDL2main -lSDL2 -g
GDB = gdb

all: $(EXE)

$(EXE): $(SRC)
	$(CPP) $(FLAGS) $(INC_DIR) $(LIB_DIR) $(SRC) -o $(EXE) $(LIBS)


run:
	./$(EXE)

debug:
	$(GDB) ./$(EXE)

clean:
	rm -F $(EXE)