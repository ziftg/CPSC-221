#include <stdio.h>
#include <iostream>
#include <algorithm>    // std::binary_search
#include <vector>       // std::vector
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>       // provides string class
#include <cctype>       // provides isalpha() and tolower()
#include <ctime>        // for time()
#include <cstdlib>      // for rand(), srand(), and RAND_MAX
#include<map>

using namespace std;

const int MAX_HEIGHT = 16;

struct Entry
{
    string word;
    int count;
    vector<int> pages;
    
    int height;
    Entry* next[MAX_HEIGHT];
    //Entry** next[MAX_HEIGHT];
};

// skip list of Entry
class Index_SL {
public:
    Index_SL();
    ~Index_SL();
    
    int randBit();
    int nodeHeight();
    void updateCount(Entry*);
    void addPageNum(Entry*, int);
    Entry* find(string, int);
    Entry* insert(string, int);
    void printIndex(ostream&);
private:
    Entry* head;
    Entry* update[MAX_HEIGHT];
};

Index_SL::Index_SL() {
    head = new Entry;
    head->word.clear();
    head->count=0;
    head->pages.clear();
    head->height = MAX_HEIGHT;
    for(int h = 0; h < MAX_HEIGHT; h++)
        head->next[h] = NULL;
}

Index_SL::~Index_SL() {}

int Index_SL::randBit(void) {             // return a "random" bit
    static int bitsUpperBd = 0;
    static int bits;              // store bits returned by rand()
    if (bitsUpperBd == 0) {      // refresh store when empty
        bitsUpperBd = RAND_MAX;
        bits = rand();
    }
    int b = bits & 1;
    bits >>= 1;
    bitsUpperBd >>= 1;
    return b;
}

int Index_SL::nodeHeight(){
    srand( static_cast<unsigned int>(time(NULL)));
    int i;
    for(i=1; i<MAX_HEIGHT; ++i ) {
        if(randBit() == 1 ) break;
    }
    int height = i;
    return height;
}


void Index_SL::updateCount(Entry* target) {
    (target->count)++;
}

void Index_SL::addPageNum(Entry* target, int pageNum) {
    vector<int>::iterator iterPage;
    for (iterPage = target->pages.begin(); iterPage != target->pages.end(); ++iterPage) {
        if (*iterPage == pageNum)
            return;
    }
    (target->pages).push_back(pageNum);
}

Entry* Index_SL::find(string keyWord, int pageNum) {
    Entry* node = head;
    for (int h = head->height - 1; h >= 0; --h){
        
        while (node->next[h] != NULL && node->next[h]->word < keyWord)
            node = node->next[h];
        
        if (node->next[h] != NULL && node->next[h]->word==keyWord) {
            updateCount(node->next[h]);
            addPageNum(node->next[h], pageNum);
            return node->next[h];}
        
        update[h] = node;
    }
    return insert(keyWord, pageNum);
}

Entry* Index_SL::insert(string keyWord, int pageNum) {
    Entry* entryToInsert = new Entry;
    entryToInsert->word = keyWord;
    entryToInsert->count = 0;
    entryToInsert->height = nodeHeight();
    
    for(int h = 0; h < entryToInsert->height; ++h) {
        entryToInsert->next[h] = update[h]->next[h]; //initialize x's next pointers
        update[h]->next[h] = entryToInsert;          //update next pointers that change
    }
    updateCount(entryToInsert);
    addPageNum(entryToInsert, pageNum);
    return entryToInsert;
}

void Index_SL::printIndex(ostream& output) {
    vector<int>::iterator iterPage;
    
    for (Entry* node = head; node->next[0]; node = node->next[0]) {
        output << node->next[0]->word << " (" << node->next[0]->count << ") ";
        
        for (iterPage = node->next[0]->pages.begin(); iterPage != node->next[0]->pages.end(); ++iterPage) {
            if (iterPage == node->next[0]->pages.begin()){
                if (node->next[0]->pages.size()==1)
                    output << *iterPage << endl;
                else if (*(iterPage+1)-*iterPage!=1)
                    output << *iterPage << ",";
                else if (*(iterPage+1)-*iterPage==1)
                    output << *iterPage << "-";
            }
            else {
                if (iterPage==node->next[0]->pages.end()-1)
                    output<<*iterPage<<endl;
                else if (*(iterPage+1)-*iterPage!=1)
                    output << *iterPage << ",";
                else if (*(iterPage+1)-*iterPage==1&&*iterPage-*(iterPage-1)!=1)
                    output << *iterPage << "-";
                else if (*(iterPage+1)-*iterPage!=1&&*iterPage-*(iterPage-1)==1)
                    output << *iterPage;
            }
        }
    }
}



// Remove all characters except letters (A-Z,a-z) from line,
// except keep '-' or '\'' if they are between letters.
void lowercaseWords(string & line) {
    for (string::iterator it = line.begin(); it != line.end(); ++it) {
        if (!isalpha(*it)) {
            if ((*it != '-' && *it != '\'') ||
                it == line.begin() || it + 1 == line.end() ||
                !isalpha(*(it - 1)) || !isalpha(*(it + 1))) {
                *it = ' ';
            }
        }
        else {
            *it = tolower(*it);
        }
    }
}

void print(ostream & output, string & word) {
    output << word << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " book.txt index.txt" << endl;
        exit(1);
    }
    
    ifstream fin;
    fin.open(argv[1]);
    if (!fin.is_open()) {
        cerr << "Unable to open " << argv[1] << endl;
        exit(2);
    }
    
    ofstream fout;
    fout.open(argv[2]);
    if (!fout.is_open()) {
        cerr << "Unable to open " << argv[2] << endl;
        exit(3);
    }
    
    string line, word;
    Index_SL Index_SL;
    int lineNum, pageNum;
    lineNum = 0;
    pageNum = 1;
    while (!fin.eof()) {
        getline(fin, line);
        lineNum++;
        if (lineNum == 41) {
            pageNum++;
            lineNum = 1;
        }
        
        lowercaseWords(line);
        
        istringstream iss(line, istringstream::in);
        while (iss >> word) {
            Index_SL.find(word, pageNum);
        }
    }
    Index_SL.printIndex(fout);
}
