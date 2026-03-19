#ifndef COLUMNS_HPP
#define COLUMNS_HPP

#include <string>

struct Columns {
    std::string name;
    std::string type;

    std::string getName() const {
        return name;
    }
};


#endif
