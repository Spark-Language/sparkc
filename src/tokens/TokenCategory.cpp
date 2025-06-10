//
// Created by Wylan Shoemaker on 6/2/2025.
//

#include "../../include/tokens/TokenCategory.h"

TokenCategory get_token_category(TokenType type) {
    switch (type) {
        // IDENTIFIERS
        case TokenType::IDENTIFIER:
            return TokenCategory::Identifier;

        // LITERALS
        case TokenType::INT8_LITERAL:
        case TokenType::INT16_LITERAL:
        case TokenType::INT32_LITERAL:
        case TokenType::INT64_LITERAL:

        case TokenType::UINT8_LITERAL:
        case TokenType::UINT16_LITERAL:
        case TokenType::UINT32_LITERAL:
        case TokenType::UINT64_LITERAL:

        case TokenType::FLOAT8_LITERAL:
        case TokenType::FLOAT16_LITERAL:
        case TokenType::FLOAT32_LITERAL:
        case TokenType::FLOAT64_LITERAL:

        case TokenType::DOUBLE_LITERAL:
        case TokenType::STRING_LITERAL:
        case TokenType::CHAR_LITERAL:
        case TokenType::BOOLEAN_LITERAL:
        case TokenType::NULL_LITERAL:
        case TokenType::TRUE_VALUE:
        case TokenType::FALSE_VALUE:
        case TokenType::NULL_VALUE:
        case TokenType::OK:
        case TokenType::FAIL:
            return TokenCategory::Literal;

        // ARITHMETIC OPERATORS
        case TokenType::PLUS:
        case TokenType::MINUS:
        case TokenType::STAR:
        case TokenType::SLASH:
        case TokenType::MODULO:
            return TokenCategory::Operator;

        // ASSIGNMENT OPERATORS
        case TokenType::EQUAL:
        case TokenType::PLUS_EQUAL:
        case TokenType::MINUS_EQUAL:
        case TokenType::STAR_EQUAL:
        case TokenType::SLASH_EQUAL:
        case TokenType::MODULO_EQUAL:
        case TokenType::AND_EQUAL:
        case TokenType::OR_EQUAL:
        case TokenType::XOR_EQUAL:
        case TokenType::SHL_EQUAL:
        case TokenType::SHR_EQUAL:
            return TokenCategory::Assignment;

        // COMPARISON
        case TokenType::EQUAL_EQUAL:
        case TokenType::NOT_EQUAL:
        case TokenType::LESS:
        case TokenType::LESS_EQUAL:
        case TokenType::GREATER:
        case TokenType::GREATER_EQUAL:
            return TokenCategory::Comparison;

        // LOGICAL
        case TokenType::AND:
        case TokenType::OR:
        case TokenType::NOT:
            return TokenCategory::Logical;

        // BITWISE
        case TokenType::BIT_AND:
        case TokenType::BIT_OR:
        case TokenType::BIT_XOR:
        case TokenType::SHIFT_LEFT:
        case TokenType::SHIFT_RIGHT:
            return TokenCategory::Bitwise;

        // GROUPING & PUNCTUATION
        case TokenType::LEFT_PAREN:
        case TokenType::RIGHT_PAREN:
        case TokenType::LEFT_BRACE:
        case TokenType::RIGHT_BRACE:
        case TokenType::LEFT_BRACKET:
        case TokenType::RIGHT_BRACKET:
            return TokenCategory::Grouping;

        case TokenType::COMMA:
        case TokenType::DOT:
        case TokenType::COLON:
        case TokenType::DOUBLE_COLON:
        case TokenType::SEMICOLON:
        case TokenType::ARROW:
        case TokenType::FAT_ARROW:
        case TokenType::ELLIPSIS:
        case TokenType::RANGE:
        case TokenType::RANGE_INCLUSIVE:
        case TokenType::QUESTION:
        case TokenType::TILDE:
        case TokenType::BACKSLASH:
        case TokenType::AT:
        case TokenType::HASH:
        case TokenType::DOLLAR:
        case TokenType::QUOTE:
        case TokenType::APOSTROPHE:
            return TokenCategory::Punctuation;

        // CONTROL FLOW
        case TokenType::IF:
        case TokenType::ELSE:
        case TokenType::SWITCH:
        case TokenType::MATCH:
        case TokenType::CASE:
        case TokenType::DEFAULT:
        case TokenType::FOR:
        case TokenType::WHILE:
        case TokenType::DO:
        case TokenType::BREAK:
        case TokenType::CONTINUE:
        case TokenType::RETURN:
        case TokenType::YIELD:
        case TokenType::GOTO:
            return TokenCategory::ControlFlow;

        // DECLARATIONS
        case TokenType::FUNC:
        case TokenType::VAR:
        case TokenType::LET:
        case TokenType::CONST:
        case TokenType::TYPE:
        case TokenType::STRUCT:
        case TokenType::CLASS:
        case TokenType::INTER:
        case TokenType::IMPL:
        case TokenType::ENUM:
        case TokenType::UNION:
        case TokenType::MODULE:
        case TokenType::IMPORT:
        case TokenType::USE:
        case TokenType::ATOMIC:

        case TokenType::INT8:
        case TokenType::INT16:
        case TokenType::INT32:
        case TokenType::INT64:

        case TokenType::UINT8:
        case TokenType::UINT16:
        case TokenType::UINT32:
        case TokenType::UINT64:

        case TokenType::FLOAT8:
        case TokenType::FLOAT16:
        case TokenType::FLOAT32:
        case TokenType::FLOAT64:

        case TokenType::DOUBLE:
        case TokenType::BOOLEAN:
        case TokenType::CHAR:
        case TokenType::STRING:
            return TokenCategory::Declaration;

        // MODIFIERS / ACCESS
        case TokenType::PUBLIC:
        case TokenType::PRIVATE:
        case TokenType::INTERNAL:
        case TokenType::STATIC:
        case TokenType::ABSTRACT:
        case TokenType::FINAL:
        case TokenType::OVERRIDE:
        case TokenType::VIRTUAL:
        case TokenType::INLINE:
            return TokenCategory::Modifier;

        // CONCURRENCY
        case TokenType::ASYNC:
        case TokenType::AWAIT:
        case TokenType::SPAWN:
        case TokenType::THREAD:
            return TokenCategory::Concurrency;

        // TYPE SYSTEM
        case TokenType::AS:
        case TokenType::IS:
        case TokenType::TYPEOF:
        case TokenType::SIZEOF:
        case TokenType::NEW:
        case TokenType::THIS:
        case TokenType::SUPER:
            return TokenCategory::TypeSystem;

        // SPECIAL
        case TokenType::BUNDLE:
        case TokenType::END_OF_FILE:
            return TokenCategory::Special;

        // UNKNOWN
        case TokenType::UNKNOWN:
        default:
            return TokenCategory::Unknown;
    }
}

