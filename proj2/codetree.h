#ifndef codetree_h
#define codetree_h

#include "priorityQueue.h"

#endif /* codetree_h */

class CodeTree{
    
public:
    CodeTree(int*);
    ~CodeTree();
    
    void printChar(int);
    void printTreeHelper(TreeNode*, string);
    void printTree();
    void printCodeHelper(TreeNode*, string);
    void printCode();
    
private:
    PriorityQueue pHeap;
};
