//
// Created by Wylan Shoemaker on 6/2/2025.
//

#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <unordered_map>
#include <variant>

#include "../util/SourceContext.h"
#include "../tokens/TokenType.h"

class Lexer {
public:
    Lexer(std::string source, const std::string &filename);

    Token next_token();

    [[nodiscard]]
    bool has_more_tokens() const;

private:
    [[nodiscard]]
    char peek() const;

    [[nodiscard]]
    char peek_next() const;

    char advance();

    bool match(char expected);

    void skip_whitespace();

    void skip_comment();

    Token make_token(TokenType type, const std::string &lexeme, const Literal &literal = {});

    Token make_char_token(TokenType type, const char &lexeme, const Literal &literal = {});

    Token identifier();

    Token number();

    Token string();

    Token character();

    [[nodiscard]]
    static TokenType keyword_or_identifier(const std::string &text);

    std::string source;
    size_t start = 0;
    size_t current = 0;
    SourceContext context;

    static const std::unordered_map<std::string, TokenType> keywords;
};


#endif //LEXER_H
