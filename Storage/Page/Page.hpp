#ifndef PAGE_HPP
#define PAGE_HPP

#include "../PageHeader/PageHeader.hpp"
#include <string>
#include <cstring>
#include <vector>

#define PAGE_SIZE 4096

class Page {
    public:
        //Constructor
        Page(int pageId);

        //Methods
        bool hasSpace(int rowSize) const;
        bool addRow(const std::string &row);

        //Getters
        std::vector<std::string> getRows() const;
        int getPageId() const;
        int getFreeSpace() const;
        char *getBuffer();
        const char *getBuffer() const;

        ~Page();
    private:
        char data[PAGE_SIZE];
};


#endif