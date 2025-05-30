//
// Created by Wylan Shoemaker on 5/29/25.
//

#include "../../include/tokens/TokenDef.h"
#include <string>
#include <variant>

enum class TokenType {
    // Keywords
    FUNC, IF, ELSE, RET,

    // Numbers
    INT_LITERAL,
    FLOAT_LITERAL,
    DOUBLE_LITERAL,

    PLUS, MINUS, MULTIPLY, DIVIDE,

    IDENTIFIER, NUMBER, STRING,

    // Characters
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACKET, RIGHT_BRACKET,
    LEFT_BRACE, RIGHT_BRACE,

    END_OF_FILE
};

using Literal = std::variant<std::monostate, int64_t, float, double, bool, std::string>;

struct Token {
    TokenType type;
    std::string lexeme;
    Literal literal;
    int line;
    int column;

    Token(TokenType type, std::string lexeme, Literal literal, int line, int column)
        : type(type),lexeme(std::move(lexeme)), literal(std::move(literal)), line(line), column(column) {}
};
