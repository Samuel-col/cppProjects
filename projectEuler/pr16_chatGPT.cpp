#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int sum = 0;
    int n = 1000;
    int result = pow(2,n);
    while (result != 0) {
        sum += result % 10;
        result /= 10;
    }
    cout << sum << endl;
    return 0;
}
