//
// Created by Wylan Shoemaker on 6/10/2025.
//

#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#include <memory>
#include <vector>

#include "../ast/AST.h"

struct Program : ASTNode {
    std::vector<std::unique_ptr<ASTNode>> statements;
};

struct FunctionDeclaration : ASTNode {
    std::string name;
    std::vector<std::string> parameters;
    std::vector<std::unique_ptr<ASTNode>> body;
    FunctionDeclaration(std::string name, std::vector<std::string> parameters) : name(std::move(name)), parameters(std::move(parameters)) {}
};

#endif //DECLARATIONS_H
