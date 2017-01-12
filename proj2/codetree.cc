#include "codetree.h"

CodeTree::CodeTree(int* freq) {
    for (int i = 0; i < 256; i++){
        if (freq[i] != 0){
            TreeNode* newNode = new TreeNode((char)i, freq[i]);
            pHeap.push(newNode);
        }
    }
        
    while (pHeap.size() != 1) {
        TreeNode* tempLeft = pHeap.top();
        pHeap.pop();
        
        TreeNode* tempRight = pHeap.top();
        pHeap.pop();
        
        TreeNode* tempNode = new TreeNode('\0', tempLeft->freq + tempRight->freq);
        tempNode->left = tempLeft;
        tempNode->right = tempRight;
        pHeap.push(tempNode);
    }
}

CodeTree::~CodeTree() {
    while (!pHeap.isEmpty())
        pHeap.pop();
}

void CodeTree::printChar(int ch) {
    if( ch < 16 ) {
        cout << "x0" << hex << ch;
    } else if( ch < 32 || ch > 126 ) {
        cout << "x" << hex << ch;
    } else {
        cout << "\"" << (char)ch << "\"";
    }
}

void CodeTree::printTreeHelper(TreeNode* r, string pre) {
    if( r == NULL ) return;
    if( r->right == NULL ) { // implies r->left == NULL
        printChar(r->ch);
        cout << endl;
    } else {
        cout << "." << endl;
        cout << pre << "|`1-";
        printTreeHelper(r->right, pre + "|   ");
        cout << pre + "|   " << endl;
        cout << pre << "`-0-";
        printTreeHelper(r->left, pre + "    ");
    }
}

void CodeTree::printTree() {
    printTreeHelper(pHeap.top(), "");
}

void CodeTree::printCodeHelper(TreeNode* r, string path){
    if (r == NULL) return;
    if (r->ch != '\0') {
        //if (r->right == NULL){
        printChar(r->ch);
        cout << ":" << path << endl;
    }
    else {
        printCodeHelper(r->left, path + "0");
        printCodeHelper(r->right, path + "1");
    }
}

void CodeTree::printCode() {
    printCodeHelper(pHeap.top(), "");
}
