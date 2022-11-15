/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 7: Gramática Regular a partir de un DFA
/// Autor: Mario Guerra Pérez
/// Correo: alu0101395036@ull.es
/// Fecha: 15/11/2022
/// Archivo grammar.cc
/// Contiene las definiciones de los metodos de la clase grammar
/// Referencias:
/// Enlaces de interés
#include "grammar.h"
Symbol kInitialState_ = Symbol("S");
std::string kInitialString_ = "S";
/// @brief constructor de la clase grammar
/// @param dfa_ automata finito determinista
Grammar::Grammar(NFA dfa_) {
  /// para cada simbolo del alfabeto = terminales
  for (auto& i : dfa_.GetAlphabet().GetSet()) {
    terminals_.insert(i);
  }
  /// para cada estado del automata = no terminales
  /// los estados del automata se cambian a no terminales con nombre alfabetico
  if (dfa_.GetStates().size() > 1) {
    std::string initial_name {"S"};
    nonterminals_.insert(Symbol(initial_name));
    /// -1 porque el primer estado es S
    for (long unsigned int i{0}; i < dfa_.GetStates().size() - 1; ++i) {
      std::string auxiliar;
      auxiliar = ('A' + i);
      if (auxiliar != initial_name) {
        nonterminals_.insert(Symbol(auxiliar));
      }
    }
  } else if (dfa_.GetStates().size() == 1) {
    std::string initial_name {"S"};
    nonterminals_.insert(Symbol(initial_name));
  }
  /// Relaciona los nombres antiguos de estados con nuevos alfabeticos
  new_names_states_ = SetNewStatesNames(dfa_);
  /// Obtiene los estados aceptados
  accepted_states_ = GetAcceptedStates(dfa_);
  for (auto& i : dfa_.GetStates()) {
    std::vector<std::pair<Symbol, Symbol>> auxiliar_vect;
    /// para cada transicion del estado
    for (auto& j : i.GetTransitions()) { 
      std::pair<Symbol, Symbol> auxiliar_pair;
      /// nombre del estado nuevo (alfabetico) al que se llega
      Symbol auxiliar_symbol = new_names_states_[j.second.at(0)];
      /// simbolo de la transicion
      auxiliar_pair.first = j.first;
      /// nombre del estado nuevo (alfabetico) al que se llega
      auxiliar_pair.second = auxiliar_symbol;
      auxiliar_vect.push_back(auxiliar_pair);
    }
    productions_.insert(std::pair<Symbol, std::vector<std::pair<Symbol, Symbol>>>(new_names_states_[i.GetState()], auxiliar_vect));
  }
}
/// @brief Atribuye nombres alfabeticos a los estados del automata
/// @param dfa_ 
/// @return mapa de estados antiguos con sus nombres nuevos
std::map<Symbol, Symbol> Grammar::SetNewStatesNames(NFA dfa_) {
  int counter{0};
  std::map<Symbol, Symbol> new_names;
  for (auto& i : dfa_.GetStates()) {
    if (!i.IsInitial()) {
      std::string auxiliar;
      auxiliar = ('A' + counter);
      new_names.insert(std::pair<Symbol, Symbol>(i.GetState(), Symbol(auxiliar)));
      ++counter;
    } else {
      new_names.insert(std::pair<Symbol, Symbol>(i.GetState(), kInitialState_));
    }
  }
  return new_names;
}
/// @brief Obtiene los estados aceptados del automata
/// @param dfa_ automata finito determinista
/// @return conjunto de estados aceptados
std::set<Symbol> Grammar::GetAcceptedStates(NFA dfa_) {
  std::set<Symbol> accepted_states_;
  for (auto& i : dfa_.GetStates()) {
    if (i.IsFinal() && i.IsInitial()) {
      accepted_states_.insert(kInitialState_);
    } else if (i.IsFinal() && !i.IsInitial()) {
      accepted_states_.insert(new_names_states_[i.GetState()]);
    }
  }
  return accepted_states_;  
}
/// @brief obtiene numero de producciones
/// @return entero con el numero de producciones
int Grammar::GetNumberProductions() {
  for (auto& i : productions_) {
    for (unsigned long int j{0}; j < i.second.size(); ++j) {
      ++number_productions_;
    }
  }
  for (unsigned long int i{0}; i < accepted_states_.size(); ++i) {
    ++number_productions_;
  }
  return number_productions_;
}
/// @brief crea el fichero de la gramatica con el formato adecuado usando flujo de strings
/// @return stringstream con el contenido del fichero
std::stringstream Grammar::OutputGrammar() {
  std::stringstream output;
  output << terminals_.size() << std::endl;
  for (auto& i : terminals_) {
    output << i.GetSymbol() << std::endl;
  }
  output << nonterminals_.size() << std::endl;
  output << kInitialState_.GetSymbol() << std::endl;
  for (auto& i : nonterminals_) {
    if (i.GetSymbol() != kInitialState_.GetSymbol()) {
      output << i.GetSymbol() << std::endl;
    }
  }
  output << kInitialState_.GetSymbol() << std::endl;
  output << GetNumberProductions() << std::endl;

  for (auto& i : productions_[kInitialState_]) {
    output << kInitialState_.GetSymbol() << " -> ";
    output << i.first.GetSymbol() << i.second.GetSymbol() << std::endl;
    /// si el estado inicial es aceptado
    if (accepted_states_.find(kInitialState_) != accepted_states_.end()) { 
      output << kInitialState_.GetSymbol() << " -> " << kEpsilon << std::endl;
    }
  }
  for (auto& i : productions_) {
    if (i.first.GetSymbol() != kInitialString_) {
      for (auto& j : i.second) {
        output << i.first.GetSymbol() << " -> ";
        output << j.first.GetSymbol() << j.second.GetSymbol() << std::endl;
      }
      /// si el estado es aceptado
      if (accepted_states_.find(i.first) != accepted_states_.end()) {
        output << i.first.GetSymbol() << " -> " << kEpsilon << std::endl;
      }
    }
  }
  return output;
}