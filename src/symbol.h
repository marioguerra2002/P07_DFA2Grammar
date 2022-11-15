/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 7: Gramática Regular a partir de un DFA
/// Autor: Mario Guerra Pérez
/// Correo: alu0101395036@ull.es
/// Fecha: 15/11/2022
/// Archivo symbol.H
/// Contiene la definición de la clase symbol
/// Referencias:
/// Enlaces de interés
#ifndef SYMBOL_H_
#define SYMBOL_H_
#include <iostream>
#include <string>
class Symbol {
  public:
    Symbol(std::string);
    Symbol();
    std::string GetSymbol (void) const;  /// getter de la clase
    const bool operator==(const Symbol&) const;
    const bool operator<(const Symbol) const;  /// operador de compación para setter
    void operator=(const Symbol&);  /// operador de asignación
  private:
    std::string recieved_;
};
#endif /// SYMBOL_H_