#include "DropDatabaseStatement.hpp"

DropDatabaseStatement::DropDatabaseStatement(std::string name)
    : name(std::move(name))
{}

void DropDatabaseStatement::execute()
{}

const std::string& DropDatabaseStatement::getName() const
{
    return name;
}

DropDatabaseStatement::~DropDatabaseStatement()
{}
