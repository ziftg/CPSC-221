#ifndef priorityQueue_h
#define priorityQueue_h

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

#endif /* priorityQueue_h */

struct TreeNode {
    char ch;
    int freq;
    TreeNode *left, *right;
    
    TreeNode(char ch, int freq) {
        left = NULL;
        right = NULL;
        this->ch = ch;
        this->freq = freq;
    }
};

class PriorityQueue{
    
public:
    PriorityQueue();
    ~PriorityQueue();
    
    void swapDown(vector<TreeNode*>&, int, int);
    void heapify(vector<TreeNode*>&, int);
    bool isEmpty();
    int size();
    TreeNode* top();
    void push(TreeNode*);
    void pop();
    
private:
    vector<TreeNode*> heap;
};
