#include "PageManager.hpp"

PageManager::PageManager(std::string filename)
{
    this->filename = filename;
    //Opens a binary file with the permission to read and to write
    file.open(filename, std::ios::in | std::ios::out | std::ios::binary);

    if (!file.is_open())
    {
        file.open(filename, std::ios::out | std::ios::binary);
        file.close();
        file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
        numberOfPages = 0;
    }
    else
    {
        std::cout << "File already exists" << '\n';

        //seekg - moves the reading cursor in a chosen position
        file.seekg(0, std::ios::end); //0 bytes before the end
        //tellg - returns a streampos and tells you where the reading cursor is
        numberOfPages = file.tellg() / PAGE_SIZE;
    }
}

bool PageManager::insertRow(const std:: string &row)
{
    if (numberOfPages > 0) //If there are pages
    {
        Page lastPage = readPage(numberOfPages - 1);
        if (lastPage.hasSpace(row.length() + 1)) //Checks if the last page has space
        {
            lastPage.addRow(row); //Adds the row
            writePage(numberOfPages - 1, lastPage); //Saves it
            return true;
        }
    }
    Page newPage(numberOfPages);
    if (!newPage.addRow(row))
        return false;
    writePage(numberOfPages, newPage);
    numberOfPages++;
    return true;
}

Page PageManager::readPage(int pageNumber)
{
    Page page(pageNumber);
    file.seekg(pageNumber * PAGE_SIZE); //Changes the current position where to read
    file.read(page.getBuffer(), PAGE_SIZE);
    return page;
}

void PageManager::writePage(int pageId, const Page &page)
{
    int position = pageId * PAGE_SIZE;

    file.seekp(position); //Changes the current position where to write
    file.write(page.getBuffer(), PAGE_SIZE);
    file.flush();
}

std::vector<std::string> PageManager::getAllRows()
{
    std::vector<std::string> rows;

    for (int i = 0; i < numberOfPages; i++) {
        Page page = readPage(i);
        std::vector<std::string> pageRows = page.getRows();
        rows.insert(rows.end(), pageRows.begin(), pageRows.end());
    }

    return rows;
}

PageManager::~PageManager()
{
    if (file.is_open())
        file.close();
}
