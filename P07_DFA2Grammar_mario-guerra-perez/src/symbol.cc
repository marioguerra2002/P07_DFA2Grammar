/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 7: Gramática Regular a partir de un DFA
/// Autor: Mario Guerra Pérez
/// Correo: alu0101395036@ull.es
/// Fecha: 15/11/2022
/// Archivo symbol.cc
/// Contiene las declaraciones de los métodos de la clase Symbol
/// Referencias:
/// Enlaces de interés
#include "symbol.h"
/// @brief constructor de la clase Symbol
/// @param recieved cadena de entrada
Symbol::Symbol(std::string recieved) {
  recieved_ = recieved;
}
/// @brief getter del simbolo
/// @return simbolo recibido de la clase
std::string Symbol::GetSymbol() const {
  return recieved_;
}
/// @brief sobrecarga del operador ==
/// @param symbol2 simbolo a comparar
/// @return bool
const bool Symbol::operator==(const Symbol& symbol2) const {
  return recieved_ == symbol2.recieved_;
}
/// @brief sobrecarga del operador <
/// @param symbol2 simbolo a comparar
/// @return bool
const bool Symbol::operator<(const Symbol symbol_2) const { return recieved_ < symbol_2.recieved_; }
void Symbol::operator=(const Symbol& symbol_2) { recieved_ = symbol_2.recieved_; }
Symbol::Symbol() {};