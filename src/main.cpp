//
// Created by wylan on 6/2/2025.
//

#include "../include/commands/Commands.h"
#include <vector>
#include <string>

int main(int argc, char** argv) {
    std::vector<std::string> args(argv + 1, argv + argc);
    return Commands::run(args);
}