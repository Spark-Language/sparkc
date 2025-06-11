//
// Created by Wylan Shoemaker on 6/10/2025.
//

#ifndef PARSER_H
#define PARSER_H

#pragma once
#include "../tokens/TokenType.h"
#include "../ast/AST.h"
#include <vector>
#include <memory>

#include "../types/Declarations.h"
#include "../types/Expression.h"
#include "../types/Statement.h"
#include "../types/Statements.h"

class Parser {
public:
    explicit Parser(const std::vector<Token> &tokens);

    std::unique_ptr<Token> parseProgram();

private:
    //input
    const std::vector<Token> &tokens;
    size_t current = 0;

    // Helpers
    bool isAtEnd() const;
    const Token &peek() const;
    const Token &previous() const;
    bool check(TokenType type) const;
    bool match(std::initializer_list<TokenType> types);
    const Token &consume(TokenType type, const std::string *errMsg);

    // Top‐level: mix of decls & stmts
    std::unique_ptr<ASTNode> parseUnit();

    // Declarations
    std::unique_ptr<FunctionDeclaration> parseFunctionDecl();

    // Statements
    std::unique_ptr<Statement> parseStatement();
    std::unique_ptr<Statement> parseIfStmt();
    std::unique_ptr<Statement> parseWhileStmt();
    std::unique_ptr<Statement> parseReturnStmt();
    std::unique_ptr<Statement> parseExprStmt();
    std::unique_ptr<BlockStatement> parseBlock();

    // Expressions (precedence‐climbing / Pratt)
    std::unique_ptr<Expression> parseExpression();
    std::unique_ptr<Expression> parseAssignment();
    std::unique_ptr<Expression> parseOr();
    std::unique_ptr<Expression> parseAnd();
    std::unique_ptr<Expression> parseEquality();
    std::unique_ptr<Expression> parseComparison();
    std::unique_ptr<Expression> parseTerm();
    std::unique_ptr<Expression> parseFactor();
    std::unique_ptr<Expression> parseUnary();
    std::unique_ptr<Expression> parseCall();
    std::unique_ptr<Expression> finishCall(std::unique_ptr<Expression> callee);
    std::unique_ptr<Expression> parsePrimary();
};


#endif //PARSER_H
