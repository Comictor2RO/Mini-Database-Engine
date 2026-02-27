cmake_minimum_required(VERSION 4.1)
project(Mini_Database_Engine)

set(CMAKE_CXX_STANDARD 14)

include_directories(Condition)
include_directories(DeleteStatement)
include_directories(InsertStatement)
include_directories(Lexer)
include_directories(SelectStatement)
include_directories(Statement)

add_executable(Mini_Database_Engine
        Condition/Condition.hpp
        DeleteStatement/DeleteStatement.cpp
        DeleteStatement/DeleteStatement.hpp
        InsertStatement/InsertStatement.cpp
        InsertStatement/InsertStatement.hpp
        Lexer/Lexer.cpp
        Lexer/Lexer.hpp
        SelectStatement/SelectStatement.cpp
        SelectStatement/SelectStatement.hpp
        Statement/Statement.hpp
        main.cpp
        Parser/Parser.cpp
        Parser/Parser.hpp)
