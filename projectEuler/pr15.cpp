#include <iostream>

using namespace std;

int main(){
    // Project Euler problem 15
    cout << "Enter the size of the grid: ";
    int n; cin >> n;

    double prod = 1.0;
    for(int k = 2*n; k>n; k--){
        prod *= k/(double)(k-n);
    }

    cout << (unsigned long long int)prod << endl;

    return 0;
}