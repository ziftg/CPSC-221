#include "codetree.h"

// Print the Huffman code tree and list of codes for a given text file.

void usage() {
    cerr << "Usage: huftree text.txt" << endl;
    throw exception();
}

int main( int argc, char *argv[] ) {
    if( argc != 2 ) {
        usage();
    }
    
    int freq[256] = { 0 };	// array initialized to 0
    
    ifstream fin( argv[1] );
    if( fin.is_open() ) {
        char ch;
        while (fin >> noskipws >> ch) {	// don't skip whitespace
            freq[(int)ch]++;
        }
        
        fin.close();
    }
    
    CodeTree ct = CodeTree( freq );
    
    ct.printTree();
    ct.printCode();
    
    return 0;
}
