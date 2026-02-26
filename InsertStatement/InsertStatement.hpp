#ifndef INSERT_STATEMENT_HPP
#define INSERT_STATEMENT_HPP

#include "../Statement/Statement.hpp"
#include <vector>
#include <string>

class InsertStatement : public Statement{
    public:
        //Constructors
        InsertStatement(std::string table, std::vector<std::string> values);
        InsertStatement(std::string table, std::vector<std::string> columns,
             std::vector<std::string> values);

        //Execute
        virtual void execute() override;

        //Setters
        void setTable(const std::string &table);
        void setValues(const std::vector<std::string> &values);
        void setColumns(const std::vector<std::string> &columns);

        //Getters
        std::string getTable() const;
        std::vector<std::string> getValues() const;
        std::vector<std::string> getColumns() const;

        //Destructor
        ~InsertStatement();
    private:
        std::string table;
        std::vector<std::string> values;
        std::vector<std::string> columns;
};

#endif