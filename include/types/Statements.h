//
// Created by Wylan Shoemaker on 6/10/2025.
//

#ifndef STATEMENTS_H
#define STATEMENTS_H
#include <memory>
#include <vector>

#include "Expression.h"
#include "Statement.h"

struct ExpressionStatement : Statement {
    std::unique_ptr<Expression> expression;
    explicit ExpressionStatement(std::unique_ptr<Expression> expression) : expression(std::move(expression)) {}
};

struct ReturnStatement : Statement {
    std::unique_ptr<Expression> expression;
    explicit ReturnStatement(std::unique_ptr<Expression> expression) : expression(std::move(expression)) {}
};

struct BlockStatement : Statement {
    std::vector<std::unique_ptr<Statement>> statements;
};

#endif //STATEMENTS_H
