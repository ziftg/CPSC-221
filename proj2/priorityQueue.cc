#include "priorityQueue.h"

PriorityQueue::PriorityQueue() {}

PriorityQueue::~PriorityQueue() {
    heap.clear();
}

void PriorityQueue::swapDown(vector<TreeNode*>& heap, int i, int size) {
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;
    int min = i;
    // find who holds largest element of i and its two children
    if (leftChild < size && heap[leftChild]->freq < heap[min]->freq)
        min = leftChild;
    if (rightChild < size && heap[rightChild]->freq < heap[min]->freq)
        min = rightChild;
    // if a child holds largest element, swap i's element to that child
    // and recurse.
    if (min != i) {
        swap(heap[i], heap[min]);
        swapDown(heap, min, size);
    }
}

void PriorityQueue::heapify(vector<TreeNode*>& heap, int size) {
    for (int i = (size - 2) / 2; i >= 0; i--)
        swapDown(heap, i, size);
}

bool PriorityQueue::isEmpty() {
    return heap.empty();
}

int PriorityQueue::size(){
    return (int)heap.size();
}

TreeNode* PriorityQueue::top(){
    if (!heap.empty()) {
        heapify(heap, (int)heap.size());
        return heap.front();
    }
    return NULL;
}

void PriorityQueue::push(TreeNode* node){
    heap.push_back(node);
    heapify(heap, (int)heap.size());
}

void PriorityQueue::pop(){
    if (!heap.empty()) {
        heap.erase(heap.begin());
        heapify(heap, (int)heap.size());
    }
}
