/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 7: Gramática Regular a partir de un DFA
/// Autor: Mario Guerra Pérez
/// Correo: alu0101395036@ull.es
/// Fecha: 15/11/2022
/// Archivo chain.h
/// Contiene la declaracion de la clase chain
/// Referencias:
/// Enlaces de interés
#ifndef CHAIN_H_
#define CHAIN_H_
#include "symbol.h"
#include "alphabet.h"
#include <string>
#include <sstream>
#include <fstream>
const char kSpace{' '};
const std::string kEpsilon{'&'};
class Chain {
  public:
    Chain(std::string);
    Chain() {};
    /// Chain GetChain();
    std::vector<Symbol> GetChain() const { return chain_; }
    friend std::ostream& operator<<(std::ostream& os, const Chain& chain);
    friend std::ostream& operator<<(std::istream& os, const std::vector<Symbol>& vector);
    friend std::istream& operator>>(std::istream& is, Chain& chain);
    int Size();
    void Inverse();
    void Prefixes();
    void Sufixes();
    void SubChain();
    void CountSymbol();
    bool IsChainAccepted(Alphabet);
  private:
    std::vector<Symbol> chain_;
    /// Alphabet alphabet_;
};
#endif /// CHAIN_H_