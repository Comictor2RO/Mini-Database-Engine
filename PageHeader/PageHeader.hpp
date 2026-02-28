#ifndef PAGEHEADER_HPP
#define PAGEHEADER_HPP

struct PageHeader {
    int pageId;
    int freeSpace;
    int rowNumber;
};

static_assert(sizeof(PageHeader) == 12);

#endif
