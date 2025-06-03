//
// Created by Wylan Shoemaker on 6/2/2025.
//

#ifndef TOKEN_CATEGORY_H
#define TOKEN_CATEGORY_H

#include "../../src/tokens/TokenType.cpp"

enum class TokenCategory {
    Identifier,
    Literal,
    Operator,
    Keyword,
    Punctuation,
    Grouping,
    Assignment,
    Comparison,
    Logical,
    Bitwise,
    Modifier,
    ControlFlow,
    Declaration,
    TypeSystem,
    Concurrency,
    Special,
    Unknown
};

TokenCategory get_token_category(TokenType type);
std::string_view category_to_string(TokenCategory category);
std::string_view token_type_to_string(TokenType type);

#endif //TOKEN_CATEGORY_H