std::string_view category_to_string(TokenCategory category) {
    switch (category) {
        case TokenCategory::Identifier: return "Identifier";
        case TokenCategory::Literal: return "Literal";
        case TokenCategory::Operator: return "Operator";
        case TokenCategory::Keyword: return "Keyword";
        case TokenCategory::Punctuation: return "Punctuation";
        case TokenCategory::Grouping: return "Grouping";
        case TokenCategory::Assignment: return "Assignment";
        case TokenCategory::Comparison: return "Comparison";
        case TokenCategory::Logical: return "Logical";
        case TokenCategory::Bitwise: return "Bitwise";
        case TokenCategory::Modifier: return "Modifier";
        case TokenCategory::ControlFlow: return "ControlFlow";
        case TokenCategory::Declaration: return "Declaration";
        case TokenCategory::TypeSystem: return "TypeSystem";
        case TokenCategory::Concurrency: return "Concurrency";
        case TokenCategory::Special: return "Special";
        case TokenCategory::Unknown: return "Unknown";
        default: return "Invalid";
    }
}

std::string_view token_type_to_string(TokenType type) {
    switch (type) {
        // IDENTIFIERS
        case TokenType::IDENTIFIER: return "IDENTIFIER";

        // LITERALS
        case TokenType::INT8_LITERAL: return "INT8_LITERAL";
        case TokenType::INT16_LITERAL: return "INT16_LITERAL";
        case TokenType::INT32_LITERAL: return "INT32_LITERAL";
        case TokenType::INT64_LITERAL: return "INT64_LITERAL";

        case TokenType::UINT8_LITERAL: return "UINT8_LITERAL";
        case TokenType::UINT16_LITERAL: return "UINT16_LITERAL";
        case TokenType::UINT32_LITERAL: return "UINT32_LITERAL";
        case TokenType::UINT64_LITERAL: return "UINT64_LITERAL";

        case TokenType::FLOAT8_LITERAL: return "FLOAT8_LITERAL";
        case TokenType::FLOAT16_LITERAL: return "FLOAT16_LITERAL";
        case TokenType::FLOAT32_LITERAL: return "FLOAT32_LITERAL";
        case TokenType::FLOAT64_LITERAL: return "FLOAT64_LITERAL";

        case TokenType::DOUBLE_LITERAL: return "DOUBLE_LITERAL";
        case TokenType::STRING_LITERAL: return "STRING_LITERAL";
        case TokenType::CHAR_LITERAL: return "CHAR_LITERAL";
        case TokenType::BOOLEAN_LITERAL: return "BOOLEAN_LITERAL";
        case TokenType::NULL_LITERAL: return "NULL_LITERAL";
        case TokenType::TRUE_VALUE: return "TRUE_VALUE";
        case TokenType::FALSE_VALUE: return "FALSE_VALUE";
        case TokenType::NULL_VALUE: return "NULL_VALUE";
        case TokenType::OK: return "OK";
        case TokenType::FAIL: return "FAIL";

        // ARITHMETIC OPERATORS
        case TokenType::PLUS: return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::STAR: return "STAR";
        case TokenType::SLASH: return "SLASH";
        case TokenType::MODULO: return "MODULO";

        // ASSIGNMENT OPERATORS
        case TokenType::EQUAL: return "EQUAL";
        case TokenType::PLUS_EQUAL: return "PLUS_EQUAL";
        case TokenType::MINUS_EQUAL: return "MINUS_EQUAL";
        case TokenType::STAR_EQUAL: return "STAR_EQUAL";
        case TokenType::SLASH_EQUAL: return "SLASH_EQUAL";
        case TokenType::MODULO_EQUAL: return "MODULO_EQUAL";
        case TokenType::AND_EQUAL: return "AND_EQUAL";
        case TokenType::OR_EQUAL: return "OR_EQUAL";
        case TokenType::XOR_EQUAL: return "XOR_EQUAL";
        case TokenType::SHL_EQUAL: return "SHL_EQUAL";
        case TokenType::SHR_EQUAL: return "SHR_EQUAL";

        // COMPARISON
        case TokenType::EQUAL_EQUAL: return "EQUAL_EQUAL";
        case TokenType::NOT_EQUAL: return "NOT_EQUAL";
        case TokenType::LESS: return "LESS";
        case TokenType::LESS_EQUAL: return "LESS_EQUAL";
        case TokenType::GREATER: return "GREATER";
        case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";

        // LOGICAL
        case TokenType::AND: return "AND";
        case TokenType::OR: return "OR";
        case TokenType::NOT: return "NOT";

        // BITWISE
        case TokenType::BIT_AND: return "BIT_AND";
        case TokenType::BIT_OR: return "BIT_OR";
        case TokenType::BIT_XOR: return "BIT_XOR";
        case TokenType::SHIFT_LEFT: return "SHIFT_LEFT";
        case TokenType::SHIFT_RIGHT: return "SHIFT_RIGHT";

        // GROUPING & PUNCTUATION
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::LEFT_BRACE: return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
        case TokenType::LEFT_BRACKET: return "LEFT_BRACKET";
        case TokenType::RIGHT_BRACKET: return "RIGHT_BRACKET";

        case TokenType::COMMA: return "COMMA";
        case TokenType::DOT: return "DOT";
        case TokenType::COLON: return "COLON";
        case TokenType::DOUBLE_COLON: return "DOUBLE_COLON";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::ARROW: return "ARROW";
        case TokenType::FAT_ARROW: return "FAT_ARROW";
        case TokenType::ELLIPSIS: return "ELLIPSIS";
        case TokenType::RANGE: return "RANGE";
        case TokenType::RANGE_INCLUSIVE: return "RANGE_INCLUSIVE";
        case TokenType::QUESTION: return "QUESTION";
        case TokenType::TILDE: return "TILDE";
        case TokenType::BACKSLASH: return "BACKSLASH";
        case TokenType::AT: return "AT";
        case TokenType::HASH: return "HASH";
        case TokenType::DOLLAR: return "DOLLAR";
        case TokenType::QUOTE: return "QUOTE";
        case TokenType::APOSTROPHE: return "APOSTROPHE";

        // CONTROL FLOW
        case TokenType::IF: return "IF";
        case TokenType::ELSE: return "ELSE";
        case TokenType::SWITCH: return "SWITCH";
        case TokenType::MATCH: return "MATCH";
        case TokenType::CASE: return "CASE";
        case TokenType::DEFAULT: return "DEFAULT";
        case TokenType::FOR: return "FOR";
        case TokenType::WHILE: return "WHILE";
        case TokenType::DO: return "DO";
        case TokenType::BREAK: return "BREAK";
        case TokenType::CONTINUE: return "CONTINUE";
        case TokenType::RETURN: return "RETURN";
        case TokenType::YIELD: return "YIELD";
        case TokenType::GOTO: return "GOTO";

        // DECLARATIONS
        case TokenType::FUNC: return "FUNCTION";
        case TokenType::VAR: return "VARIABLE";
        case TokenType::LET: return "LET";
        case TokenType::CONST: return "CONSTANT";
        case TokenType::TYPE: return "TYPE";
        case TokenType::STRUCT: return "STRUCTURE";
        case TokenType::CLASS: return "CLASS";
        case TokenType::INTER: return "INTERFACE";
        case TokenType::IMPL: return "IMPLEMENTATION";
        case TokenType::ENUM: return "ENUMERATOR";
        case TokenType::UNION: return "UNION";
        case TokenType::MODULE: return "MODULE";
        case TokenType::IMPORT: return "IMPORT";
        case TokenType::USE: return "USE";
        case TokenType::ATOMIC: return "ATOMIC";

        case TokenType::INT8: return "INT8";
        case TokenType::INT16: return "INT16";
        case TokenType::INT32: return "INT32";
        case TokenType::INT64: return "INT64";

        case TokenType::UINT8: return "UINT8";
        case TokenType::UINT16: return "UINT16";
        case TokenType::UINT32: return "UINT32";
        case TokenType::UINT64: return "UINT64";

        case TokenType::FLOAT8: return "FLOAT8";
        case TokenType::FLOAT16: return "FLOAT16";
        case TokenType::FLOAT32: return "FLOAT32";
        case TokenType::FLOAT64: return "FLOAT64";

        case TokenType::DOUBLE: return "DOUBLE";
        case TokenType::BOOLEAN: return "BOOLEAN";
        case TokenType::CHAR: return "CHARACTER";
        case TokenType::STRING: return "STRING";

        // MODIFIERS / ACCESS
        case TokenType::PUBLIC: return "PUBLIC";
        case TokenType::PRIVATE: return "PRIVATE";
        case TokenType::INTERNAL: return "INTERNAL";
        case TokenType::STATIC: return "STATIC";
        case TokenType::ABSTRACT: return "ABSTRACT";
        case TokenType::FINAL: return "FINAL";
        case TokenType::OVERRIDE: return "OVERRIDE";
        case TokenType::VIRTUAL: return "VIRTUAL";
        case TokenType::INLINE: return "INLINE";

        // CONCURRENCY
        case TokenType::ASYNC: return "ASYNC";
        case TokenType::AWAIT: return "AWAIT";
        case TokenType::SPAWN: return "SPAWN";
        case TokenType::THREAD: return "THREAD";

        // TYPE SYSTEM
        case TokenType::AS: return "AS";
        case TokenType::IS: return "IS";
        case TokenType::TYPEOF: return "TYPEOF";
        case TokenType::SIZEOF: return "SIZEOF";
        case TokenType::NEW: return "NEW";
        case TokenType::THIS: return "THIS";
        case TokenType::SUPER: return "SUPER";

        // SPECIAL
        case TokenType::BUNDLE: return "BUNDLE";
        case TokenType::END_OF_FILE: return "END_OF_FILE";

        // UNKNOWN
        case TokenType::UNKNOWN: return "UNKNOWN";
        default: return "UNRECOGNIZED";
    }
}
