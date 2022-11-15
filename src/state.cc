/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 7: Gramática Regular a partir de un DFA
/// Autor: Mario Guerra Pérez
/// Correo: alu0101395036@ull.es
/// Fecha: 15/11/2022
/// Archivo state.cc
/// Contiene las definiciones de los métodos de la clase state
/// Referencias:
/// Enlaces de interés
#include "state.h"
/// @brief constructor de la clase state
/// @param input cadena de entrada
State::State(std::string input) {
  std::string auxiliar;
  while (input[0] != kSpace) {
    auxiliar += input[0];
    input.erase(0, 1);
  }
  state_ = auxiliar;
  auxiliar = "";
  input.erase(0, 1); /// borro el espacio (no estoy seguro de que sea necesario)
  auxiliar = input[0]; /// leemos el primer caracter para saber si es final
  if (std::stoi(auxiliar) == 1) {
    final = true;
  } else {
    final = false;
  }
  input.erase(0, 2); /// borramos el 0 o 1 y el espacio
  auxiliar = input[0]; /// leemos el primer caracter para saber el numero de transiciones
  int number_transitions = std::stoi(auxiliar);
  auxiliar = "";
  input.erase(0, 2); /// borramos el numero de transiciones y el espacio
  Symbol symbol1;
  Symbol symbol2;
  std::vector<std::string> states;
  if (number_transitions == 1) {
    while (input[0] != kSpace) {
      auxiliar += input[0];
      input.erase(0, 1);
    }
    symbol1 = Symbol(auxiliar);
    auxiliar = "";
    input.erase(0, 1); /// borramos el espacio
    while (input[0] != kSpace) {
      auxiliar += input[0];
      input.erase(0, 1);
    }
    states.push_back(auxiliar);
    auxiliar = "";
    input.erase(0, 1); /// borramos el espacio
    transitions_[symbol1] = states; /// añadimos la transición al mapa
  } else if (number_transitions > 1) {
    while (input[0] != kSpace) {
      auxiliar += input[0];
      input.erase(0, 1);
    }
    symbol1 = Symbol(auxiliar);
    auxiliar = "";
    input.erase(0, 1); /// borramos el espacio
    while (input[0] != kSpace) {
      auxiliar += input[0];
      input.erase(0, 1);
    }
    input.erase(0, 1); /// borramos el espacio
    states.push_back(auxiliar);  /// da error
    auxiliar = "";
    transitions_[symbol1] = states; /// añadimos la transición al mapa

    for (int i{0}; i < number_transitions - 1; ++i) {
      while (input[0] != kSpace) {
        auxiliar += input[0];
        input.erase(0, 1);
      }
      symbol2 = Symbol(auxiliar);
      auxiliar = "";
      input.erase(0, 1); /// borramos el espacio
      if (symbol1 == symbol2) { /// si el símbolo es el mismo que el anterior, añadimos el estado al vector
        while (input[0] != kSpace) {
          auxiliar += input[0];
          input.erase(0, 1);
        }
        states.push_back(auxiliar); /// añadimos el estado al vector de estados
        auxiliar = "";
        input.erase(0, 1); /// borramos el espacio
        transitions_[symbol1] = states; /// añadimos la transición al mapa
      } else {
        states.clear(); /// vaciamos el vector de estados
        while (input[0] != kSpace) {
          auxiliar += input[0];
          input.erase(0, 1);
        }
        states.push_back(auxiliar); /// añadimos el estado al vector de estados
        auxiliar = "";
        input.erase(0, 1); /// borramos el espacio
        transitions_[symbol2] = states; /// añadimos la transición al mapa
      }
      symbol1 = symbol2; /// actualizamos el símbolo para la siguiente iteración
    }
  }
}
/// @brief getter del estado
/// @return state_
const std::string State::GetState() const {
  return state_;
}
/// @brief comprueba si el estado es final
/// @return bool
const bool State::IsFinal() const {
  return final;
}
/// @brief comprueba si el estado es inicial
/// @return bool 
const bool State::IsInitial() const {
  return initial;
}
/// @brief comprueba si se puede ir de un estado a otro con un símbolo de entrada
/// @param symbol simbolo de entrada con el que se quiere ir de un estado a otro
/// @return bool
const bool State::IsTransition(Symbol symbol) const {
  if (transitions_.find(symbol) != transitions_.end()) {
    return true;
  } else {
    return false;
  }
}
/// @brief getter del mapa de transiciones
/// @return transitions_
const std::map<Symbol, std::vector<std::string>> State::GetTransitions() const {
  return transitions_;
}
/// @brief setter del estado inicial
void State::SetInitial() {
  initial = true;
}
/// @brief setter del nombre del estado
/// @param state nuevo nombre del estado
void State::SetStateName(std::string state) {
  state_ = state;
}
/// @brief realiza una transición de un estado a otro con un símbolo de entrad
/// @param symbol símbolo de entrada con el que se quiere ir de un estado a otro
/// @param states estados a los que se puede ir con el símbolo de entrada
/// @return std::vector<std::string> estados a los que se puede ir con el símbolo de entrada
std::vector<State> State::GetNextStates(Symbol symbol, std::vector<State> states) const {
  std::vector<State> next_states;
  std::vector<std::string> next_states_names;
  if (!transitions_.count(symbol)) { /// si no hay transiciones con el símbolo
    return next_states;
  } else {
    next_states_names = transitions_.at(symbol);
    /// next_states_names.insert(next_states_names.end(), transitions_.at(Symbol(kEpsilon)).begin(), transitions_.at(Symbol(kEpsilon)).end());  /// añadimos los estados con transición con epsilon
    if (next_states_names.size() != 0) {
      for (long unsigned int i{0}; i < next_states_names.size(); ++i) {
        for (auto& j : states) {
          if (next_states_names[i] == j.GetState()) {
            next_states.push_back(j);
          }
        }
      }
    }
    return next_states;
  }
}
const bool State::operator<(const State& state2) const {
  return state_ < state2.GetState();
}