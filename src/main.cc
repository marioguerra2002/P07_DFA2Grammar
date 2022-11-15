/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 7: Gramática Regular a partir de un DFA
/// Autor: Mario Guerra Pérez
/// Correo: alu0101395036@ull.es
/// Fecha: 15/11/2022
/// Archivo main.cc
/// Contiene el main del programa 
/// Referencias:
/// Enlaces de interés
#include "nfa.h"
#include "grammar.h"
#include <string.h>
#include <fstream>
#include <iostream>
/// @brief contiene el main del programa
/// @param argc es el número de argumentos
/// @param argv es el array de argumentos
/// @return 
int main(int argc, char* argv[]) {
  if (strcmp(argv[1], "--help") == 0) {
    std::cout << "Este programa lee un fichero de texto con un automata determinista" << std::endl;
    std::cout << "y lo transforma en una gramatica regular" << std::endl;
    std::cout << "El programa se ejecuta de la siguiente manera:" << std::endl;
    std::cout << "./practica7 fichero_entrada fichero_salida" << std::endl;
    return 0;
  } else if (argc != 3) {
    std::cout << "Modo de empleo: ./P07_dfa_grammar dfa.fa input.txt" << std::endl;
    std::cout << "Pruebe ./P07_dfa_grammar --help para más información." << std::endl;
    return 1;
  }
  std::ifstream dfafile(argv[1]);
  std::ofstream grammarout(argv[2]);
  std::string line;
  std::vector<std::string> vect_auxiliar;
  while (std::getline(dfafile, line)) {
    vect_auxiliar.push_back(line);  /// meto cada línea del fichero en un vector
  }
  NFA dfa(vect_auxiliar);
  // Grammar grammar(dfa);
  // grammarout << grammar.OutputGrammar().str();
  if (dfa.CheckDFA() == false) {
    std::cout << "El automata no es un DFA" << std::endl;
    return 1;
  } else {
    Grammar grammar(dfa);
    grammarout << grammar.OutputGrammar().str();
  }
}