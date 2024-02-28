#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int sum_of_divisors(int n){

    int s = 0;
    for(int k = 1; k < floor(sqrt(n)); k++)
        s += k*(n%k == 0) + (n/k)*(n%k == 0)*(k!=1);
    if(floor(sqrt(n)) == sqrt(n)) s += sqrt(n);

    return s;
}

int main(){
    // Project Euler problem 21

    // Find amicable numbers
    vector<int> amicables;
    int s_divisors;
    for(int k = 1; k < 10000; k++){
        s_divisors = sum_of_divisors(k);
        if(sum_of_divisors(s_divisors) == k &&
            s_divisors != k &&
            s_divisors < 10000)
            amicables.push_back(k);
    }

    // Print and sum amicable numbers
    int s = 0;
    for(int k : amicables){
        cout << k << " | " << sum_of_divisors(k) << endl;
        s += k;
    }

    cout << "Answer: " << s << endl;


    return 0;
}