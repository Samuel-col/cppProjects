#include <iostream>
#include <math.h>

using namespace std;

int nth_triangular_number(int n){
    return n*(n+1)/2;
}

int number_of_divisors(int n){

    int ndiv = 0;
    for(int k = 1; k < floor(sqrt(n)); k ++)
        ndiv += (n%k == 0);
    ndiv *= 2;
    if(floor(sqrt(n)) == sqrt(n)) ndiv++;

    return ndiv;
}

int main(){
    // Project Euler problem 12
    int ndiv;
    int n = 0;
    do{
        n++;
        ndiv = number_of_divisors(nth_triangular_number(n));
    }while(ndiv<=500);

    cout << n << " : " << nth_triangular_number(n) << " : " << number_of_divisors(nth_triangular_number(n)) << endl;

    return 0;
}