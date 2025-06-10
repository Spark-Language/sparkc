//
// Created by Wylan Shoemaker on 6/2/2025.
//

#include "../../include/lexer/Lexer.h"

#include <algorithm>
#include <cctype>
#include <functional>
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
                    break;
                }

                if (peek_next() == '*') {
                    if (peek_next() == '*') skip_documentation_comment();
                    else skip_block_comment();
                    break;
                }

                return;
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

void Lexer::skip_block_comment() {
    while (!(peek() == '*' && peek_next() == '/') && peek() != '\0') {
        advance();
    }

    if (peek() == '\0') return;
    advance(); // consume '*'
    advance(); // consume '/'
}

void Lexer::skip_documentation_comment() {
    while (!(peek() == '*' && peek_next() == '/') && peek() != '\0') {
        advance();
    }

    if (peek() == '\0') return;
    advance(); // consume '*'
    advance(); // consume '/'
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
        case '+': {
            if (match('=')) return make_token(TokenType::PLUS_EQUAL, "+=");
            return make_token(TokenType::PLUS, "+");
        }
        case '-': {
            if (match('=')) return make_token(TokenType::MINUS_EQUAL, "-=");
            if (match('>')) return make_token(TokenType::ARROW, "->");
            return make_token(TokenType::MINUS, "-");
        }
        case '*': {
            if (match('=')) return make_token(TokenType::STAR_EQUAL, "*=");
            return make_token(TokenType::STAR, "*");
        }
        case '/': {
            if (match('=')) return make_token(TokenType::SLASH_EQUAL, "/=");
            return make_token(TokenType::SLASH, "/");
        }
        case '=': {
            if (match('=')) return make_token(TokenType::EQUAL_EQUAL, "==");
            if (match('>')) return make_token(TokenType::FAT_ARROW, "=>");
            return make_token(TokenType::EQUAL, "=");
        }
        case '%': {
            if (match('=')) return make_token(TokenType::MODULO_EQUAL, "%=");
            return make_token(TokenType::MODULO, "%");
        }
        case '^': {
            if (match('=')) return make_token(TokenType::XOR_EQUAL, "^=");
            return make_token(TokenType::BIT_XOR, "^");
        }
        case '!': return match('=') ? make_token(TokenType::NOT_EQUAL, "!=") : make_token(TokenType::NOT, "!");
        case '?': return make_token(TokenType::QUESTION, "?");
        case '(': return make_token(TokenType::LEFT_PAREN, "(");
        case ')': return make_token(TokenType::RIGHT_PAREN, ")");
        case '{': return make_token(TokenType::LEFT_BRACE, "{");
        case '}': return make_token(TokenType::RIGHT_BRACE, "}");
        case '[': return make_token(TokenType::LEFT_BRACKET, "[");
        case ']': return make_token(TokenType::RIGHT_BRACKET, "]");
        case ';': return make_token(TokenType::SEMICOLON, ";");
        case ':': return match(':') ? make_token(TokenType::DOUBLE_COLON, "::") : make_token(TokenType::COLON, ":");
        case ',': return make_token(TokenType::COMMA, ",");
        case '|': {
            if (match('|')) return make_token(TokenType::OR, "||");
            if (match('=')) return make_token(TokenType::OR_EQUAL, "|=");
            return make_token(TokenType::BIT_AND, "|");
        }
        case '>': {
            if (match('=')) return make_token(TokenType::GREATER_EQUAL, ">=");
            if (match('>')) {
                if (match('=')) return make_token(TokenType::SHR_EQUAL, ">>=");
                return make_token(TokenType::SHIFT_RIGHT, ">>");
            }
            return make_token(TokenType::GREATER, ">");
        }
        case '<': {
            if (match('=')) return make_token(TokenType::LESS_EQUAL, "<=");
            if (match('<')) {
                if (match('=')) return make_token(TokenType::SHL_EQUAL, "<<=");
                return make_token(TokenType::SHIFT_LEFT, "<<");
            }
            return make_token(TokenType::LESS, "<");
        }
        case '.': {
            if (match('.')) {
                if (match('=')) return make_token(TokenType::RANGE_INCLUSIVE, "..=");
                if (match('.')) return make_token(TokenType::ELLIPSIS, "...");
                return make_token(TokenType::RANGE, "..");
            }
            return make_token(TokenType::DOT, ".");
        }
        case '&': {
            if (match('&')) return make_token(TokenType::AND, "&&");
            if (match('=')) return make_token(TokenType::AND_EQUAL, "=");
            return make_token(TokenType::BIT_AND, "&");
        }
        case '~': return make_token(TokenType::TILDE, "~");
        case '\\': return make_token(TokenType::BACKSLASH, "\\");
        case '@': return make_token(TokenType::AT, "@");
        case '#': return make_token(TokenType::HASH, "#");
        case '$': return make_token(TokenType::DOLLAR, "$"); // TODO: Probably wont stay

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
    bool hasDot = false;

    // scan digits, underscores, and at most one dot
    //    (we assume `start` is at the first digit)
    while (true) {
        char c = peek();
        if (std::isdigit(c) || c == '_') {
            advance();
        } else if (c == '.' && !hasDot && std::isdigit(peek_next())) {
            hasDot = true;
            advance();           // consume '.'
        } else {
            break;
        }
    }
    // mark where the “numeric part” ends
    size_t numericEnd = current;

    // scan suffix (letters+digits only)
    std::string suffix;
    while (std::isalpha(peek()) || std::isdigit(peek())) {
        suffix.push_back(peek());
        advance();
    }

    // extract raw text & numeric substring
    std::string text           = source.substr(start, current - start);
    std::string rawNumericPart = source.substr(start, numericEnd - start);

    // no leading/trailing underscores
    if (rawNumericPart.front() == '_' ||
        rawNumericPart.back()  == '_') {
            // TODO: should probably thrown an error
            return identifier();
        }

    // strip ALL underscores before parsing
    std::string cleanNumeric;
    cleanNumeric.reserve(rawNumericPart.size());
    for (char c : rawNumericPart) {
        if (c != '_') cleanNumeric.push_back(c);
    }

    return makeNumberTokenFromSuffix(
        text,
        cleanNumeric,
        suffix,
        hasDot
    );
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
    {"abstract", TokenType::ABSTRACT},
    {"as", TokenType::AS},
    {"async", TokenType::ASYNC},
    {"await", TokenType::AWAIT},
    {"bool", TokenType::BOOLEAN},
    {"break", TokenType::BREAK},
    {"bundle", TokenType::BUNDLE},
    {"case", TokenType::CASE},
    {"char", TokenType::CHAR},
    {"class", TokenType::CLASS},
    {"const", TokenType::CONST},
    {"continue", TokenType::CONTINUE},
    {"default", TokenType::DEFAULT},
    {"do", TokenType::DO},
    {"double", TokenType::DOUBLE},
    {"else", TokenType::ELSE},
    {"enum", TokenType::ENUM},
    {"Fail", TokenType::FAIL},
    {"false", TokenType::FALSE_VALUE},
    {"final", TokenType::FINAL},

    {"float", TokenType::FLOAT64},
    {"f8", TokenType::FLOAT8},
    {"f16", TokenType::FLOAT16},
    {"f32", TokenType::FLOAT32},
    {"f64", TokenType::FLOAT64},

    {"for", TokenType::FOR},
    {"func", TokenType::FUNC},
    {"if", TokenType::IF},
    {"impl", TokenType::IMPL},
    {"import", TokenType::IMPORT},

    {"goto", TokenType::GOTO},
    {"inline", TokenType::INLINE},

    {"int", TokenType::INT64},
    {"i8", TokenType::INT8},
    {"i16", TokenType::INT16},
    {"i32", TokenType::INT32},
    {"i64", TokenType::INT64},

    {"inter", TokenType::INTER},
    {"internal", TokenType::INTERNAL},
    {"is", TokenType::IS},
    {"let", TokenType::LET},
    {"match", TokenType::MATCH},
    {"module", TokenType::MODULE},
    {"new", TokenType::NEW},
    {"null", TokenType::NULL_VALUE},
    {"Ok", TokenType::OK},
    {"override", TokenType::OVERRIDE},
    {"private", TokenType::PRIVATE},
    {"public", TokenType::PUBLIC},
    {"ret", TokenType::RETURN},
    {"sizeof", TokenType::SIZEOF},
    {"spawn", TokenType::SPAWN},
    {"static", TokenType::STATIC},
    {"string", TokenType::STRING},
    {"struct", TokenType::STRUCT},
    {"super", TokenType::SUPER},
    {"this", TokenType::THIS},
    {"thread", TokenType::THREAD},
    {"true", TokenType::TRUE_VALUE},
    {"type", TokenType::TYPE},
    {"typeof", TokenType::TYPEOF},

    {"uint", TokenType::UINT64},
    {"u8", TokenType::UINT8},
    {"u16", TokenType::UINT16},
    {"u32", TokenType::UINT32},
    {"u64", TokenType::UINT64},

    {"use", TokenType::USE},
    {"atomic", TokenType::ATOMIC},
    {"var", TokenType::VAR},
    {"virtual", TokenType::VIRTUAL},
    {"while", TokenType::WHILE},
    {"yield", TokenType::YIELD},
};

