#include "Table.hpp"

static bool evaluateCondition(const Condition *cond, const Row &row, const std::vector<Columns> &scheme)
{
    //Finds the column index in scheme
    int colIndex = -1;
    for (int i = 0; i < (int)scheme.size(); i++)
    {
        if (scheme[i].name == cond->column)
        {
            colIndex = i;
            break;
        }
    }
    if (colIndex == -1)
        return false;

    const std::string &rowValue = row.values[colIndex];

    if (cond->op == "=")  return rowValue == cond->value;
    if (cond->op == "!=") return rowValue != cond->value;
    if (cond->op == ">")  return std::stoi(rowValue) > std::stoi(cond->value);
    if (cond->op == "<")  return std::stoi(rowValue) < std::stoi(cond->value);
    if (cond->op == ">=") return std::stoi(rowValue) >= std::stoi(cond->value);
    if (cond->op == "<=") return std::stoi(rowValue) <= std::stoi(cond->value);
    return false;
}

Table::Table(const std::string &name, const std::vector<Columns> &schema)
    : name(name), scheme(schema), pageManager(name + ".db")
{}

void Table::insertRow(const Row &row)
{
    std::string serialized;
    for (int i = 0; i < row.values.size(); i++)
    {
        serialized += row.values[i];
        if (i + 1 < row.values.size())
            serialized += "|";
    }
    pageManager.insertRow(serialized);
}

std::vector<Row> Table::selectRow(Condition *cond)
{
    std::vector<std::string> rawRows = pageManager.getAllRows();
    std::vector<Row> result;
    int colCount = scheme.size();

    for (const auto &raw : rawRows)
    {
        Row row;
        row.values = split(raw, '|'); // split "1|Ion|25" -> {"1", "Ion", "25"}

        if (cond == nullptr || evaluateCondition(cond, row, scheme))
            result.push_back(row);
    }

    return result;
}

void Table::deleteRow(Condition *cond)
{
    //Reads all the existent rows
    std::vector<Row> allRows = selectRow(nullptr);

    //Keeps only the rows which does not match the condition
    std::vector<Row> toKeep;
    for (const auto &row : allRows)
    {
        if (cond == nullptr || !evaluateCondition(cond, row, scheme))
            toKeep.push_back(row);
    }

    //Delets all the file
    pageManager.clearAll();

    //Rewrites it
    for (const auto &row : toKeep)
        insertRow(row);
}