//
// Created by Wylan Shoemaker on 6/10/2025.
//

#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H
#include <memory>
#include <utility>
#include <vector>

#include "Expression.h"
#include "../tokens/TokenType.h"

struct LiteralExpression : Expression {
  Literal literal;
  explicit LiteralExpression(Literal literal) : literal((std::move(literal))) {}
};

struct VariableExpression : Expression {
  std::string name;
  explicit VariableExpression(std::string name) : name(std::move(name)) {}
};

struct BinaryExpression : Expression {
  std::unique_ptr<Expression> left, right;
  Token op;
  BinaryExpression(std::unique_ptr<Expression> left, Token o, std::unique_ptr<Expression> right) : left(std::move(left)), right(std::move(right)), op(std::move(o)) {}
};

struct CallExpression : Expression {
  std::unique_ptr<Expression> callee;
  std::vector<std::unique_ptr<Expression>> arguments;
  explicit CallExpression(std::unique_ptr<Expression> c) : callee(std::move(c)) {}
};

#endif //EXPRESSIONS_H
