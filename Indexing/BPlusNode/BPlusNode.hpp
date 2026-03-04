#ifndef BPLUSNODE_HPP
#define BPLUSNODE_HPP
#include <vector>

#include "../IndexRecord/IndexRecord.hpp"

struct BPlusNode {
    std::vector<int> keys; //Keys inside the node
    std::vector<BPlusNode*> children; //Pointers towards the children(if is internal node)
    BPlusNode *parent;
    std::vector<IndexRecord> records; //Data
    BPlusNode *next = nullptr; //Pointer towards the next leaf
    bool isLeaf = false;
};

#endif
