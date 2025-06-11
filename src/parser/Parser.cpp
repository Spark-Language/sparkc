//
// Created by Wylan Shoemaker on 6/10/2025.
//

#include "../../include/parser/Parser.h"
#include <sstream>

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens) {}

std::unique_ptr<Program> Parser::parseProgram() {
    try {
        // First pass: collect all declarations
        collectDeclarations();
        
        // Second pass: parse implementations
        return parseImplementations();
    } catch (const ParseError& e) {
        // Handle parse error
        throw;
    }
}

void Parser::collectDeclarations() {
    while (!isAtEnd()) {
        try {
            if (match({TokenType::FUNC})) {
                auto func = parseFunctionSignature();
                symbols.functions[func->name] = std::move(func);
            } else if (match({TokenType::TYPE})) {
                auto type = parseTypeDeclaration();
                symbols.types[type->name] = std::move(type);
            } else if (match({TokenType::INTER})) {
                auto interface = parseInterfaceDeclaration();
                symbols.interfaces[interface->name] = std::move(interface);
            } else if (match({TokenType::MODULE})) {
                auto module = parseModuleDeclaration();
                symbols.modules[module->name] = std::move(module);
            } else {
                advance(); // Skip unknown tokens
            }
        } catch (const ParseError& e) {
            synchronize();
        }
    }
}

std::unique_ptr<Program> Parser::parseImplementations() {
    reset(); // Reset token position
    auto program = std::make_unique<Program>();
    
    while (!isAtEnd()) {
        try {
            if (match({TokenType::FUNC})) {
                auto func = parseFunctionSignature();
                program->statements.push_back(std::move(func));
            } else if (match({TokenType::TYPE})) {
                auto type = parseTypeDeclaration();
                program->statements.push_back(std::move(type));
            } else if (match({TokenType::INTER})) {
                auto interface = parseInterfaceDeclaration();
                program->statements.push_back(std::move(interface));
            } else if (match({TokenType::MODULE})) {
                auto module = parseModuleDeclaration();
                program->statements.push_back(std::move(module));
            } else {
                advance(); // Skip unknown tokens
            }
        } catch (const ParseError& e) {
            synchronize();
        }
    }
    
    return program;
}

void Parser::synchronize() {
    while (!isAtEnd()) {
        if (previous().type == TokenType::SEMICOLON) return;
        
        switch (peek().type) {
            case TokenType::FUNC:
            case TokenType::TYPE:
            case TokenType::INTER:
            case TokenType::MODULE:
                return;
            default:
                advance();
        }
    }
}

Visibility Parser::parseVisibility() {
    if (match({TokenType::PUBLIC})) return Visibility::Public;
    if (match({TokenType::PRIVATE})) return Visibility::Private;
    if (match({TokenType::INTERNAL})) return Visibility::Internal;
    return Visibility::Private; // Default visibility
}

std::vector<std::string> Parser::parseModifiers() {
    std::vector<std::string> modifiers;
    while (match({TokenType::FINAL, TokenType::ABSTRACT, TokenType::STATIC})) {
        modifiers.push_back(previous().lexeme);
    }
    return modifiers;
}

std::unique_ptr<Type> Parser::parseType() {
    if (match({TokenType::IDENTIFIER})) {
        auto typeName = previous().lexeme;
        
        // Check if it's a generic type
        if (match({TokenType::LESS})) {
            auto typeParams = parseTypeParameters();
            consume(TokenType::GREATER, "Expected '>' after type parameters");
            return std::make_unique<GenericType>(typeName, std::move(typeParams));
        }
        
        // Check if it's a user-defined type
        if (symbols.types.find(typeName) != symbols.types.end()) {
            return std::make_unique<UserDefinedType>(typeName);
        }
        
        // Basic type
        return std::make_unique<BasicType>(typeName);
    }
    
    // Built-in types
    if (match({TokenType::INT32})) return std::make_unique<BasicType>("int32");
    if (match({TokenType::FLOAT32})) return std::make_unique<BasicType>("float32");
    if (match({TokenType::BOOLEAN})) return std::make_unique<BasicType>("bool");
    if (match({TokenType::STRING})) return std::make_unique<BasicType>("string");
    
    throw ParseError("Expected type");
}

std::vector<std::unique_ptr<Type>> Parser::parseTypeParameters() {
    std::vector<std::unique_ptr<Type>> params;
    do {
        params.push_back(parseType());
    } while (match({TokenType::COMMA}));
    return params;
}

std::unique_ptr<FunctionDeclaration> Parser::parseFunctionSignature() {
    // Parse visibility
    auto visibility = parseVisibility();
    bool isPublic = visibility == Visibility::Public;
    bool isInternal = visibility == Visibility::Internal;
    
    // Parse modifiers
    auto modifiers = parseModifiers();
    
    // Parse function name
    auto name = consume(TokenType::IDENTIFIER, "Expected function name").lexeme;
    
    // Parse type parameters if any
    std::vector<std::string> typeParams;
    if (match({TokenType::LESS})) {
        do {
            typeParams.push_back(consume(TokenType::IDENTIFIER, "Expected type parameter name").lexeme);
        } while (match({TokenType::COMMA}));
        consume(TokenType::GREATER, "Expected '>' after type parameters");
    }
    
    // Parse parameters
    std::vector<std::string> params;
    std::vector<std::unique_ptr<Type>> paramTypes;
    
    if (match({TokenType::LEFT_PAREN})) {
        if (!check(TokenType::RIGHT_PAREN)) {
            do {
                // Parameter name
                params.push_back(consume(TokenType::IDENTIFIER, "Expected parameter name").lexeme);
                
                // Parameter type
                consume(TokenType::COLON, "Expected ':' after parameter name");
                paramTypes.push_back(parseType());
            } while (match({TokenType::COMMA}));
        }
        consume(TokenType::RIGHT_PAREN, "Expected ')' after parameters");
    }
    
    // Parse return type
    std::unique_ptr<Type> returnType;
    if (match({TokenType::ARROW})) {
        returnType = parseType();
    } else {
        returnType = std::make_unique<BasicType>("void");
    }
    
    return std::make_unique<FunctionDeclaration>(
        name,
        std::move(params),
        std::move(paramTypes),
        std::move(returnType),
        isPublic,
        isInternal
    );
}

