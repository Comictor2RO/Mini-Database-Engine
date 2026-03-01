#include "Table/Table.hpp"

int main()
{
    // 1. Definesti schema
    std::vector<Columns> schema = {
        {"id",   "INT"},
        {"name", "STRING"},
        {"age",  "INT"}
    };

    // 2. Creezi tabela
    Table table("users", schema);

    // 3. INSERT
    Row r1; r1.values = {"1", "Ion",  "25"};
    Row r2; r2.values = {"2", "Ana",  "30"};
    Row r3; r3.values = {"3", "Popa", "40"};
    table.insertRow(r1);
    table.insertRow(r2);
    table.insertRow(r3);
    std::cout << "INSERT OK\n";

    // 4. SELECT * (fara conditie)
    std::vector<Row> rows = table.selectRow(nullptr);
    std::cout << "SELECT * -> " << rows.size() << " rows:\n";
    for (const auto &row : rows)
    {
        for (const auto &val : row.values)
            std::cout << val << " | ";
        std::cout << "\n";
    }

    // 5. SELECT WHERE id = 2
    Condition cond;
    cond.column = "id";
    cond.op     = "=";
    cond.value  = "2";
    std::vector<Row> filtered = table.selectRow(&cond);
    std::cout << "SELECT WHERE id=2 -> " << filtered.size() << " rows:\n";
    for (const auto &row : filtered)
    {
        for (const auto &val : row.values)
            std::cout << val << " | ";
        std::cout << "\n";
    }

    // 6. DELETE WHERE id = 2
    table.deleteRow(&cond);
    std::cout << "DELETE WHERE id=2 OK\n";

    // 7. SELECT * dupa delete
    rows = table.selectRow(nullptr);
    std::cout << "SELECT * dupa delete -> " << rows.size() << " rows:\n";
    for (const auto &row : rows)
    {
        for (const auto &val : row.values)
            std::cout << val << " | ";
        std::cout << "\n";
    }

    return 0;
}