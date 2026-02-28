#ifndef CATALOG_HPP
#define CATALOG_HPP

#include <map>
#include <string>
#include <vector>
#include "../AST/Columns/Columns.hpp"

class Catalog {
    public:
        //Methods
        void createTable(const std::string &name, const std::vector<Columns> &columns);
        bool tableExists(const std::string &name) const;

        //Getter
        std::vector<Columns> getColumns(const std::string &name) const;

    private:
        std::map<std::string, std::vector<Columns>> columns;
};


#endif