Token Lexer::makeNumberTokenFromSuffix(const std::string& text, const std::string& numericPart, const std::string& suffix, bool hasDot) {
    // lowercase the suffix once
    std::string sfx = suffix;
    std::transform(sfx.begin(), sfx.end(), sfx.begin(), [](unsigned char c){ return std::tolower(c); });

    // map suffix → a lambda that builds the right Token
    static const std::unordered_map<std::string, std::function<Token(const std::string&, const std::string&)>>
    handlers = {
        // floats
        { "f", [&](const auto &fullText, const auto &numericStr) { return make_token(TokenType::FLOAT64_LITERAL,  fullText, std::stof(numericStr));}},
        { "f8", [&](const auto &fullText, const auto &numericStr) { return make_token(TokenType::FLOAT8_LITERAL,  fullText, std::stof(numericStr));}},
        { "f16", [&](const auto &fullText, const auto &numericStr) { return make_token(TokenType::FLOAT16_LITERAL,  fullText, std::stof(numericStr));}},
        { "f32", [&](const auto &fullText, const auto &numericStr) { return make_token(TokenType::FLOAT32_LITERAL,  fullText, std::stof(numericStr));}},
        { "f64", [&](const auto &fullText, const auto &numericStr) { return make_token(TokenType::FLOAT64_LITERAL,  fullText, std::stof(numericStr));}},

        // doubles
        {"d",  [&](const auto &fullText, const auto &numericStr){ return make_token(TokenType::DOUBLE_LITERAL, fullText, std::stod(numericStr)); }},

        // signed ints
        {"i8", [&](const auto &fullText, const auto &numericStr){ return make_token(TokenType::INT8_LITERAL,  fullText, std::stoll(numericStr)); }},
        {"i16", [&](const auto &fullText, const auto &numericStr){ return make_token(TokenType::INT16_LITERAL, fullText, std::stoll(numericStr)); }},
        {"i32", [&](const auto &fullText, const auto &numericStr){ return make_token(TokenType::INT32_LITERAL, fullText, std::stoll(numericStr)); }},
        {"i64", [&](const auto &fullText, const auto &numericStr){ return make_token(TokenType::INT64_LITERAL, fullText, std::stoll(numericStr)); }},

        // unsigned ints
        {"u8", [&](const auto &fullText, const auto &numericStr){ return make_token(TokenType::UINT8_LITERAL,  fullText, std::stoll(numericStr)); }},
        {"u16", [&](const auto &fullText, const auto &numericStr){ return make_token(TokenType::UINT16_LITERAL, fullText, std::stoll(numericStr)); }},
        {"u32", [&](const auto &fullText, const auto &numericStr){ return make_token(TokenType::UINT32_LITERAL, fullText, std::stoll(numericStr)); }},
        {"u64", [&](const auto &fullText, const auto &numericStr){ return make_token(TokenType::UINT64_LITERAL, fullText, std::stoll(numericStr)); }},

    };

    if (auto it = handlers.find(sfx); it != handlers.end()) {
        // found a custom handler for this suffix
        return it->second(text, numericPart);
    }

    // fallback: choose double vs. int64 by whether we saw a dot
    if (hasDot) {
        return make_token(TokenType::DOUBLE_LITERAL, text, std::stod(numericPart));
    }

    return make_token(TokenType::INT64_LITERAL, text, std::stoll(numericPart));
}
