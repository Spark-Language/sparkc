//
// Created by wylan on 6/2/2025.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/tokens/TokenCategory.h"
#include "../include/lexer/Lexer.h"

std::string read_file(const std::string &path) {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("Could not open file: " + path);
    }

    std::ostringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./lexer_test <source_file>\n";
        return 1;
    }

    std::string filename = argv[1];
    std::string source;

    try {
        source = read_file(filename);
    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    Lexer lexer(source, filename);

    while (lexer.has_more_tokens()) {
        Token token = lexer.next_token();

        std::cout << "[" << token.line << ":" << token.column << "] "
                << "Type: " << token_type_to_string(token.type)
                << " | Lexeme: \"" << token.lexeme << "\"";

        if (std::holds_alternative<int64_t>(token.literal)) {
            std::cout << " | Literal: " << std::get<int64_t>(token.literal);
        } else if (std::holds_alternative<float>(token.literal)) {
            std::cout << " | Literal: " << std::get<float>(token.literal);
        } else if (std::holds_alternative<double>(token.literal)) {
            std::cout << " | Literal: " << std::get<double>(token.literal);
        } else if (std::holds_alternative<bool>(token.literal)) {
            std::cout << " | Literal: " << (std::get<bool>(token.literal) ? "true" : "false");
        } else if (std::holds_alternative<std::string>(token.literal)) {
            std::cout << " | Literal: \"" << std::get<std::string>(token.literal) << "\"";
        }

        std::cout << "\n";

        if (token.type == TokenType::END_OF_FILE) break;
    }

    return 0;
}
