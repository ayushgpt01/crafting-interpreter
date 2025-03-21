#include <AstPrinter.hpp>

std::string AstPrinter::parenthesize(const std::string& name, const std::vector<Expr*>& expressions) {
  std::string result = "(" + name;
  for (const Expr* expr : expressions) {
    result += " " + print(*expr);
  }

  result += ")";
  return result;
}

std::string AstPrinter::print(const Expr& expr) {
  return std::visit([this](const auto& ptr) -> std::string {
    using T = std::decay_t<decltype(ptr)>;
    if constexpr (std::is_same_v<T, BinaryPtr>) {
      return this->parenthesize(ptr->op.lexeme, { &ptr->left, &ptr->right });
    }
    else if constexpr (std::is_same_v<T, UnaryPtr>) {
      return this->parenthesize(ptr->op.lexeme, { &ptr->right });
    }
    else if constexpr (std::is_same_v<T, GroupingPtr>) {
      return this->parenthesize("group", { &ptr->expression });
    }
    else if constexpr (std::is_same_v<T, LiteralPtr>) {
      if (std::holds_alternative<std::monostate>(ptr->value)) {
        return "nil";
      }
      else if (std::holds_alternative<std::string>(ptr->value)) {
        return "\"" + std::get<std::string>(ptr->value) + "\"";
      }
      else if (std::holds_alternative<bool>(ptr->value)) {
        return std::get<bool>(ptr->value) ? "true" : "false";
      }
      else {
        return std::to_string(std::get<double>(ptr->value));
      }
    }

    return "";
    }, expr);
}