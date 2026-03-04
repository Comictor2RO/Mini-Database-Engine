#include <iostream>
#include "Frontend/Lexer/Lexer.hpp"
#include "Frontend/Parser/Parser.hpp"
#include "Engine/Engine.hpp"
#include "Catalog/Catalog.hpp"

void runQuery(const std::string &sql, Engine &engine)
{
    std::cout << "\n>> " << sql << "\n";
    Lexer lexer(sql);
    std::vector<Token> tokens = lexer.tokenize();
    Parser parser(tokens);
    Statement *stmt = parser.parse();
    if (stmt)
    {
        engine.execute(stmt);
        delete stmt;
    }
}

int main()
{
    Catalog catalog;
    Engine engine(catalog);

    // Cream tabela
    runQuery("CREATE TABLE users (id INT, name VARCHAR, age INT)", engine);

    // Inseram randuri
    runQuery("INSERT INTO users VALUES (1, Ion, 25)", engine);
    runQuery("INSERT INTO users VALUES (2, Maria, 30)", engine);
    runQuery("INSERT INTO users VALUES (3, Andrei, 22)", engine);
    runQuery("INSERT INTO users VALUES (4, Elena, 28)", engine);

    // SELECT fara conditie - full scan
    std::cout << "\n--- SELECT * FROM users ---\n";
    runQuery("SELECT * FROM users", engine);

    // SELECT cu WHERE pe prima coloana INT = foloseste B+ Tree index
    std::cout << "\n--- SELECT cu index (WHERE id = 2) ---\n";
    runQuery("SELECT * FROM users WHERE id = 2", engine);

    // SELECT cu WHERE pe alta coloana = full scan
    std::cout << "\n--- SELECT full scan (WHERE age = 22) ---\n";
    runQuery("SELECT * FROM users WHERE age = 22", engine);

    // DELETE cu conditie
    std::cout << "\n--- DELETE WHERE id = 1 ---\n";
    runQuery("DELETE FROM users WHERE id = 1", engine);

    // Verificam dupa delete
    std::cout << "\n--- SELECT * dupa delete ---\n";
    runQuery("SELECT * FROM users", engine);

    return 0;
}
