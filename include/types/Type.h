//
// Created by Wylan Shoemaker on 6/10/2025.
//

#ifndef TYPE_H
#define TYPE_H

#include <string>
#include <vector>
#include <memory>
#include "../ast/AST.h"

// Base type class
class Type : public ASTNode {
public:
    virtual ~Type() = default;
    virtual std::string toString() const = 0;
    virtual bool isAssignableFrom(const Type& other) const = 0;
};

// Basic types (int, float, bool, etc.)
class BasicType : public Type {
public:
    explicit BasicType(std::string name) : name(std::move(name)) {}
    
    std::string toString() const override { return name; }
    bool isAssignableFrom(const Type& other) const override {
        if (const auto* basic = dynamic_cast<const BasicType*>(&other)) {
            return name == basic->name;
        }
        return false;
    }

private:
    std::string name;
};

// Generic type (e.g., List<T>)
class GenericType : public Type {
public:
    GenericType(std::string baseName, std::vector<std::unique_ptr<Type>> typeParams)
        : baseName(std::move(baseName)), typeParameters(std::move(typeParams)) {}
    
    std::string toString() const override {
        std::string result = baseName + "<";
        for (size_t i = 0; i < typeParameters.size(); ++i) {
            if (i > 0) result += ", ";
            result += typeParameters[i]->toString();
        }
        result += ">";
        return result;
    }
    
    bool isAssignableFrom(const Type& other) const override {
        if (const auto* generic = dynamic_cast<const GenericType*>(&other)) {
            if (baseName != generic->baseName || typeParameters.size() != generic->typeParameters.size()) {
                return false;
            }
            for (size_t i = 0; i < typeParameters.size(); ++i) {
                if (!typeParameters[i]->isAssignableFrom(*generic->typeParameters[i])) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

private:
    std::string baseName;
    std::vector<std::unique_ptr<Type>> typeParameters;
};

// User-defined type
class UserDefinedType : public Type {
public:
    explicit UserDefinedType(std::string name) : name(std::move(name)) {}
    
    std::string toString() const override { return name; }
    bool isAssignableFrom(const Type& other) const override {
        if (const auto* user = dynamic_cast<const UserDefinedType*>(&other)) {
            return name == user->name;
        }
        return false;
    }

private:
    std::string name;
};

#endif //TYPE_H 