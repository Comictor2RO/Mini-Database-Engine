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
