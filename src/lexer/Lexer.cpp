//
// Created by Wylan Shoemaker on 6/2/2025.
//

#include "../../include/lexer/Lexer.h"
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string.h>
#include <utility>

Lexer::Lexer(std::string src, const std::string &filename)
    : source(std::move(src)), context(filename) {
}

bool Lexer::has_more_tokens() const {
    return current < source.length();
}

char Lexer::peek() const {
    return current < source.size() ? source[current] : '\0';
}

char Lexer::peek_next() const {
    return current + 1 < source.size() ? source[current + 1] : '\0';
}

char Lexer::advance() {
    char c = peek();
    ++current;
    context.advance(c);
    return c;
}

bool Lexer::match(char expected) {
    if (peek() != expected) return false;
    advance();
    return true;
}

void Lexer::skip_whitespace() {
    while (true) {
        char c = peek();
        switch (c) {
            case ' ':
            case '\t':
            case '\r':
            case '\n':
                advance();
                break;
            case '/':
                if (peek_next() == '/') {
                    skip_comment();
                } else {
                    return;
                }
                break;
            default:
                return;
        }
    }
}

void Lexer::skip_comment() {
    while (peek() != '\n' && peek() != '\0') {
        advance();
    }
}

Token Lexer::make_token(TokenType type, const std::string &lexeme, const Literal &literal) {
    return {type, lexeme, literal, context.line(), context.column()};
}

Token Lexer::make_char_token(TokenType type, const char &lexeme, const Literal &literal) {
    char str1[2] = {lexeme, '\0'};
    char str2[5] = "";
    return {type, strcpy(str2, str1), literal, context.line(), context.column()};
}

Token Lexer::next_token() {
    skip_whitespace();
    start = current;

    if (!has_more_tokens()) {
        return make_token(TokenType::END_OF_FILE, "");
    }

    char c = advance();

    if (std::isalpha(c) || c == '_') return identifier();
    if (std::isdigit(c)) return number();

    switch (c) {
        case '"': return string();
        case '\'': return character();
        case '+': return make_token(TokenType::PLUS, "+");
        case '-': return match('>') ? make_token(TokenType::ARROW, "->") : make_token(TokenType::MINUS, "-");
        case '*': return make_token(TokenType::STAR, "*");
        case '/': return make_token(TokenType::SLASH, "/");
        case '=': return match('=') ? make_token(TokenType::EQUAL_EQUAL, "==") : make_token(TokenType::EQUAL, "=");
        case '!': return match('=') ? make_token(TokenType::NOT_EQUAL, "!=") : make_token(TokenType::NOT, "!");
        case '(': return make_token(TokenType::LEFT_PAREN, "(");
        case ')': return make_token(TokenType::RIGHT_PAREN, ")");
        case '{': return make_token(TokenType::LEFT_BRACE, "{");
        case '}': return make_token(TokenType::RIGHT_BRACE, "}");
        case ';': return make_token(TokenType::SEMICOLON, ";");
        case ':': return match(':') ? make_token(TokenType::DOUBLE_COLON, "::") : make_token(TokenType::COLON, ":");
        case ',': return make_token(TokenType::COMMA, ",");
        case '>': {
            if (match('=')) return make_token(TokenType::GREATER_EQUAL, ">=");
            if (match('>')) return make_token(TokenType::SHIFT_RIGHT, ">>");
            return make_token(TokenType::GREATER, ">");
        }
        case '<': {
            if (match('=')) return make_token(TokenType::LESS_EQUAL, "<=");
            if (match('>')) return make_token(TokenType::SHIFT_LEFT, "<<");
            return make_token(TokenType::LESS, "<");
        }
        case '.': {
            if (match('.')) {
                if (match('=')) return make_token(TokenType::RANGE_INCLUSIVE, "..=");
                return make_token(TokenType::RANGE, "..");
            }
            return make_token(TokenType::DOT, ".");
        }
        case '&': {
            if (match('&')) {
                return make_token(TokenType::AND, "&&");
            }
            return make_token(TokenType::BIT_AND, "&");
        }

        default: return make_token(TokenType::UNKNOWN, std::string(1, c));
    }
}

Token Lexer::identifier() {
    while (std::isalnum(peek()) || peek() == '_') advance();
    std::string text = source.substr(start, current - start);
    TokenType type = keyword_or_identifier(text);
    return make_token(type, text);
}

TokenType Lexer::keyword_or_identifier(const std::string &text) {
    auto it = keywords.find(text);
    return it != keywords.end() ? it->second : TokenType::IDENTIFIER;
}

