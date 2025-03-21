#ifndef CLOX_AST_PRINTER_HPP
#define CLOX_AST_PRINTER_HPP

#include <vector>
#include <ExprStruct.hpp>

class AstPrinter {
  std::string parenthesize(const std::string&, const std::vector<Expr*>&);
public:
  AstPrinter() {};
  std::string print(const Expr&);
};

#endif