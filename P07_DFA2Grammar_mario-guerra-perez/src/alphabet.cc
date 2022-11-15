/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 7: Gramática Regular a partir de un DFA
/// Autor: Mario Guerra Pérez
/// Correo: alu0101395036@ull.es
/// Fecha: 15/11/2022
/// Archivo alphabet.cc
/// Contiene la definición de los métodos de la clase alphabet
/// Referencias:
/// Enlaces de interés

#include "alphabet.h"

/// @brief constructor de la clase alphabet
/// @param input vector de strings que contiene el alfabeto
/// @return objeto de la clase alphabet
Alphabet::Alphabet (std::vector<std::string> input) {
  for (unsigned int i{0}; i < input.size() - 1; ++i) {  /// -1 porque el símbolo final es chain
    alphabet_.insert(Symbol(input[i]));
  }
}
/// @brief Getter del atributo alphabet_
/// @param  void
/// @return  atributo alphabet_
std::set<Symbol> Alphabet::GetSet(void) {
  return alphabet_;
}
/// @brief comprueba si un símbolo pertenece al alfabeto
/// @param input símbolo a comprobar 
/// @return boolenao que indica si el símbolo pertenece al alfabeto
bool Alphabet::CheckAlphabet(std::set<Symbol> input) {
  for (auto i : input) {
    if (alphabet_.find(i) == alphabet_.end()) {
      return false;
    }
  }
  return true;
}