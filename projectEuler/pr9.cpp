#include <iostream>
#include <math.h>

using namespace std;

int main(){

    // Project Euler problem 9

    int a, b, c;
    for(a = 1; a < 1000; a++){
        for(b = a+1; b < 1000; b++){
            c = 1000 - a - b;
            if(c<=b) continue;
            if(pow(c,2) == pow(b,2) + pow(a,2)){
                cout << "a: " << a << endl;
                cout << "b: " << b << endl;
                cout << "c: " << c << endl;
                cout << "a*b*c: " << a*b*c << endl;
                break;
            }
        }
    }

    return 0;
}