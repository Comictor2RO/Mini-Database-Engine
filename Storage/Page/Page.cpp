#include "Page.hpp"

Page::Page(int pageId)
{
    PageHeader *header = (PageHeader *)data;
    header->pageId = pageId;
    header->freeSpace = PAGE_SIZE - sizeof(PageHeader);
    header->rowNumber = 0;
    memset(data + sizeof(PageHeader), 0, PAGE_SIZE - (sizeof(PageHeader)));

}

std::vector<std::string> Page::getRows() const
{
    PageHeader *header = (PageHeader *)data;
    std::vector<std::string> row;
    std::string current;
    int data_start = sizeof(PageHeader) ; //Jumps over the header
    int bytes_used = PAGE_SIZE - header->freeSpace - sizeof(PageHeader); //How many bytes where used

    for (int i = data_start; i < data_start + bytes_used; i++) //Goes until the bytes written in the file
    {
        if (data[i] == '\0') //Exits
            break;
        if (data[i] == '\n') //When it arrives on \n saves the data in row and clears the data
        {
            if (!current.empty())
            {
                row.push_back(current);
                current.clear();
            }
        }
        else
            current += data[i]; //Builds the row
    }

    return row;
}

int Page::getPageId() const
{
    PageHeader *header = (PageHeader *)data;
    return header->pageId;
}

int Page::getFreeSpace() const
{
    PageHeader *header = (PageHeader *)data;
    return header->freeSpace;
}

char *Page::getBuffer()
{
    return data;
}

const char *Page::getBuffer() const
{
    return data;
}

bool Page::hasSpace(int rowSize) const
{
    PageHeader *header = (PageHeader *)data;
    return header->freeSpace >= rowSize;
}

bool Page::addRow(const std::string &row)
{
    PageHeader *header = (PageHeader *)data;

    if (!hasSpace(row.length() + 1)) //If there is no space returns false
        return false;

    int offset = PAGE_SIZE - header->freeSpace;

    memcpy(data + offset, row.c_str(), row.length()); //Saves the row
    data[offset + row.length()] = '\n'; //Adds the newline at the end

    header->freeSpace -= row.length() + 1; //Updates the free space available
    header->rowNumber++; //Updates the number of rows

    return true;
}

Page::~Page()
{}
