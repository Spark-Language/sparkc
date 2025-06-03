//
// Created by Wylan Shoemaker on 5/29/25.
//

#include "../../include/tokens/TokenType.h"

// Literal values that tokens may hold
using Literal = std::variant<std::monostate, int64_t, float, double, bool, std::string>;

// Core Token structure
struct Token {
    TokenType type;        // what kind of token this is
    std::string lexeme;    // the original source text
    Literal literal;       // optional parsed literal value
    int line;              // line number in source
    int column;            // column number in source

    Token(TokenType type, std::string lexeme, Literal literal, int line, int column)
            : type(type), lexeme(std::move(lexeme)), literal(std::move(literal)), line(line), column(column) {}
};
