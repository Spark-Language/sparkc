cmake_minimum_required(VERSION 3.31)
project(sparkc)

set(CMAKE_CXX_STANDARD 20)

add_executable(sparkc
        src/main.cpp
        src/tokens/TokenType.cpp
        include/tokens/TokenType.h
        src/tokens/TokenCategory.cpp
        include/tokens/TokenCategory.h
        src/lexer/Lexer.cpp
        include/lexer/Lexer.h
        src/util/SourceContext.cpp
        include/util/SourceContext.h
        src/commands/Commands.cpp
        include/commands/Commands.h
        src/visibility/Visibility.cpp
        include/visibility/Visibility.h
        src/parser/Parser.cpp
        include/parser/Parser.h
        src/ast/AST.cpp
        include/ast/AST.h
        include/types/Statement.h
        include/types/Expression.h
        include/types/Expressions.h
        include/types/Statements.h
        include/types/Declarations.h)
