#include <iostream>
#include <cstdlib> // for atoi
using namespace std;
//5/2
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Wrong number of arguments!" << endl;
        return 1;
    }
    
    int n = atoi(argv[1]);
    for(int i = 1; i <= n/5; i++) {
        cout << "I " << i << endl;
    }
    
    for(int i = 1; i <= n/5; i++) {
        cout << "F " << n/4 << endl;
    }
    
    for(int i = 1; i <= n/5; i++) {
        cout << "R " << n/8 << endl;
    }
    
    for(int j = n/5; j >= 1; j--) {
        cout << "F " << j << endl;
    }
    
    for(int j = n/5; j >= 1; j--) {
        cout << "F " << (n/4)+1 << endl;
    }
    return 0;
}
