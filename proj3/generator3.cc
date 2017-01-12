#include <iostream>
#include <cstdlib> // for atoi
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Wrong number of arguments!" << endl;
        return 1;
    }
    
    int n = atoi(argv[1]);
    for(int j = n; j >= 1; j--) {
        cout << "I " << j << endl;
    }
    return 0;
}
