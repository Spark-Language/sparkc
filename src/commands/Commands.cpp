//
// Created by Wylan Shoemaker on 6/2/2025.
//

#include "../../include/commands/Commands.h"
#include "../../include/lexer/Lexer.h"
#include "../../include/tokens/TokenCategory.h"

#include <iostream>
#include <fstream>
#include <sstream>

static std::string read_file(const std::string& path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("Could not open file: " + path);
    std::ostringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

int Commands::run(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cerr << "No command provided. Use `spark help`.\n";
        return 1;
    }

    const std::string& command = args[0];

    if (command == "--lexer") return run_lexer(args);
    if (command == "--version") return run_version();
    if (command == "--help") return run_help();

    std::cerr << "Unknown command: " << command << "\n";
    return 1;
}

int Commands::run_lexer(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "Usage: spark lexer <file>\n";
        return 1;
    }

    const std::string& file = args[1];

    try {
        print_token_output(file);
    } catch (const std::exception& e) {
        std::cerr << "Lexer error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}

int Commands::run_version() {
    std::cout << "Spark Language Toolchain v0.1.0\n";
    return 0;
}

int Commands::run_help() {
    std::cout << "Spark CLI - available commands:\n";
    std::cout << "  spark --lexer <file>     Tokenize and print tokens from file\n";
    std::cout << "  spark --version          Show version information\n";
    std::cout << "  spark --help             Show this help message\n";
    return 0;
}

void Commands::print_token_output(const std::string& file) {
    std::string source = read_file(file);
    Lexer lexer(source, file);

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
}
