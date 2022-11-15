/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 7: Gramática Regular a partir de un DFA
/// Autor: Mario Guerra Pérez
/// Correo: alu0101395036@ull.es
/// Fecha: 15/11/2022
/// Archivo nfa.cc
/// Contiene las definiciones de los métodos de la clase NFA
/// Referencias:
/// Enlaces de interés
#include "nfa.h"
/// @brief constructor de la clase NFA
/// @param input cadena de entrada 
NFA::NFA (std::vector<std::string> input) {
  //// en cada componente del vector hay una linea del fichero
  //// la primera linea es el alfabeto
  //// la siguiente es el numero de estados
  //// la sifuiente es el estado inicial
  //// las siguientes son los estados
  std::string auxiliar;
  std::vector<std::string> auxiliar_vect;
  for (unsigned int j{0}; j < input[0].size(); ++j) {
    if (input[0][j] != kSpace) {
      auxiliar += input[0][j];
    } else {
      auxiliar_vect.push_back(auxiliar);
      auxiliar = "";
    }
  }
  auxiliar_vect.push_back(auxiliar); /// para el ultimo elemento de la linea
  auxiliar = "";
  alphabet_ = Alphabet(auxiliar_vect); /// creamos el alfabeto
  size_alphabet_ = alphabet_.GetSet().size() + 1;
  number_states_ = std::stoi(input[1]); /// numero de estados
  initial_state_ = input[2]; /// estado inicial
  for (unsigned long int i{0} ; i < number_states_; ++i) {
    states_.push_back(State(input[i+3]));
  }
  SetInitial();
}
/// @brief getter de states_
/// @param  
/// @return states_
const std::vector<State> NFA::GetStates(void) const {
  return states_;
}
void NFA::SetInitial(void) {  /// define el estado como inicial (se realiza a la hora de crear el nfa)
  for (unsigned long int i{0}; i < number_states_; ++i) {
    if (states_[i].GetState() == initial_state_) {
      states_[i].SetInitial();
    }
  }
}
/// @brief getter de alphabet_
/// @param  
/// @return alphabet_
Alphabet NFA::GetAlphabet(void) const {
  return alphabet_;
}
/// @brief comprueba si el DFA es valido
/// @return bool
bool NFA::CheckDFA() const{
  /// comprueba que el nfa es correcto
  /// comprueba que el numero de estados es igual al numero de estados del fichero
  /// comprueba que el estado inicial es correcto
  /// comprueba que los estados son correctos
  /// comprueba que el alfabeto es correcto
  if (number_states_ != states_.size()) {
    return false;
  }
  for (unsigned long int i{0}; i < number_states_; ++i) {
    if (states_[i].GetState() == initial_state_) {  /// comprueba que el estado inicial es correcto
      if (states_[i].IsInitial() == false) {
        return false;
      }
    }
  }
  for (auto& i : states_) {  /// compruebo por cada estado
    unsigned long int counter{0};
    std::set<Symbol> auxiliar_set;
    for (auto& j : i.GetTransitions()) {
      if (j.first == kEpsilon) { /// comprueba que no hay transiciones con epsilon
        return false;
      } else {
        if (auxiliar_set.find(j.first) == auxiliar_set.end()) {
          auxiliar_set.insert(j.first); /// comprueba que no hay transiciones con el mismo simbolo
        } else {
          return false;
        }
      }
    }
    for (unsigned long int j{0}; j < i.GetTransitions().size(); ++j) {  
      counter++;  /// numero de transiciones de un estado
    }
    if (counter != size_alphabet_) {  /// comprueba que el numero de transiciones es igual al numero de simbolos del alfabeto
      return false;
    }
  }
  return true;
}
/// @brief Comprueba si la cadena es valida
/// @param chain cadena de entrada
/// @return bool
const bool NFA::IsAccepted(Chain chain) const {
  std::set<State> current_states;
  std::set<State> next_states;
  /// iteracion 0 (estado inicial)
  for (unsigned long int i{0}; i < number_states_; ++i) {
    if (states_[i].IsInitial()) {
      current_states.insert(states_[i]);
    }
  }
  for (int i{0}; i < chain.Size(); ++i) {
    for (auto& state : current_states) { /// para cada estado en el conjunto de estados actuales
      std::vector<State> auxiliar = state.GetNextStates(chain.GetChain()[i], states_);
      /// devuelve un vector con los estados a los que se puede llegar con el simbolo
      for (auto& state : auxiliar) {
        next_states.insert(state); /// inserta los estados en el conjunto de estados
      }
    }
    /// una vez tenemos los estados a los que se puede llegar con el simbolo, los pasamos a los estados actuales
    current_states = next_states;
    next_states.clear();
  }
  for (auto& state : current_states) {
    if (state.IsFinal()) {
      return true;
    }
  }
  return false;
}