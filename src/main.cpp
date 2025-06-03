//
// Created by Wylan Shoemaker on 5/29/25.
//

#include "../include/commands/Commands.h"
#include <vector>
#include <string>

int main(int argc, char** argv) {
    std::vector<std::string> args(argv + 1, argv + argc);
    return Commands::run(args);
}