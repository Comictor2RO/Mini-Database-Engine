#include <iostream>
#include "SelectStatement/SelectStatement.hpp"
#include "InsertStatement/InsertStatement.hpp"
#include "DeleteStatement/DeleteStatement.hpp"
#include "Lexer/Lexer.hpp"

int main()
{
    Lexer lexer("select * From users WHERE x = 5");
    std::vector<Token> tokens = lexer.tokenize();

    for(const Token &t: tokens)
    {
        std::cout << t.value << " ";
    }
    return 0;
}