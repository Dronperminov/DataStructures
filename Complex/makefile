COMPILER=g++
FLAGS=-Wall -pedantic

all: main tests

main:
	$(COMPILER) $(FLAGS) main.cpp -o main

tests:
	$(COMPILER) $(FLAGS) tests.cpp -o tests

clean:
	rm -rf main tests