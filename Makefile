SRC=./src/*.c
LIB=./include/*.h
FLAGS=-Wall -Wextra -Wpedantic
EXE=loc

main: $(SRC)
	gcc -o $(EXE) $(SRC)

dev: $(SRC)
	gcc -o $(EXE) $(SRC) $(FLAGS)

install: $(EXE)
	sudo cp $(EXE) /usr/bin

clean: $(EXE)
	rm $(EXE)

