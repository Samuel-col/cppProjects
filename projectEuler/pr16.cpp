#include <iostream>

using namespace std;

int * multiply_by_two(int * D,int length,int times){
    if(times == 1){
        int load = 0;
        for(int i = 0;i < length; i++){
            if(*(D+i)<5){
                *(D+i) *= 2;
                *(D+i) += load;
                load = 0;
            }else{
                *(D+i) = (*(D+i)*2) % 10;
                *(D+i) += load;
                load = 1;
            }
        }
        return D;

    }else{
        return multiply_by_two(multiply_by_two(D,length,1),length,times-1);
    }
}

void print_digits(int * D,int length){
    cout << string(30,'-') << endl;
    bool nothing = 1;
    for(int i = length - 1; i>=0;i-- ){
        if(*(D+i) != 0) nothing = 0;
        if(!nothing) cout << *(D+i);
    }
    cout << endl;
    cout << string(30,'-') << endl;
}

int main(){
    // Project Euler problem 16

    cout << "Insert the power of two: ";
    int n; cin >> n;

    int * digits;
    digits = new int [n/2];

    *digits = 1;
    for(int i = 1; i < n/2; i++) *(digits + i) = 0;

    digits = multiply_by_two(digits,n/2,n);
    print_digits(digits,n/2);

    int s = 0;
    for(int i = 0; i < n/2; i++) s+= *(digits+i);

    cout << s << endl;



    return 0;
}