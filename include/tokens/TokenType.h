//
// Created by Wylan Shoemaker on 5/29/25.
//

#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#include <string>
#include <variant>
#include <cstdint>

// This enum defines all possible token types the lexer can emit
enum class TokenType {
    // ===== IDENTIFIERS & LITERALS =====
    IDENTIFIER,           // variable, function, or type names
    INT_LITERAL,          // e.g. 42
    FLOAT_LITERAL,        // e.g. 3.14f
    DOUBLE_LITERAL,       // e.g. 3.1415926535
    STRING_LITERAL,       // e.g. "hello"
    CHAR_LITERAL,         // e.g. 'a'
    BOOLEAN_LITERAL,      // true or false
    NULL_LITERAL,         // null, none, or nil

    // ===== STRUCTURAL & PUNCTUATION =====
    LEFT_PAREN,           // (
    RIGHT_PAREN,          // )
    LEFT_BRACE,           // {
    RIGHT_BRACE,          // }
    LEFT_BRACKET,         // [
    RIGHT_BRACKET,        // ]
    COMMA,                // ,
    DOT,                  // .
    COLON,                // :
    SEMICOLON,            // ;
    ARROW,                // ->
    FAT_ARROW,            // =>
    ELLIPSIS,             // ...
    RANGE,                // ..
    RANGE_INCLUSIVE,      // ..=
    QUOTE,                // ""
    APOSTROPHE,           // ''

    // ===== ARITHMETIC OPERATORS =====
    PLUS,                 // +
    MINUS,                // -
    STAR,                 // *
    SLASH,                // /
    MODULO,               // %

    // ===== BITWISE OPERATORS =====
    BIT_AND,              // &
    BIT_OR,               // |
    BIT_XOR,              // ^
    BIT_NOT,              // ~
    SHIFT_LEFT,           // <<
    SHIFT_RIGHT,          // >>

    // ===== ASSIGNMENT OPERATORS =====
    EQUAL,                // =
    PLUS_EQUAL,           // +=
    MINUS_EQUAL,          // -=
    STAR_EQUAL,           // *=
    SLASH_EQUAL,          // /=
    MODULO_EQUAL,         // %=
    AND_EQUAL,            // &=
    OR_EQUAL,             // |=
    XOR_EQUAL,            // ^=
    SHL_EQUAL,            // <<=
    SHR_EQUAL,            // >>=

    // ===== COMPARISON OPERATORS =====
    EQUAL_EQUAL,          // ==
    NOT_EQUAL,            // !=
    LESS,                 // <
    LESS_EQUAL,           // <=
    GREATER,              // >
    GREATER_EQUAL,        // >=

    // ===== LOGICAL OPERATORS =====
    AND,                  // &&
    OR,                   // ||
    NOT,                  // !

    // ===== MISC SYMBOLS =====
    QUESTION,             // ?
    TILDE,                // ~
    BACKSLASH,
    AT,                   // @
    HASH,                 // #
    DOLLAR,               // $

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
    RET,
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

    // ===== ACCESS CONTROL & MODIFIERS =====
    INTERNAL,
    STATIC,
    ABSTRACT,
    FINAL,
    OVERRIDE,
    VIRTUAL,
    INLINE,
    MUT,

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
    OK,                  // for Result types
    FAIL,                // for Result types

    // ===== SPECIAL =====
    END_OF_FILE,         // signals end of input
    UNKNOWN              // catch-all for error recovery
};

#endif //TOKEN_TYPE_H
