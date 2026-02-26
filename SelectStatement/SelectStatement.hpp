#ifndef SELECT_STATEMENT_HPP
#define SELECT_STATEMENT_HPP

#include "../Statement/Statement.hpp"
#include "../Condition/Condition.hpp"
#include <vector>
#include <string>

class SelectStatement : public Statement{
    public:

        //Constructors
        SelectStatement(std::vector<std::string> columns, std::string table);
        SelectStatement(std::vector<std::string> columns, std::string table, Condition *condition);

        //Execute
        virtual void execute() override;

        //Setters
        void setTable(const std::string &table);
        void setColumns(const std::vector<std::string> &columns);
        void setCondition(Condition *condition);
        
        //Getters
        std::string getTable() const;
        std::vector<std::string> getColumns() const;
        Condition *getCondition() const;

        //Destructor
        ~SelectStatement();
    private:
        std::vector<std::string> columns;
        std::string table;
        Condition *condition;
};

#endif