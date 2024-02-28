#include <iostream>

using namespace std;

void print_digits(int * D,int length){
    cout << string(30,'-') << endl;
    bool nothing = 1;
    for(int i = length - 1; i>=0;i-- ){
        if(*(D+i) != 0) nothing = 0;
        if(!nothing) cout << *(D+i);
    }
    if(nothing) cout << 0;
    cout << endl;
    cout << string(30,'-') << endl;
}

int * sum_big_number(int * A,int * B,int length){

    int * R;
    R = new int [length];

    int load = 0;
    int tmp_sum;
    for(int i = 0; i<length; i++){
        tmp_sum = (*(A+i)) + (*(B+i)) + (load);
        load = tmp_sum/10;
        *(R+i) = tmp_sum - 10*load;
    }
    return R;

}

int * multiply_big_number(int * D,int m,int length){
    if(m>=100){
        cout << "Big nubers can only be multiplied by numbers less than 100" << endl;
        return {0};
    }

    int * R;
    R = new int [length];

    if(m<10){
        int load = 0;
        int tmp_product;
        int product_units;
        int product_tens;
        for(int i = 0; i < length;i++){
            tmp_product   = *(D+i)*m + load;
            product_tens  = tmp_product/10;
            product_units = tmp_product - 10*product_tens;
            *(R+i)        = product_units;
            load          = product_tens;
        }
        return R;
    }else{
        int m_tens  = m/10;
        int m_units = m - 10*m_tens;
        int * tens  = multiply_big_number(D,m_tens,length);
        int * units = multiply_big_number(D,m_units,length);
        int tmp;
        for(int i = length - 1; i > 0;i--)
            *(tens+i) = *(tens+i-1);
        *tens = 0;
        R = sum_big_number(tens,units,length);
        return R;
    }
}

int main(){
    // Project Euler problem 20

    int n = 100;
    int length = 3*n;

    int * digits;
    digits = new int [length];

    for(int i = 0; i < length; i++) *(digits + i) = 0;
    *(digits+2) = 1;

    for(int k = n-1;k>0;k--){
        digits = multiply_big_number(digits,k,length);
    }

    cout << "100!:" << endl;
    print_digits(digits,length);

    int s = 0;
    for(int i = 0; i < length; i++) s+= *(digits+i);

    cout << "Answer: " << s << endl;

    return 0;
}