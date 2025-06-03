//
// Created by Wylan Shoemaker on 6/2/2025.
//

#ifndef COMMANDS_H
#define COMMANDS_H

#pragma once

#include <string>
#include <vector>

class Commands {
public:
    static int run(const std::vector<std::string>& args);

private:
    static int run_lexer(const std::vector<std::string>& args);
    static int run_parse(const std::vector<std::string>& args);
    static int run_check(const std::vector<std::string>& args);
    static int run_run(const std::vector<std::string>& args);
    static int run_format(const std::vector<std::string>& args);
    static int run_version();
    static int run_help();

    // Optional: Helper for file reading in shared logic
    static std::string read_file(const std::string& path);

    static void print_token_output(const std::string& file);
};

#endif //COMMANDS_H
