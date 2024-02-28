#include <iostream>
#include <vector>

using namespace std;

// Useful formulas:
// sum_{k = 1}^n k = (n+1)n/2
// sum_{k = 1}^n k^2 = n(n+1)(2n+1)/6

int gaussSum(int n){
    return (n+1)*n/2;
}

int squaresSumm(int n){
    return n*(n+1)*(2*n+1)/6;
}

int main(){
    // Project Euler problem 6

    cout << "Ingrese el entero: ";
    int k;
    cin >> k;

    int ss = squaresSumm(k);
    int s = gaussSum(k);
    cout << s*s - ss << endl;

    return 0;
}