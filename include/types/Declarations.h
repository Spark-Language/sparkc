//
// Created by Wylan Shoemaker on 6/10/2025.
//

#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#include <memory>
#include <vector>
#include <string>
#include "../ast/AST.h"
#include "Type.h"

// Forward declarations
class Statement;
class Expression;

struct Program : ASTNode {
    std::vector<std::unique_ptr<ASTNode>> statements;
};

struct FunctionDeclaration : ASTNode {
    std::string name;
    std::vector<std::string> parameters;
    std::vector<std::unique_ptr<Type>> parameterTypes;
    std::unique_ptr<Type> returnType;
    std::vector<std::unique_ptr<Statement>> body;
    bool isPublic;
    bool isInternal;
    
    FunctionDeclaration(std::string name, 
                       std::vector<std::string> parameters,
                       std::vector<std::unique_ptr<Type>> paramTypes,
                       std::unique_ptr<Type> returnType,
                       bool isPublic = false,
                       bool isInternal = false)
        : name(std::move(name))
        , parameters(std::move(parameters))
        , parameterTypes(std::move(paramTypes))
        , returnType(std::move(returnType))
        , isPublic(isPublic)
        , isInternal(isInternal) {}
};

struct InterfaceDeclaration : ASTNode {
    std::string name;
    std::vector<std::unique_ptr<FunctionDeclaration>> methods;
    std::vector<std::string> extends;  // Interfaces this interface extends
    
    InterfaceDeclaration(std::string name,
                        std::vector<std::unique_ptr<FunctionDeclaration>> methods,
                        std::vector<std::string> extends = {})
        : name(std::move(name))
        , methods(std::move(methods))
        , extends(std::move(extends)) {}
};

struct ModuleDeclaration : ASTNode {
    std::string name;
    std::vector<std::unique_ptr<ASTNode>> declarations;
    std::vector<std::string> imports;
    
    ModuleDeclaration(std::string name,
                     std::vector<std::unique_ptr<ASTNode>> declarations,
                     std::vector<std::string> imports = {})
        : name(std::move(name))
        , declarations(std::move(declarations))
        , imports(std::move(imports)) {}
};

struct TypeDeclaration : ASTNode {
    std::string name;
    std::vector<std::string> typeParameters;
    std::vector<std::unique_ptr<FunctionDeclaration>> methods;
    std::vector<std::string> implements;  // Interfaces this type implements
    bool isPublic;
    bool isInternal;
    
    TypeDeclaration(std::string name,
                   std::vector<std::string> typeParams = {},
                   std::vector<std::unique_ptr<FunctionDeclaration>> methods = {},
                   std::vector<std::string> implements = {},
                   bool isPublic = false,
                   bool isInternal = false)
        : name(std::move(name))
        , typeParameters(std::move(typeParams))
        , methods(std::move(methods))
        , implements(std::move(implements))
        , isPublic(isPublic)
        , isInternal(isInternal) {}
};

#endif //DECLARATIONS_H
