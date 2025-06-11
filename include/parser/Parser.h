//
// Created by Wylan Shoemaker on 6/10/2025.
//

#ifndef PARSER_H
#define PARSER_H

#pragma once
#include "../tokens/TokenType.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include <stdexcept>

#include "../types/Declarations.h"
#include "../types/Expression.h"
#include "../types/Statement.h"
#include "../types/Statements.h"

// Forward declarations
class Type;
class GenericType;
struct InterfaceDeclaration;
struct ModuleDeclaration;

class Parser {
public:
    explicit Parser(const std::vector<Token> &tokens);

    std::unique_ptr<Program> parseProgram();

private:
    // Symbol table structures
    struct SymbolTable {
        std::unordered_map<std::string, std::unique_ptr<FunctionDeclaration>> functions;
        std::unordered_map<std::string, std::unique_ptr<TypeDeclaration>> types;
        std::unordered_map<std::string, std::unique_ptr<InterfaceDeclaration>> interfaces;
        std::unordered_map<std::string, std::unique_ptr<ModuleDeclaration>> modules;
    };

    // Input and state
    const std::vector<Token> &tokens;
    size_t current = 0;
    SymbolTable symbols;

    // Error handling
    struct ParseError : std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    // Core parsing methods
    void collectDeclarations();
    std::unique_ptr<Program> parseImplementations();
    void synchronize();

    // Declaration parsing
    std::unique_ptr<FunctionDeclaration> parseFunctionSignature();
    std::unique_ptr<TypeDeclaration> parseTypeDeclaration();
    std::unique_ptr<InterfaceDeclaration> parseInterfaceDeclaration();
    std::unique_ptr<ModuleDeclaration> parseModuleDeclaration();
    
    // Type system
    std::unique_ptr<Type> parseType();
    std::unique_ptr<GenericType> parseGenericType();
    std::vector<std::unique_ptr<Type>> parseTypeParameters();
    
    // Visibility and modifiers
    Visibility parseVisibility();
    std::vector<std::string> parseModifiers();

    // Helper methods
    bool isAtEnd() const;
    const Token &peek() const;
    const Token &previous() const;
    bool check(TokenType type) const;
    bool match(std::initializer_list<TokenType> types);
    const Token &consume(TokenType type, const std::string &errMsg);
    const Token &advance();
    void reset();

    // Existing methods
    std::unique_ptr<Statement> parseStatement();
    std::unique_ptr<Statement> parseIfStmt();
    std::unique_ptr<Statement> parseWhileStmt();
    std::unique_ptr<Statement> parseReturnStmt();
    std::unique_ptr<Statement> parseExprStmt();
    std::unique_ptr<BlockStatement> parseBlock();
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