Token Lexer::number() {
    bool isFloatLike = false;
    bool hasDot = false;

    while (std::isdigit(peek())) advance();

    if (peek() == '.' && std::isdigit(peek_next())) {
        hasDot = true;
        isFloatLike = true;
        advance(); // consume '.'
        while (std::isdigit(peek())) advance();
    }

    // Optional suffix
    char suffix = '\0';
    if (std::isalpha(peek())) {
        suffix = peek();
        if (suffix == 'f' || suffix == 'F' ||
            suffix == 'd' || suffix == 'D' ||
            suffix == 'i' || suffix == 'I') {
            advance(); // consume suffix
        } else {
            suffix = '\0'; // Not a valid numeric suffix
        }
    }

    std::string text = source.substr(start, current - start);
    std::string numericPart = text;

    if (suffix != '\0') {
        numericPart.pop_back(); // remove suffix for parsing
    }

    switch (suffix) {
        case 'f':
        case 'F':
            return make_token(TokenType::FLOAT_LITERAL, text, std::stof(numericPart));
        case 'd':
        case 'D':
            return make_token(TokenType::DOUBLE_LITERAL, text, std::stod(numericPart));
        case 'i':
        case 'I':
            return make_token(TokenType::INT_LITERAL, text, std::stoll(numericPart));
        default: ;
    }

    // Default behavior
    if (hasDot || isFloatLike) {
        return make_token(TokenType::DOUBLE_LITERAL, text, std::stod(numericPart));
    } else {
        return make_token(TokenType::INT_LITERAL, text, std::stoll(numericPart));
    }
}

Token Lexer::string() {
    while (peek() != '"' && peek() != '\0') advance();
    if (peek() == '"') advance(); // consume closing quote
    std::string text = source.substr(start + 1, current - start - 2); // exclude quotes
    return make_token(TokenType::STRING_LITERAL, "\"" + text + "\"", text);
}

Token Lexer::character() {
    char c = peek();
    advance();
    if (peek() == '\'') advance();
    return make_char_token(TokenType::CHAR_LITERAL, c, c);
}

const std::unordered_map<std::string, TokenType> Lexer::keywords = {
    {"as", TokenType::AS},
    {"async", TokenType::ASYNC},
    {"await", TokenType::AWAIT},
    {"break", TokenType::BREAK},
    {"bundle", TokenType::BUNDLE},
    {"char", TokenType::CHAR},
    {"class", TokenType::CLASS},
    {"const", TokenType::CONST},
    {"continue", TokenType::CONTINUE},
    {"double", TokenType::DOUBLE},
    {"else", TokenType::ELSE},
    {"enum", TokenType::ENUM},
    {"Fail", TokenType::FAIL},
    {"false", TokenType::FALSE_VALUE},

    {"float", TokenType::FLOAT64},
    {"f8", TokenType::FLOAT8},
    {"f16", TokenType::FLOAT16},
    {"f32", TokenType::FLOAT32},
    {"f64", TokenType::FLOAT64},
    {"f128", TokenType::FLOAT128},

    {"for", TokenType::FOR},
    {"func", TokenType::FUNC},
    {"if", TokenType::IF},
    {"impl", TokenType::IMPL},
    {"import", TokenType::IMPORT},

    {"int", TokenType::INT64},
    {"int8", TokenType::INT8},
    {"int16", TokenType::INT16},
    {"int32", TokenType::INT32},
    {"int64", TokenType::INT64},
    {"int128", TokenType::INT128},

    {"let", TokenType::LET},
    {"match", TokenType::MATCH},
    {"module", TokenType::MODULE},
    {"null", TokenType::NULL_VALUE},
    {"Ok", TokenType::OK},
    {"ret", TokenType::RETURN},
    {"string", TokenType::STRING},
    {"struct", TokenType::STRUCT},
    {"super", TokenType::SUPER},
    {"this", TokenType::THIS},
    {"true", TokenType::TRUE_VALUE},
    {"type", TokenType::TYPE},

    {"uint", TokenType::UINT64},
    {"uint8", TokenType::UINT8},
    {"uint16", TokenType::UINT16},
    {"uint32", TokenType::UINT32},
    {"uint64", TokenType::UINT64},
    {"uint128", TokenType::UINT128},

    {"use", TokenType::USE},
    {"var", TokenType::VAR},
    {"while", TokenType::WHILE},
    {"yield", TokenType::YIELD},
};