std::unique_ptr<TypeDeclaration> Parser::parseTypeDeclaration() {
    // Parse visibility
    auto visibility = parseVisibility();
    bool isPublic = visibility == Visibility::Public;
    bool isInternal = visibility == Visibility::Internal;
    
    // Parse modifiers
    auto modifiers = parseModifiers();
    
    // Parse type name
    auto name = consume(TokenType::IDENTIFIER, "Expected type name").lexeme;
    
    // Parse type parameters if any
    std::vector<std::string> typeParams;
    if (match({TokenType::LESS})) {
        do {
            typeParams.push_back(consume(TokenType::IDENTIFIER, "Expected type parameter name").lexeme);
        } while (match({TokenType::COMMA}));
        consume(TokenType::GREATER, "Expected '>' after type parameters");
    }
    
    // Parse implemented interfaces
    std::vector<std::string> implements;
    if (match({TokenType::IMPL})) {
        do {
            implements.push_back(consume(TokenType::IDENTIFIER, "Expected interface name").lexeme);
        } while (match({TokenType::COMMA}));
    }
    
    // Parse type body
    std::vector<std::unique_ptr<FunctionDeclaration>> methods;
    if (match({TokenType::LEFT_BRACE})) {
        while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
            if (match({TokenType::FUNC})) {
                methods.push_back(parseFunctionSignature());
            } else {
                throw ParseError("Expected function declaration in type body");
            }
        }
        consume(TokenType::RIGHT_BRACE, "Expected '}' after type body");
    }
    
    return std::make_unique<TypeDeclaration>(
        name,
        std::move(typeParams),
        std::move(methods),
        std::move(implements),
        isPublic,
        isInternal
    );
}

std::unique_ptr<InterfaceDeclaration> Parser::parseInterfaceDeclaration() {
    // Parse interface name
    auto name = consume(TokenType::IDENTIFIER, "Expected interface name").lexeme;
    
    // Parse extended interfaces
    std::vector<std::string> extends;
    if (match({TokenType::INTER})) {
        do {
            extends.push_back(consume(TokenType::IDENTIFIER, "Expected interface name").lexeme);
        } while (match({TokenType::COMMA}));
    }
    
    // Parse interface body
    std::vector<std::unique_ptr<FunctionDeclaration>> methods;
    consume(TokenType::LEFT_BRACE, "Expected '{' after interface name");
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        if (match({TokenType::FUNC})) {
            methods.push_back(parseFunctionSignature());
        } else {
            throw ParseError("Expected function declaration in interface body");
        }
    }
    consume(TokenType::RIGHT_BRACE, "Expected '}' after interface body");
    
    return std::make_unique<InterfaceDeclaration>(
        name,
        std::move(methods),
        std::move(extends)
    );
}

std::unique_ptr<ModuleDeclaration> Parser::parseModuleDeclaration() {
    // Parse module name
    auto name = consume(TokenType::IDENTIFIER, "Expected module name").lexeme;
    
    // Parse imports
    std::vector<std::string> imports;
    while (match({TokenType::IMPORT})) {
        imports.push_back(consume(TokenType::IDENTIFIER, "Expected module name").lexeme);
        consume(TokenType::SEMICOLON, "Expected ';' after import");
    }
    
    // Parse module body
    std::vector<std::unique_ptr<ASTNode>> declarations;
    consume(TokenType::LEFT_BRACE, "Expected '{' after module name");
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        if (match({TokenType::FUNC})) {
            declarations.push_back(parseFunctionSignature());
        } else if (match({TokenType::TYPE})) {
            declarations.push_back(parseTypeDeclaration());
        } else if (match({TokenType::INTER})) {
            declarations.push_back(parseInterfaceDeclaration());
        } else {
            throw ParseError("Expected declaration in module body");
        }
    }
    consume(TokenType::RIGHT_BRACE, "Expected '}' after module body");
    
    return std::make_unique<ModuleDeclaration>(
        name,
        std::move(declarations),
        std::move(imports)
    );
}

// Helper methods
bool Parser::isAtEnd() const {
    return peek().type == TokenType::END_OF_FILE;
}

const Token& Parser::peek() const {
    return tokens[current];
}

const Token& Parser::previous() const {
    return tokens[current - 1];
}

bool Parser::check(TokenType type) const {
    if (isAtEnd()) return false;
    return peek().type == type;
}

bool Parser::match(std::initializer_list<TokenType> types) {
    for (TokenType type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

const Token& Parser::consume(TokenType type, const std::string& errMsg) {
    if (check(type)) return advance();
    
    std::stringstream ss;
    ss << errMsg << " at '" << peek().lexeme << "'";
    throw ParseError(ss.str());
}

const Token& Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

void Parser::reset() {
    current = 0;
}
