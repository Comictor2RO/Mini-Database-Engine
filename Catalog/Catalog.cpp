#include "Catalog.hpp"

bool Catalog::tableExists(const std::string &name) const
{
    return columns.find(name) != columns.end();
}

void Catalog::createTable(const std::string &name, const std::vector<Columns> &columns)
{
    if (tableExists(name))
        return;
    this->columns[name] = columns;
}

std::vector<Columns> Catalog::getColumns(const std::string &name) const
{
    if (!tableExists(name))
        return {};
    return columns.at(name);
}
