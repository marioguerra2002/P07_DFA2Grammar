/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 7: Gramática Regular a partir de un DFA
/// Autor: Mario Guerra Pérez
/// Correo: alu0101395036@ull.es
/// Fecha: 15/11/2022
/// Archivo state.h
/// Contiene la definición de la clase State
/// Referencias:
/// Enlaces de interés

#ifndef STATE_H_
#define STATE_H_

#include "alphabet.h"
#include "chain.h"
#include "symbol.h"
#include <iostream>
#include <utility>
#include <map>

class State {
  public:
    State (std::string);
    State ();
    const std::string GetState(void) const;
    const bool IsFinal(void) const;
    const bool IsInitial(void) const;
    const bool IsTransition(Symbol) const;
    const std::map<Symbol, std::vector<std::string>> GetTransitions() const;
    std::vector<State> GetNextStates(Symbol, std::vector<State>) const;
    void SetInitial(void);
    const bool operator<(const State& state) const;

    void SetStateName(std::string);
    /// Symbol GetSymbol (void) const; /// devuelve el símbolo del estado
    /// std::map<Symbol, std::vector<State>> GetMap (void) const; /// devuelve el mapa de transiciones del estado
  private:
    bool initial = false;
    bool final;
    std::string state_; /// nombre del estado
    std::map<Symbol, std::vector<std::string>> transitions_; /// transiciones del estado
};
#endif /// STATE_H_