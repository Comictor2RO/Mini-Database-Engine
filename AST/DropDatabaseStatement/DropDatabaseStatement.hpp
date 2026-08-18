#ifndef DROP_DATABASE_STATEMENT_HPP
#define DROP_DATABASE_STATEMENT_HPP

#include "../Statement/Statement.hpp"
#include <string>

class DropDatabaseStatement : public Statement{
public:
    explicit DropDatabaseStatement(std::string name);

    void execute() override;

    const std::string& getName() const;

    ~DropDatabaseStatement() override;
private:
    std::string name;
};


#endif
