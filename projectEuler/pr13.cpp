#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

long long int * read_numbers(string file_name,int first_n_digits,int nnumbers){

    ifstream file(file_name);
    string current_line;
    string sub_line;
    long long int * dat;
    dat = new long long int [nnumbers];
    long long int k;

    int i = 0;
    while(getline(file,current_line)){
        
        sub_line = current_line.substr(0,first_n_digits);
        k = strtol(sub_line.c_str(),NULL,10);
        *(dat+i) = k;
        i++;
    }

    file.close();

    return dat;
}


int main(){
    // Project Euler problem 13

    int N = 100;
    int ndigits = 12;
    long long int * nums = read_numbers("pr13_data.txt",ndigits,N);

    long long int S = 0;
    for(int i = 0; i < N;i++) S += *(nums+i);

    // Check number of digits
    int k = 0;
    while(S>pow(10,k)){
        k++;
    }

    // Take the first 10 digits
    long long int ans = S/(int)pow(10,k-10);

    cout << ans << endl;

    return 0;
}