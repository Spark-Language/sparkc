//
// Created by Wylan Shoemaker on 5/29/25.
//

#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#include <string>
#include <variant>
#include <cstdint>

#include "../visibility/Visibility.h"

// This enum defines all possible token types the lexer can emit
enum class TokenType {
    // ===== IDENTIFIERS & LITERALS =====
    IDENTIFIER, // variable, function, or type names

    INT8_LITERAL,
    INT16_LITERAL,
    INT32_LITERAL,
    INT64_LITERAL,// e.g. 42

    UINT8_LITERAL,
    UINT16_LITERAL,
    UINT32_LITERAL,
    UINT64_LITERAL,

    FLOAT8_LITERAL,
    FLOAT16_LITERAL,
    FLOAT32_LITERAL,
    FLOAT64_LITERAL, // e.g. 3.14f

    DOUBLE_LITERAL, // e.g. 3.1415926535
    STRING_LITERAL, // e.g. "hello"
    CHAR_LITERAL, // e.g. 'a'
    BOOLEAN_LITERAL, // true or false
    NULL_LITERAL, // null, none, or nil

    // ===== STRUCTURAL & PUNCTUATION =====
    LEFT_PAREN, // (
    RIGHT_PAREN, // )
    LEFT_BRACE, // {
    RIGHT_BRACE, // }
    LEFT_BRACKET, // [
    RIGHT_BRACKET, // ]
    COMMA, // ,
    DOT, // .
    COLON, // :
    DOUBLE_COLON, // ::
    SEMICOLON, // ;
    ARROW, // ->
    FAT_ARROW, // =>
    ELLIPSIS, // ...
    RANGE, // ..
    RANGE_INCLUSIVE, // ..=
    QUOTE, // ""
    APOSTROPHE, // ''

    // ===== ARITHMETIC OPERATORS =====
    PLUS, // +
    MINUS, // -
    STAR, // *
    SLASH, // /
    MODULO, // %

    // ===== BITWISE OPERATORS =====
    BIT_AND, // &
    BIT_OR, // |
    BIT_XOR, // ^
    SHIFT_LEFT, // <<
    SHIFT_RIGHT, // >>

    // ===== ASSIGNMENT OPERATORS =====
    EQUAL, // =
    PLUS_EQUAL, // +=
    MINUS_EQUAL, // -=
    STAR_EQUAL, // *=
    SLASH_EQUAL, // /=
    MODULO_EQUAL, // %=
    AND_EQUAL, // &=
    OR_EQUAL, // |=
    XOR_EQUAL, // ^=
    SHL_EQUAL, // <<=
    SHR_EQUAL, // >>=

    // ===== COMPARISON OPERATORS =====
    EQUAL_EQUAL, // ==
    NOT_EQUAL, // !=
    LESS, // <
    LESS_EQUAL, // <=
    GREATER, // >
    GREATER_EQUAL, // >=

    // ===== LOGICAL OPERATORS =====
    AND, // &&
    OR, // ||
    NOT, // !

    // ===== MISC SYMBOLS =====
    QUESTION, // ?
    TILDE, // ~
    BACKSLASH,
    AT, // @
    HASH, // #
    DOLLAR, // $

    // ===== CONTROL FLOW KEYWORDS =====
    IF,
    ELSE,
    SWITCH,
    MATCH,
    CASE,
    DEFAULT,
    FOR,
    WHILE,
    DO,
    BREAK,
    CONTINUE,
    RETURN,
    YIELD,
    GOTO,

    // ===== DECLARATION KEYWORDS =====
    FUNC,
    VAR,
    LET,
    CONST,
    TYPE,
    STRUCT,
    CLASS,
    INTER,
    IMPL,
    ENUM,
    UNION,
    MODULE,
    IMPORT,
    USE,
    ATOMIC,

    // ===== ACCESS CONTROL & MODIFIERS =====
    PUBLIC,
    PRIVATE,
    INTERNAL,
    STATIC,
    ABSTRACT,
    FINAL,
    OVERRIDE,
    VIRTUAL,
    INLINE,

    // ===== CONCURRENCY & ASYNC =====
    ASYNC,
    AWAIT,
    SPAWN,
    THREAD,

    // ===== TYPE SYSTEM & MEMORY =====
    AS,
    IS,
    TYPEOF,
    SIZEOF,
    NEW,
    THIS,
    SUPER,

    // ===== LITERAL KEYWORDS =====
    TRUE_VALUE,
    FALSE_VALUE,
    NULL_VALUE,

    INT8,
    INT16,
    INT32,
    INT64,

    UINT8,
    UINT16,
    UINT32,
    UINT64,

    FLOAT8,
    FLOAT16,
    FLOAT32,
    FLOAT64,

    DOUBLE,
    STRING,
    BOOLEAN,
    CHAR,
    OK, // for Result types
    FAIL, // for Result types

    // ===== SPECIAL =====
    BUNDLE,
    END_OF_FILE, // signals end of input
    UNKNOWN // catch-all for error recovery
};

// Literal values that tokens may hold
using Literal = std::variant<std::monostate, int64_t, float, double, bool, char, std::string>;

// Core Token structure
struct Token {
    TokenType type; // what kind of token this is
    std::string lexeme; // the original source text
    Literal literal; // optional parsed literal value
    int line; // line number in source
    int column; // column number in source

    Visibility visibility = Visibility::Private;

    Token(TokenType type, std::string lexeme, Literal literal, int line, int column, Visibility visibility = Visibility::Private)
        : type(type), lexeme(std::move(lexeme)), literal(std::move(literal)), line(line),
          column(column), visibility(visibility) {
    }
};

#endif //TOKEN_TYPE_H
