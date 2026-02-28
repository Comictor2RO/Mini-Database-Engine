#include <iostream>
#include "AST/SelectStatement/SelectStatement.hpp"
#include "AST/InsertStatement/InsertStatement.hpp"
#include "AST/DeleteStatement/DeleteStatement.hpp"
#include "Frontend/Lexer/Lexer.hpp"
#include "Storage/Page/Page.hpp"
#include "Frontend/Parser/Parser.hpp"

int main()
{
    Page page(0);

    std::cout << "PageId: " << page.getPageId() << '\n';
    std::cout << "FreeSpace initial: " << page.getFreeSpace() << '\n';

    page.addRow("Ana|25|ana@email.com");
    page.addRow("Ion|30|ion@email.com");
    page.addRow("Maria|22|maria@email.com");

    std::cout << "FreeSpace dupa 3 randuri: " << page.getFreeSpace() << '\n';

    std::vector<std::string> rows = page.getRows();
    std::cout << "Numar randuri: " << rows.size() << '\n';
    for (const auto& row : rows)
        std::cout << "Row: " << row << '\n';

    return 0;
}