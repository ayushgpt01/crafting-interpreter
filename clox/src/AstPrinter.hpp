#ifndef CLOX_AST_PRINTER_HPP
#define CLOX_AST_PRINTER_HPP

#include <array>
#include <ExprStruct.hpp>

class AstPrinter {
  std::string parenthesize(const std::string&, const std::array<Expr*, 2>&);

public:
  AstPrinter() {};
  std::string print(const Expr&);
};

#endif