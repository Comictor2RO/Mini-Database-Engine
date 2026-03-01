#include "../Parser/Parser.hpp"
#include "Engine/Engine.hpp"
#include "Catalog/Catalog.hpp"

int main()
{
    Catalog catalog;
    Engine engine(catalog);

    std::vector<std::string> queries = {
        "CREATE TABLE users (id INT, name STRING, age INT)",
        "INSERT INTO users VALUES (1, Ion, 25)",
        "INSERT INTO users VALUES (2, Ana, 30)",
        "INSERT INTO users VALUES (3, Popa, 40)",
        "SELECT * FROM users",
        "SELECT * FROM users WHERE id = 2",
        "DELETE FROM users WHERE id = 2",
        "SELECT * FROM users"
    };

    for (const auto &query : queries)
    {
        std::cout << "> " << query << "\n";
        Lexer lexer(query);
        Parser parser(lexer.tokenize());
        Statement *stmt = parser.parse();
        engine.execute(stmt);
        delete stmt;
        std::cout << "\n";
    }

    return 0;
}