/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 7: Gramática Regular a partir de un DFA
/// Autor: Mario Guerra Pérez
/// Correo: alu0101395036@ull.es
/// Fecha: 15/11/2022
/// Archivo grammar.h
/// Contiene la declaracion de la clase grammar
/// Referencias:
/// Enlaces de interés
#ifndef GRAMMAR_H_
#define GRAMMAR_H_
#include "nfa.h"
#include "state.h"
#include <sstream>
#include <fstream>
class Grammar {
  public:
    Grammar (NFA);
    std::map<Symbol, Symbol> SetNewStatesNames (NFA);
    std::set<Symbol> GetAcceptedStates (NFA);
    std::stringstream OutputGrammar (void);
    int GetNumberProductions (void);
  private:
    std::set<Symbol> terminals_;
    std::set<Symbol> nonterminals_;
    /// Mapa que relaciona los nombres antiguos de estados con nuevos alfabeticos
    std::map<Symbol, Symbol> new_names_states_; 
    std::map<Symbol, std::vector<std::pair<Symbol, Symbol>>> productions_;
    std::set<Symbol> accepted_states_;
    int number_productions_{0};
};
#endif /// GRAMMAR_H_