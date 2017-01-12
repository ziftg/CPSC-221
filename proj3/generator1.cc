#include <iostream>
#include <cstdlib> // for atoi
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Wrong number of arguments!" << endl;
        return 1;
    }
    
    int n = atoi(argv[1]);
    for(int i = 1; i <= n/3; i++) {
        cout << "I " << i << endl;
    }
    
    for(int j = (2*n)/3; j >= (n/3)+1; j--) {
        cout << "F " << j << endl;
    }
    
    for(int j = n/3; j >= 1; j--) {
        cout << "R " << j << endl;
    }
    return 0;
}
