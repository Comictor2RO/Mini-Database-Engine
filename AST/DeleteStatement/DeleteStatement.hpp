#ifndef DELETE_STATEMENT_HPP
#define DELETE_STATEMENT_HPP

#include "../Statement/Statement.hpp"
#include "../Condition/Condition.hpp"
#include <string>

class DeleteStatement : public Statement{
    public:

        //Constructors
        DeleteStatement(std::string table);
        DeleteStatement(std::string table, Condition *condition);

        //Execute
        void execute() override;

        //Setters
        void setTable(const std::string &table);
        void setCondition(Condition *condition);

        //Getters
        std::string getTable() const;
        Condition *getCondition() const;

        //Destructor
        ~DeleteStatement() override;
    private:
        std::string table;
        Condition *condition;
};

#endif