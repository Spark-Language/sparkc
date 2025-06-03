//
// Created by Wylan Shoemaker on 6/2/2025.
//

#ifndef COMMANDS_H
#define COMMANDS_H
#include <string>
#include <vector>


class Commands {
public:
    static int run(const std::vector<std::string> &args);

private:
    static int run_lexer(const std::vector<std::string> &args);

    static int run_version();

    static int run_help();

    static void print_token_output(const std::string &file);
};


#endif //COMMANDS_H
