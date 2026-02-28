#include <iostream>
#include "AST/SelectStatement/SelectStatement.hpp"
#include "AST/InsertStatement/InsertStatement.hpp"
#include "AST/DeleteStatement/DeleteStatement.hpp"
#include "Frontend/Lexer/Lexer.hpp"
#include "Storage/Page/Page.hpp"
#include "Frontend/Parser/Parser.hpp"
#include "Storage/PageManager/PageManager.hpp"

int main()
{
    Lexer lexer("CREATE TABLE users (id INT, name STRING, age INT)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    auto stmt = (CreateStatement*)parser.parse();

    for (auto& col : stmt->getColumns())
        std::cout << col.name << " " << col.type << '\n';
}