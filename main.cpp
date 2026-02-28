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
    PageManager pm("mydb.dat");

    // Inserează rows
    pm.insertRow("Ion|25|ion@email.com");
    pm.insertRow("Ana|30|ana@email.com");
    pm.insertRow("Maria|22|maria@email.com");

    // Citește toate rows
    auto rows = pm.getAllRows();
    for (const auto& row : rows)
        std::cout << row << '\n';

    return 0;
}