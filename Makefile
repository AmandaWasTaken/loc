SRC=./src/*.c
LIB=./include/*.h
FLAGS=-Wall -Wextra -Wpedantic
EXE=loc
BIN_DIR=./bin

main: $(SRC)
	gcc -o $(BIN_DIR)/$(EXE) $(SRC)

dev: $(SRC)
	gcc -o $(BIN_DIR)/$(EXE) $(SRC) $(FLAGS)

install: $(EXE)
	sudo cp $(BIN_DIR)/$(EXE) /usr/bin

clean: $(BIN_DIR)/$(EXE)
	rm $(BIN_DIR)/$(EXE)

