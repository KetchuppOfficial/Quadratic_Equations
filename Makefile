CC = gcc
CFLAGS = -c -Wall -Werror -Wextra

OBJ = Objects/main.o Objects/Quadratic_Equation.o Objects/Unit_Test.o

all: Quadratic_Equation

Quadratic_Equation: main.o Quadratic_Equation.o Unit_Test.o
	$(CC) $(OBJ) -o quadratic.out -lm

main.o: main.c
	$(CC) $(CFLAGS) main.c -o Objects/main.o

Quadratic_Equation.o: Quadratic_Equation.c
	$(CC) $(CFLAGS) Quadratic_Equation.c -o Objects/Quadratic_Equation.o

Unit_Test.o: Unit_Test.c
	$(CC) $(CFLAGS) Unit_Test.c -o Objects/Unit_Test.o

run:
	./quadratic.out

clean:
	rm $(OBJ)
	rm quadratic.out

