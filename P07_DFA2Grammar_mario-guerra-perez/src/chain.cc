/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: Computabilidad y Algoritmia
/// Curso: 2º
/// Práctica 7: Gramática Regular a partir de un DFA
/// Autor: Mario Guerra Pérez
/// Correo: alu0101395036@ull.es
/// Fecha: 15/11/2022
/// Archivo chain.cc
/// Contiene las definiciones de los metodos de la clase chain
/// Referencias:
/// Enlaces de interés

#include "chain.h"

/// @brief constructor de la clase chain
/// @param input cadena de entrada
Chain::Chain(std::string input) { /// constructor de cadena sin alfabeto
  std::string auxiliar;
  for (unsigned int i{0}; i < input.size(); ++i) {
    if (input[i] != kSpace) {
      auxiliar += input[i];
    }
    chain_.push_back(Symbol(auxiliar));
    auxiliar = "";
  }
}
/// @brief sobrecarga del operador << para la clase chain
/// @param os 
/// @param chain cadena a imprimir
/// @return ostream 
std::ostream &operator<<(std::ostream &os, const Chain &chain) {
  for (auto& symbol : chain.chain_) {
    os << symbol.GetSymbol();
  }
  os << std::endl;
  return os;
}
/// @brief sobre carga del operador << para vector de Symbol
/// @param os 
/// @param vector vector de Symbol a imprimir
/// @return ostream
std::ostream &operator<<(std::ostream &os, const std::vector<Symbol> &vector) {
  for (auto& symbol : vector) {
    os << symbol.GetSymbol();
  }
  os << std::endl;
  return os;
}
/// @brief sobre carga del operador >>
/// @param is 
/// @param chain cadena a leer
/// @return istream
std::istream &operator>>(std::istream &is, Chain &chain) {
  std::string input;
  is >> input;
  chain = Chain(input);
  return is;
}
int Chain::Size() {
  return chain_.size();
}
/// @brief Comprueba si la cadena es aceptada por el alfabeto
/// @param alphabet alfabeto a comprobar
/// @return bool
bool Chain::IsChainAccepted(Alphabet alphabet) {
  std::set<Symbol> alphabet_set = alphabet.GetSet();
  bool accepted = true;
  for (auto& symbol : chain_) {
    for (auto& symbol_2 : alphabet_set) {
      if (symbol == symbol_2) {
        accepted = true;
        break;
      } else {
        accepted = false;
      }
    }
  }
  return accepted;
}
/// @brief Realiza la inversa de la cadena
void Chain::Inverse() {
  std::vector<Symbol> inverse;
  std::stringstream output;
  /// recorro vector al revés
  for (long unsigned int i{chain_.size() - 1}; i >= 0 && i != chain_.empty(); --i) {
    /// usamos el empty() para que no se salga del vector (me estaba dando error)
    inverse.push_back(chain_[i]);
  }
  inverse.push_back(chain_[0]);
  output << std::endl;
  std::ofstream outputtext("output_file.txt");

  for (auto& symbol : inverse) {
    output << symbol.GetSymbol();
  }
  outputtext << output.str();
}
/// @brief Calcula los prefijos de la cadena
void Chain::Prefixes() {
  std::vector<Symbol> prefixes;
  std::string auxiliar;
  std::stringstream output;
  output << std::endl;
  prefixes.push_back(Symbol(kEpsilon));
  for (unsigned int i{0}; i < chain_.size(); ++i) {
    /// cojo símbolo a símbolo de la cadena empezando por el primero
    /// luego cojo el siguiente símbolo y lo concateno al anterior
    auxiliar += chain_[i].GetSymbol();
    prefixes.push_back(Symbol(auxiliar));
  }
  std::ofstream outputtext("output_file.txt");
  for (auto& symbol : prefixes) {
    output << symbol.GetSymbol() << " ";
  }
  outputtext.write(output.str().c_str(), output.str().size());
  ///outputtext << output.str();
}
/// @brief Calcula los sufijos de la cadena
void Chain::Sufixes() {
  std::vector<Symbol> suffixes;
  std::string auxiliar;
  std::stringstream output;
  output << std::endl;
  suffixes.push_back(Symbol(kEpsilon));
  /// igual que en Prefixes, pero empezando por el final
  /// y recorriendo el vector al revés
  for (long unsigned int i{chain_.size() - 1}; i >= 0 && i != chain_.empty(); --i) {
    /// usamos el empty() para que no se salga del vector (me estaba dando error)
    auxiliar = chain_[i].GetSymbol() + auxiliar;
    suffixes.push_back(Symbol(auxiliar));
  }
  std::ofstream outputtext("output_file.txt");
  for (auto& symbol : suffixes) {
    output << symbol.GetSymbol() << " ";
  }
  outputtext << output.str();
}
/// @brief Calcula los subcadenas de la cadena
void Chain::SubChain() {
  std::vector<Symbol> subchain;
  std::string auxiliar;
  std::stringstream output;
  output << std::endl;
  subchain.push_back(Symbol(kEpsilon));
  ///subchain.push_back(Symbol(kSpace_b));
  for (unsigned int i{0}; i < chain_.size(); ++i) {
    for (unsigned int j{i}; j < chain_.size(); ++j) {
      ///a partir del primero, cojo símbolo a símbolo siguientes
      auxiliar += chain_[j].GetSymbol();
      subchain.push_back(Symbol(auxiliar));
    }
    auxiliar = "";
  }
  std::ofstream outputtext("output_file.txt");
  for (auto& symbol : subchain) {
    output << symbol.GetSymbol() << " ";
  }
  outputtext << output.str();
}
