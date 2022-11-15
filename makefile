CC=g++
CFLAGS=-O0 -g -Wall
DEPS = alphabet.h chain.h symbol.h state.h nfa.h grammar.h
OBJ = main.o

SRC = './src/'

compilar:
	g++ $(CFLAGS) $(SRC)*.cc -o P07_dfa_grammar


%.o: %.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
all: dfa_grammar

language: main.o
	g++ -o dfa_grammar main.cc alphabet.cc chain.cc symbol.cc state.cc nfa.cc grammar.cc

clean:
	rm -f *.o