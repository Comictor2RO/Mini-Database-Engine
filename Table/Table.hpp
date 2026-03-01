#ifndef TABLE_HPP
#define TABLE_HPP

#include "Condition.hpp"
#include "../Storage/PageManager/PageManager.hpp"
#include "../AST/Columns/Columns.hpp"
#include "../AST/Row/Row.hpp"
#include "../StringUtils/StringUtils.hpp"

class Table {
    public:
        Table(const std::string &name, const std::vector<Columns> &scheme);

        void insertRow(const Row &row);
        std::vector<Row> selectRow(Condition *cond);
        void deleteRow(Condition *cond);

    private:
        std::string name;
        std::vector<Columns> scheme;
        PageManager pageManager;
};

static bool evaluateCondition(const Condition *cond, const Row &row, const std::vector<Columns> &schema);

#endif