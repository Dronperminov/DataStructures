compiler=g++
flags=-Wall -pedantic

all: tests menu perfomance

tests:
	$(compiler) $(flags) tests.cpp -o tests

menu:
	$(compiler) $(flags) menu.cpp -o menu

perfomance:
	$(compiler) $(flags) perfomance.cpp -o perfomance

clean:
	rm -rf tests menu perfomance