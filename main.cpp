#include <iostream>
#include "SelectStatement/SelectStatement.hpp"
#include "InsertStatement/InsertStatement.hpp"
#include "DeleteStatement/DeleteStatement.hpp"
#include "Lexer/Lexer.hpp"
#include "Parser/Parser.hpp"

int main()
{
    Lexer lexer("Select name, age from users where age < 18");
    std::vector<Token> tokens = lexer.tokenize();

    Parser parser(tokens);
    Statement *statement = parser.parse();

    SelectStatement *select_statement = dynamic_cast<SelectStatement *>(statement);
    if (select_statement)
    {
        std::cout << "Table: " << select_statement->getTable() << '\n';
        for (const auto &token : select_statement->getColumns())
        {
            std::cout << "Column: " << token << '\n';
        }
        if (select_statement->getCondition())
        {
            std::cout << "Condition: " << select_statement->getCondition()->column
                      << " " << select_statement->getCondition()->op
                      << " " << select_statement->getCondition()->value << '\n';
        }

    }
    else
    {
        std::cout << "Error: Invalid command.";
    }

    delete statement;
    return 0;
}
