CC=g++

all: test

main: main.o calc.o
	$(CC) -o main main.o calc.o

main.o: main.cpp
	$(CC) -c main.cpp

calc.o: calc/calc.cpp
	$(CC) -c calc/calc.cpp

test: main test_calc.py
	@python3 test_calc.py

clean:
	@rm *.o main